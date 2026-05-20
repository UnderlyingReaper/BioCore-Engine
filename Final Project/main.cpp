#include <raylib.h>

#include "Time.h"
#include "Vector.h"
#include "UserInterfaceUtils.h"
#include "Engine.h"
#include "InputManager.h"
#include "Plant.h"
#include "Herbivore.h"
#include "Scavenger.h"
#include "ApexPredator.h"


enum SimulationState { MENU, SIMULATION };

bool DrawButton(Rectangle bounds, const char* text)
{
	bool clicked = false;
	Vector2 mousePoint = GetMousePosition();
	bool isHovered = CheckCollisionPointRec(mousePoint, bounds);

	if (isHovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		clicked = true;

	// Draw Button
	DrawRectangleRec(bounds, isHovered ? LIGHTGRAY : GRAY);
	DrawRectangleLinesEx(bounds, 2, DARKGRAY);

	int textWidth = MeasureText(text, 20);
	DrawText(text, bounds.x + bounds.width / 2 - textWidth / 2, bounds.y + bounds.height / 2 - 10, 20, BLACK);

	return clicked;
}
void DrawParameter(int startX, int y, const char* label, int& value, int step, int minVal)
{
	DrawText(label, startX - 100, y + 10, 20, BLACK);

	if (DrawButton({ (float)startX + 120, (float)y, 40, 40 }, "-") && value > minVal)
		value -= step;

	DrawText(TextFormat("%d", value), startX + 180, y + 10, 20, DARKBLUE);

	if (DrawButton({ (float)startX + 230, (float)y, 40, 40 }, "+"))
		value += step;
}

void InitializeSimulation(int mapSize, int maxPlants, int maxAnimals, int pctHerb, int pctScav, int pctApex)
{
	Engine* engine = Engine::GetInstance();
	engine->SetMapSize(mapSize);
	engine->SetMaxPlants(maxPlants);

	Vector<PlantData> plantLibrary;
	plantLibrary.PushBack({ "Fern",  2, 0.05f, 0.5f, 1, 0.5f, 8.0f,  0.01f });
	plantLibrary.PushBack({ "Shrub", 3, 0.03f, 0.3f, 1, 1.0f, 11.0f,  0.005f });
	plantLibrary.PushBack({ "Grass", 1, 0.08f, 0.8f, 1, 0.8f, 5.0f,  0.02f });

	AnimalData herbData = { "Herbivore",     1.0f,  8,  80,  100, 0.5f };
	AnimalData scavData = { "Scavenger",     1.7f, 15,  60,   80, 0.3f };
	AnimalData apexData = { "Apex Predator", 2.0f, 12, 150,  120, 0.4f };

	// Spawn Plants
	for (int i = 0; i < maxPlants; i++) {
		PlantData randomData = plantLibrary[GetRandomValue(0, plantLibrary.Size() - 1)];
		Plant p(randomData);
		Vector3 randomPos = { (float)GetRandomValue(-mapSize, mapSize), 0, (float)GetRandomValue(-mapSize, mapSize) };
		engine->Instantiate(p, randomPos);
	}

	// Normalize percentages
	float totalPct = (float)(pctHerb + pctScav + pctApex);
	if (totalPct == 0) totalPct = 1.0f;

	int numHerb = (int)((pctHerb / totalPct) * maxAnimals);
	int numScav = (int)((pctScav / totalPct) * maxAnimals);
	int numApex = maxAnimals - numHerb - numScav;

	// Spawn Herbivores
	for (int i = 0; i < numHerb; i++)
	{
		Herbivore h(herbData);
		Vector3 randomPos = { (float)GetRandomValue(-mapSize, mapSize), 0, (float)GetRandomValue(-mapSize, mapSize) };
		engine->Instantiate(h, randomPos);
	}

	// Spawn Scavengers
	for (int i = 0; i < numScav; i++)
	{
		Scavenger s(scavData);
		Vector3 randomPos = { (float)GetRandomValue(-mapSize, mapSize), 0, (float)GetRandomValue(-mapSize, mapSize) };
		engine->Instantiate(s, randomPos);
	}

	// Spawn Apex Predators
	for (int i = 0; i < numApex; i++)
	{
		ApexPredator a(apexData);
		Vector3 randomPos = { (float)GetRandomValue(-mapSize, mapSize), 0, (float)GetRandomValue(-mapSize, mapSize) };
		engine->Instantiate(a, randomPos);
	}
}

int main()
{
	InitWindow(1366, 768, "BioCore Engine");
	SetTargetFPS(120);

	// Simulation Parameters
	SimulationState currentState = SimulationState::MENU;
	int mapSize = 100;
	int maxPlants = 200;
	int maxAnimals = 50;
	int weightHerbivore = 60;
	int weightScavenger = 30;
	int weightApex = 10;

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

	// Main Loop
	EnableCursor();
	while (!WindowShouldClose())
	{
		if (currentState == MENU) {
			// ---------- MENU RENDERING ----------
			BeginDrawing();
				ClearBackground(RAYWHITE);

				DrawAlignedText("BIOCORE SIMULATION SETUP", GetScreenWidth() / 2, 100, 30, DARKGRAY);

				// UI Variables Setup
				int startX = GetScreenWidth() / 2 - 150;
				int startY = 200;
				int spacing = 60;

				DrawParameter(startX, startY, "Map Size: ", mapSize, 5, 0);
				DrawParameter(startX, startY + spacing, "Max Plants:", maxPlants, 10, 0);
				DrawParameter(startX, startY + spacing * 2, "Max Animals:", maxAnimals, 5, 0);
				DrawParameter(startX, startY + spacing * 3, "Herbivore %:", weightHerbivore, 5, 0);
				DrawParameter(startX, startY + spacing * 4, "Scavenger %:", weightScavenger, 5, 0);
				DrawParameter(startX, startY + spacing * 5, "Apex %:", weightApex, 5, 0);

				// Start Simulation Button
				if (DrawButton({ (float)GetScreenWidth() / 2 - 100, (float)startY + spacing * 7, 200, 50 }, "START SIMULATION"))
				{
					InitializeSimulation(mapSize, maxPlants, maxAnimals, weightHerbivore, weightScavenger, weightApex);
					currentState = SIMULATION;
					DisableCursor();
				}

			EndDrawing();
		}
		else if (currentState == SIMULATION) {
			// ---------- SIMULATION RENDERING ----------
			inputManager->Update();

			if (!inputManager->IsPaused()) {
				Time::Tick();
				engine->UpdateTick();
			}

			UpdateCamera(&cam, CAMERA_FREE);

			BeginDrawing();
			ClearBackground({ 135, 206, 235, 255 });

			BeginMode3D(cam);
			engine->RenderPass();
			EndMode3D();

			engine->DrawHUD();
			EndDrawing();

			if (!inputManager->IsPaused()) {
				engine->DeletePass();
			}
		}
	}

	CloseWindow();
	return 0;
}