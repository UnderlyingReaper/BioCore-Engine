#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "Utils.h"
#include "Engine.h"
#include "Plant.h"
#include "Animal.h"

class Herbivore : public Animal
{
private:
	Plant* _targetPlant;
	Vector3 _wanderTarget;
	bool _reachedDestination;

	void GetTarget();
	void Wander();
	void Hunt();

public:
	Herbivore(AnimalData data, Vector3 scale = { 0.6f, 0.6f, 0.8f });
	Herbivore(const Herbivore& o);


	void Update() override;
	void Interact(Entity& other) override;
	void Draw() override;

	Entity* Clone() override;
};

#endif // !HERBIVORE_H
