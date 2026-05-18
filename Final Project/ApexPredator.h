#ifndef APEX_PREDATOR_H
#define APEX_PREDATOR_H

#include "Utils.h"
#include "Engine.h"
#include "Animal.h"

class ApexPredator : public Animal
{
private:
	Animal* _targetAnimal;
	Vector3 _wanderTarget;
	bool _reachedDestination;

	void GetTarget();
	void Wander();
	void Hunt();
public:
	ApexPredator(AnimalData data, Vector3 scale = { 1.0f, 1.0f, 1.4f });
	ApexPredator(const ApexPredator& o);

	void Update() override;
	void Interact(Entity& other) override;
	void Draw() override;

	Entity* Clone() override;
};

#endif // !APEX_PREDATOR_H
