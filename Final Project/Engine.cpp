#include "Engine.h"

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
	DrawPlane({ 0, -0.01f, 0 }, { 100, 100 }, { 38, 70, 45, 255 });
	DrawGrid(20, 5);
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