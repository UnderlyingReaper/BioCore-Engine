#ifndef SCAVENGER_H
#define SCAVENGER_H

#include "Utils.h"
#include "Engine.h"
#include "Animal.h"

class Scavenger : public Animal
{
private:
	Animal* _targetAnimal;
	Vector3 _wanderTarget;
	bool _reachedDestination;

	void GetTarget();
	void Wander();
	void Hunt();

public:
	Scavenger(AnimalData data, Vector3 scale = { 1.4f, 0.4f, 0.8f });
	Scavenger(const Scavenger& o);


	void Update() override;
	void Interact(Entity& other) override;
	void Draw() override;

	Entity* Clone() override;
};

#endif // !SCAVENGER_H
