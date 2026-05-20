#include "Time.h"
#include "Herbivore.h"
#include <rlgl.h>

// Private
void Herbivore::GetTarget()
{
	Vector<Entity*>& entities = Engine::GetInstance()->GetEntities();
	for (int i = 0; i < entities.Size(); i++)
	{
		if (entities[i] == this) continue;
		if (entities[i]->IsDead()) continue;

		Plant* plant = dynamic_cast<Plant*>(entities[i]);
		if (plant == nullptr) continue;

		if (Distance(_transform.position, plant->GetTransform().position) <= _range)
			_targetPlant = plant;
	}
}
void Herbivore::Wander()
{
	if (_reachedDestination)
	{
		Vector3 randomDir = GetRandomDirection();

		_wanderTarget = {
			_transform.position.x + randomDir.x * _range,
			0,
			_transform.position.z + randomDir.z * _range
		};

		_reachedDestination = false;
	}

	_transform.FaceTowards(_wanderTarget);
	_transform.MoveTowards(_wanderTarget, _speed, Time::DeltaTime);

	if (Distance(_transform.position, _wanderTarget) <= 0.2f)
		_reachedDestination = true;
}
void Herbivore::Hunt()
{
	if (_targetPlant->IsDead() || _targetPlant->IsMarkedForDeletion())
	{
		_targetPlant = nullptr;
		return;
	}

	_transform.MoveTowards(_targetPlant->GetTransform().position, _speed, Time::DeltaTime);
	_transform.FaceTowards(_targetPlant->GetTransform().position);

	if (Distance(_transform.position, _targetPlant->GetTransform().position) <= 0.2f)
	{
		_targetPlant->Interact(*this);
		_hunger = 0;
		_targetPlant = nullptr;
	}
}


// Public
Herbivore::Herbivore(AnimalData data, Vector3 scale) : Animal(data, scale)
{
	_targetPlant = nullptr;
	_reachedDestination = true;
}
Herbivore::Herbivore(const Herbivore& o) : Animal(o)
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

	_targetPlant = nullptr;
	_reachedDestination = o._reachedDestination;
}

void Herbivore::Update()
{
	if (_isDead) return;

	_hunger += _hungerRate * Time::DeltaTime;
	_hunger = Clamp(_hunger, 0, _maxHunger);
	if (_hunger >= _maxHunger)
	{
		_isDead = true;
		_transform.scale = {
			_transform.scale.x - 0.05f,
			_transform.scale.y - 0.1f,
			_transform.scale.z - 0.05f
		};

		return;
	}

	if (_targetPlant == nullptr)
		GetTarget();

	if (_targetPlant != nullptr && _hunger >= _maxHunger * 0.25f)
		Hunt();
	else
		Wander();
}
void Herbivore::Interact(Entity& other)
{
	if (_isDead)
	{
		Destroy();
		return;
	}

	_isDead = true;
}
void Herbivore::Draw()
{
	Color baseColor = _isDead ? Color{ 100, 100, 100, 255 } : Color{ 34, 139, 34, 255 };
	Color wireColor = _isDead ? Color{ 50, 50, 50, 255 } : Color{ 0, 100, 0, 255 };

	rlPushMatrix();
		rlTranslatef(_transform.position.x, _transform.position.y, _transform.position.z);
		rlRotatef(_transform.rotation.y, 0, 1, 0);
		rlRotatef(_transform.rotation.x, 1, 0, 0);

		DrawCube(ZeroVector(), _transform.scale.x, _transform.scale.y, _transform.scale.z, baseColor);
		DrawCubeWires(ZeroVector(), _transform.scale.x, _transform.scale.y, _transform.scale.z, wireColor);
	rlPopMatrix();
}

Entity* Herbivore::Clone()
{
	return new Herbivore(*this);
}