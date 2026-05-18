#ifndef ENTITY_H
#define ENTITY_H

#include "SpatialData.h"

class Entity
{
private:
	bool _markedForDeletion;

protected:
	SpatialData _transform;
	bool _isDead;

public:
	Entity()
	{
		_isDead = false;
		_markedForDeletion = false;
	}
	virtual ~Entity() { };

	// Getters
	SpatialData& GetTransform() { return _transform; }
	bool IsDead() { return _isDead; }
	bool IsMarkedForDeletion() { return _markedForDeletion; }

	// Setters
	void Destroy() { _markedForDeletion = true; }

	// Virtual Functions
	virtual void Update() = 0;
	virtual void Interact(Entity& other) = 0;
	virtual void Draw() = 0;
	virtual Entity* Clone() = 0;
};

#endif // !ENTITY_H
