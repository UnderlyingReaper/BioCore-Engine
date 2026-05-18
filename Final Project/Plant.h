#ifndef PLANT_H
#define PLANT_H

#include <raylib.h>
#include "String.h"
#include "Entity.h"
#include "Engine.h"

struct PlantData
{
	String name;
	float energy;

	float growthRate;
	float energyRate;
	float healthRate;
	
	float maxHeight;

	float ReproductionThreshold;
	float ReproductionRate;
};

class Plant: public Entity
{
private:
	String _name;
	float _growthRate;
	float _energyRate;
	float _healthRate;

	float _energy;

	float _maxHeight;

	float _reproductionThreshold;
	float _reproductionRate;
	float _reproductionCooldown;
	float _reproductionCooldownMax;

	void Reproduce();

public:
	Plant(PlantData data, Vector3 scale = { 0.6f, 0.15f, 0.6f });
	Plant(const Plant& o);
	
	void Update() override;
	void Draw() override;
	void Interact(Entity& other) override;
	Entity* Clone() override;
};

#endif // !PLANT_H
