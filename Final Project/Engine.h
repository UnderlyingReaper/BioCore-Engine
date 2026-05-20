#ifndef ENGINE_H
#define ENGINE_H

#include "Vector.h"
#include "Entity.h"

class Engine
{
private:
	Vector<Entity*> _entities;
	int _maxPlants;
	int _MapSize;

	Engine();
	~Engine() { }

public:
	static Engine* GetInstance();

	Vector<Entity*>& GetEntities() { return _entities; }
	int GetMaxPlants() const { return _maxPlants; }
	int GetMapSize() const { return _MapSize; }

	void SetMaxPlants(int max) { _maxPlants = max; }
	void SetMapSize(int size) { _MapSize = size; }

	void Instantiate(Entity& entity, Vector3 pos = { 0, 0, 0 }, Vector3 rot = { 0, 0, 0 });

	void DrawWorld();
	void DrawHUD();
	void UpdateTick();
	void RenderPass();
	void DeletePass();
};

#endif // !ENGINE_H
