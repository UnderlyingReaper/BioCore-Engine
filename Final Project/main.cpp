#include <raylib.h>

#include "Time.h"
#include "Engine.h"
#include "InputManager.h"
#include "Plant.h"
#include "Herbivore.h"
#include "Scavenger.h"
#include "ApexPredator.h"

int main()
{
	InitWindow(1366, 768, "BioCore Engine");
	SetTargetFPS(120);

	// Camera Setup
	Camera3D cam = { 0 };
	cam.position = { 20, 20, 20 };
	cam.target = { 0, 0, 0 };
	cam.up = { 0, 1, 0 };
	cam.fovy = 45.0f;
	cam.projection = CAMERA_PERSPECTIVE;


	// System Initialization
	Engine* engine = Engine::GetInstance();
	InputManager* inputManager = InputManager::GetInstance();

	// Name, Energy, GrowthRate, EnergyRate, HealthRate, MaxHeight, RepThreshold, RepRate
	PlantData data1 = { "Fern",  3, 0.05f, 0.5f, 1, 1.2f, 5.0f,  0.02f };
	PlantData data2 = { "Shrub", 6, 0.03f, 0.3f, 1, 2.0f, 8.0f,  0.01f };
	PlantData data3 = { "Grass", 2, 0.08f, 0.8f, 1, 0.8f, 3.0f,  0.04f };

	// Name, Speed, Range, MaxHealth, MaxHunger, HungerRate
	AnimalData herbData = { "Herbivore",    1.0f,  8,  80,  100, 0.5f };
	AnimalData scavData = { "Scavenger",    1.7f,  15, 60,  80,  0.3f };
	AnimalData apexData = { "Apex Predator", 2.0f, 12, 150, 120, 0.4f };

	Plant plant1(data1);
	Plant plant2(data2);
	Plant plant3(data3);
	Herbivore herb(herbData);
	Scavenger scav(scavData);
	ApexPredator apex(apexData);

	engine->Instantiate(plant1, { 1, 0, 1 });
	engine->Instantiate(plant2, { -2, 0, -1});
	engine->Instantiate(plant3, {5, 0, 2});

	engine->Instantiate(herb, { 5, 0, 5 });
	engine->Instantiate(scav, { 10, 5, 10 });
	engine->Instantiate(apex, { 15, 0, 15 });


	// Main Loop
	DisableCursor();
	while (!WindowShouldClose())
	{
		// Pre Frame
		inputManager->Update();

		if (!inputManager->IsPaused())
		{
			Time::Tick();
			engine->UpdateTick();
		}

		UpdateCamera(&cam, CAMERA_FREE);

		BeginDrawing();
			ClearBackground({ 135, 206, 235, 255 });

			BeginMode3D(cam);
				engine->RenderPass(); // Render World & Entities
			EndMode3D();

			// UI
			DrawFPS(GetScreenWidth() - 80, 10);
			DrawText(TextFormat("Elapsed Time: %.1f", Time::ElapsedTime), 10, 10, 20, WHITE);
			if (inputManager->IsPaused())
			{
				int textWidth = MeasureText("PAUSED", 24);
				int posX = (GetScreenWidth() - textWidth) / 2;

				// Draw the aligned text
				DrawText("PAUSED", posX, 15, 24, RED);
			}
		EndDrawing();

		// Post Frame Cleanup
		if (!inputManager->IsPaused())
		{
			engine->DeletePass();
		}
	}

	CloseWindow();
	return 0;
}