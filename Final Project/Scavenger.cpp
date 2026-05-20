#include "Time.h"
#include <rlgl.h>
#include "Scavenger.h"

// Private
void Scavenger::GetTarget()
{
	Vector<Entity*>& entities = Engine::GetInstance()->GetEntities();
	for (int i = 0; i < entities.Size(); i++)
	{
		if (entities[i] == this) continue;
		if (!entities[i]->IsDead()) continue;

		Animal* animal = dynamic_cast<Animal*>(entities[i]);
		if (animal == nullptr) continue;

		if (Distance(_transform.position, animal->GetTransform().position) <= _range)
			_targetAnimal = animal;
	}
}
void Scavenger::Wander()
{
	if (_reachedDestination)
	{
		Vector3 randomDir = GetRandomDirection();

		_wanderTarget = {
			_transform.position.x + randomDir.x * _range,
			10 + (float)GetRandomValue(-1, 3),
			_transform.position.z + randomDir.z * _range
		};

		_reachedDestination = false;
	}

	_transform.MoveTowards(_wanderTarget, _speed, Time::DeltaTime);
	_transform.FaceTowards(_wanderTarget);
	if (Distance(_transform.position, _wanderTarget) <= 0.4f)
		_reachedDestination = true;
}
void Scavenger::Hunt()
{
	if (_targetAnimal->IsMarkedForDeletion() || _targetAnimal == nullptr)
	{
		_targetAnimal = nullptr;
		return;
	}

	_transform.MoveTowards(_targetAnimal->GetTransform().position, _speed, Time::DeltaTime);
	_transform.FaceTowards(_targetAnimal->GetTransform().position);

	if (Distance(_transform.position, _targetAnimal->GetTransform().position) <= 0.2f)
	{
		_targetAnimal->Interact(*this);
		_hunger = 0;
		_targetAnimal = nullptr;
	}
}


// Public
Scavenger::Scavenger(AnimalData data, Vector3 scale) : Animal(data, scale)
{
	_targetAnimal = nullptr;
	_reachedDestination = true;
}
Scavenger::Scavenger(const Scavenger& o) : Animal(o)
{
	_isDead = o._isDead;
	_transform = o._transform;

	_name = o._name;
	_health = o._health;
	_hunger = o._hunger;
	_speed = o._speed;
	_range = o._range;

	_maxHealth = o._maxHealth;
	_maxHunger = o._maxHunger;

	_hungerRate = o._hungerRate;

	_targetAnimal = nullptr;
	_reachedDestination = o._reachedDestination;
}

void Scavenger::Update()
{
	if (_isDead)
	{
		if (_transform.position.y >= 0.1f)
			_transform.MoveTowards({ _transform.position.x, 0, _transform.position.z }, 2, Time::DeltaTime);
		return;
	}

	_hunger += _hungerRate * Time::DeltaTime;
	_hunger = Clamp(_hunger, 0, _maxHunger);
	if (_hunger >= _maxHunger)
	{
		_isDead = true;
		_transform.scale = {
			_transform.scale.x - 0.05f,
			_transform.scale.y - 0.05f,
			_transform.scale.z - 0.1f
		};

		return;
	}

	if (_targetAnimal == nullptr)
		GetTarget();

	if (_targetAnimal != nullptr && _hunger >= _maxHunger * 0.25f)
		Hunt();
	else
		Wander();
}
void Scavenger::Interact(Entity& other)
{
	if (_isDead)
	{
		Destroy();
		return;
	}
	else
	{
		_isDead = true;
		return;
	}
}
void Scavenger::Draw()
{
	Color baseColor = _isDead ? Color{ 89, 77, 55, 255 } : Color{ 178, 154, 110, 255 };
	Color wireColor = _isDead ? Color{ 50, 40, 25, 255 } : Color{ 100, 80, 50, 255 };

	rlPushMatrix();
		rlTranslatef(_transform.position.x, _transform.position.y, _transform.position.z);
		rlRotatef(_transform.rotation.y, 0, 1, 0);
		rlRotatef(_transform.rotation.x, 1, 0, 0);

		DrawCube(ZeroVector(), _transform.scale.x, _transform.scale.y, _transform.scale.z, baseColor);
		DrawCubeWires(ZeroVector(), _transform.scale.x, _transform.scale.y, _transform.scale.z, wireColor);
	rlPopMatrix();
}

Entity* Scavenger::Clone()
{
	return new Scavenger(*this);
}