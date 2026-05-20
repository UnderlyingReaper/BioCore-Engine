#include "Engine.h"
#include "Time.h"
#include "InputManager.h"
#include "UserInterfaceUtils.h"


// Private Functions
Engine::Engine()
{
	_maxPlants = 200;
	_MapSize = 100;
}

// Public Functions
Engine* Engine::GetInstance()
{
	static Engine instance;
	return &instance;
}

void Engine::Instantiate(Entity& entity, Vector3 pos, Vector3 rot)
{
	Entity* newEntity = entity.Clone();

	newEntity->GetTransform().position = pos;
	newEntity->GetTransform().rotation = rot;

	_entities.PushBack(newEntity);
}

void Engine::DrawWorld()
{
	DrawPlane({ 0, -0.01f, 0 }, { 1000, 1000 }, { 38, 70, 45, 255 });
	DrawGrid(20, 10);
}
void Engine::DrawHUD()
{
	InputManager* inputManager = InputManager::GetInstance();

	DrawFPS(GetScreenWidth() - 80, 10);
	DrawText(TextFormat("Elapsed Time: %.1f", Time::ElapsedTime), 10, 10, 20, WHITE);
	if (inputManager->IsPaused())
	{
		DrawAlignedText("PAUSED", GetScreenWidth() / 2, 15, 24, RED);
	}
	if (Time::TimeScale > 1)
	{
		DrawAlignedText("SPED UP", GetScreenWidth() / 2, 40, 20, ORANGE);
	}
}

void Engine::UpdateTick()
{
	for (int i = 0; i < _entities.Size(); i++)
		_entities[i]->Update();
}
void Engine::RenderPass()
{
	DrawWorld();

	for (int i = 0; i < _entities.Size(); i++)
		_entities[i]->Draw();
}
void Engine::DeletePass()
{
	for (int i = 0; i < _entities.Size(); i++)
	{
		if (_entities[i]->IsMarkedForDeletion())
		{
			delete _entities[i];
			_entities.Erase(i);
			i--;
		}
	}
}