#include "Time.h"
#include "Engine.h"
#include "Plant.h"


// Private Functions
void Plant::Reproduce()
{
	Engine* engine = Engine::GetInstance();
	Vector<Entity*>& entities = engine->GetEntities();

	int plantCount = 0;

	for (int i = 0; i < entities.Size(); i++)
		if (dynamic_cast<Plant*>(entities[i])) plantCount++;

	if (plantCount >= engine->GetMaxPlants()) return;

	float angle = (float)GetRandomValue(0, 360) * DEG2RAD;
	float radius = (float)GetRandomValue(20, 60) / 10.0f;

	Vector3 spawnPos = {
		_transform.position.x + cosf(angle) * radius,
		0,
		_transform.position.z + sinf(angle) * radius
	};

	PlantData childData = {
		_name,
		_energy * 0.4f,
		_growthRate,
		_energyRate,
		_healthRate,
		_maxHeight,
		_reproductionThreshold,
		_reproductionRate * 0.8f
	};

	Plant child(childData, { 0.3f, 0.05f, 0.3f });
	engine->Instantiate(child, spawnPos);
}

// Public Functions
Plant::Plant(PlantData data, Vector3 scale) : Entity()
{
	_transform.scale = scale;
	_name = data.name;

	_growthRate = data.growthRate;
	_energy = data.energy;

	_energyRate = data.energyRate;
	_healthRate = data.healthRate;

	_maxHeight = data.maxHeight;

	_reproductionThreshold = data.ReproductionThreshold;
	_reproductionRate = data.ReproductionRate;
	_reproductionCooldown = 0.0f;
	_reproductionCooldownMax = 30.0f;
}
Plant::Plant(const Plant& o)
{
	_isDead = o._isDead;
	_transform = o._transform;

	_name = o._name;
	_growthRate = o._growthRate;
	_energy = o._energy;
	_energyRate = o._energyRate;
	_healthRate = o._healthRate;
	_maxHeight = o._maxHeight;

	_reproductionThreshold = o._reproductionThreshold;
	_reproductionRate = o._reproductionRate;
	_reproductionCooldown = o._reproductionCooldown;
	_reproductionCooldownMax = o._reproductionCooldownMax;
}

void Plant::Update()
{
	if (_isDead) return;
	if (_transform.scale.y < _maxHeight)
	{
		_energy += _energyRate * Time::DeltaTime;
		_transform.scale.y += _growthRate * Time::DeltaTime;
		_transform.scale.y = Clamp(_transform.scale.y, 0, _maxHeight);
	}

	if (_transform.scale.y != _maxHeight) return;

	_reproductionCooldown -= Time::DeltaTime;

	bool matureEnough = _transform.scale.y >= (_maxHeight * 0.6f);
	bool energyEnough = _energy >= _reproductionThreshold;
	bool cooledDown = _reproductionCooldown <= 0.0f;

	if (matureEnough && energyEnough && cooledDown)
	{
		float roll = (float)GetRandomValue(0, 1000) / 1000.0f;
		if (roll < _reproductionRate)
		{
			Reproduce();
			_reproductionCooldown = _reproductionCooldownMax;
			_energy *= 0.6f; // reproduction costs energy
		}
	}
}
void Plant::Draw()
{
	if (!_isDead)
	{
		DrawCube(_transform.position, _transform.scale.x, _transform.scale.y, _transform.scale.z, { 144, 238, 144, 255 });
		DrawCubeWires(_transform.position, _transform.scale.x, _transform.scale.y, _transform.scale.z, { 0, 68, 27, 255 });
	}
	else
	{
		DrawCube(_transform.position, _transform.scale.x, _transform.scale.y, _transform.scale.z, { 72, 119, 72, 255 });
		DrawCubeWires(_transform.position, _transform.scale.x, _transform.scale.y, _transform.scale.z, { 0, 34, 13, 255 });
	}
}
	
void Plant::Interact(Entity& other)
{
	if (_isDead) return;
	_isDead = true;

	_transform.scale = {
			_transform.scale.x - 0.1f,
			0.05f,
			_transform.scale.z - 0.1f
	};
}

Entity* Plant::Clone()
{
	return new Plant(*this);
}