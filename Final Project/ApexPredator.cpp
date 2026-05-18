#include "Time.h"
#include "ApexPredator.h"
#include <rlgl.h>

// Private Methods
void ApexPredator::GetTarget()
{
	Vector<Entity*>& entities = Engine::GetInstance()->GetEntities();
	for (int i = 0; i < entities.Size(); i++)
	{
		if (entities[i] == this) continue;
		if (entities[i]->IsDead()) continue;

		Animal* animal = dynamic_cast<Animal*>(entities[i]);
		if (animal == nullptr) continue;
		if (animal->GetTransform().position.y > 0.5f) continue;

		if (Distance(_transform.position, animal->GetTransform().position) <= _range)
			_targetAnimal = animal;
	}
}
void ApexPredator::Wander()
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

	if (Distance(_transform.position, _wanderTarget) <= 0.1f)
		_reachedDestination = true;
}
void ApexPredator::Hunt()
{
	if (_targetAnimal->IsDead() || _targetAnimal->IsMarkedForDeletion())
	{
		_targetAnimal = nullptr;
		return;
	}

	_transform.MoveTowards(_targetAnimal->GetTransform().position, _speed, Time::DeltaTime);
	_transform.FaceTowards(_targetAnimal->GetTransform().position);

	if (Distance(_transform.position, _targetAnimal->GetTransform().position) <= 0.3f)
	{
		_targetAnimal->Interact(*this);
		_hunger = 0;
		_targetAnimal = nullptr;
	}
}

// Public Methods
ApexPredator::ApexPredator(AnimalData data, Vector3 scale) : Animal(data, scale)
{
	_targetAnimal = nullptr;
	_reachedDestination = true;
}

ApexPredator::ApexPredator(const ApexPredator& o) : Animal(o)
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
	_reachedDestination = true;
}

void ApexPredator::Update()
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

	if (_targetAnimal == nullptr)
		GetTarget();

	if (_targetAnimal != nullptr && _hunger >= _maxHunger * 0.1f)
		Hunt();
	else
		Wander();
}
void ApexPredator::Interact(Entity& other)
{
	if (_isDead)
	{
		Destroy();
		return;
	}

	_isDead = true;
}
void ApexPredator::Draw()
{
	Color baseColor = _isDead ? Color{ 90, 30, 30, 255 } : Color{ 200, 40, 40, 255 };
	Color wireColor = _isDead ? Color{ 50, 10, 10, 255 } : Color{ 100, 10, 10, 255 };

	rlPushMatrix();
		rlTranslatef(_transform.position.x, _transform.position.y, _transform.position.z);
		rlRotatef(_transform.rotation.y, 0, 1, 0);
		rlRotatef(_transform.rotation.x, 1, 0, 0);

		DrawCube(ZeroVector(), _transform.scale.x, _transform.scale.y, _transform.scale.z, baseColor);
		DrawCubeWires(ZeroVector(), _transform.scale.x, _transform.scale.y, _transform.scale.z, wireColor);
	rlPopMatrix();
}

Entity* ApexPredator::Clone()
{
	return new ApexPredator(*this);
}