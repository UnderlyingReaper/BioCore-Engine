#ifndef ENGINE_H
#define ENGINE_H

#include "Vector.h"
#include "Entity.h"

class Engine
{
private:
	Vector<Entity*> _entities;

	Engine() { }
	~Engine() { }

public:
	static Engine* GetInstance();

	Vector<Entity*>& GetEntities() { return _entities; }

	void Instantiate(Entity& entity, Vector3 pos = { 0, 0, 0 }, Vector3 rot = { 0, 0, 0 });

	void DrawWorld();
	void UpdateTick();
	void RenderPass();
	void DeletePass();
};

#endif // !ENGINE_H
