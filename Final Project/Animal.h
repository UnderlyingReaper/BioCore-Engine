#ifndef ANIMAL_H
#define ANIMAL_H

#include "String.h"
#include "Entity.h"

struct AnimalData
{
	String Name;
	float Speed;
	float Range;

	float MaxHealth;
	float MaxHunger;

	float HungerRate;
};

class Animal: public Entity
{
protected:
	String _name;
	float _health;
	float _speed;
	float _range;
	float _hunger;

	float _maxHealth;
	float _maxHunger;

	float _hungerRate = 1;

public:
	Animal(AnimalData data, Vector3 scale = { 0.5f, 0.5f, 0.5f })
	{
		_transform.scale = scale;

		_name = data.Name;
		_health = data.MaxHealth;
		_hunger = 0;
		_speed = data.Speed;
		_range = data.Range;

		_maxHealth = data.MaxHealth;
		_maxHunger = data.MaxHunger;

		_hungerRate = data.HungerRate;
	}
	virtual ~Animal() {};

	float GetHealth() const { return _health; }
	float GetHunger() const { return _hunger; }
	float GetSpeed() const { return _speed; }

	void Update() override = 0;
	void Interact(Entity& other) override = 0;
	void Draw() override = 0;
	Entity* Clone() override = 0;
};

#endif // !ANIMAL_H
