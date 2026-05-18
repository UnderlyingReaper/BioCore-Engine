#include "SpatialData.h"

SpatialData::SpatialData() : position({ 0, 0, 0 }), rotation({ 0, 0, 0 }), scale({ 1, 1, 1 }) { }

SpatialData& SpatialData::operator= (const SpatialData& other)
{
	position = other.position;
	rotation = other.rotation;
	scale = other.scale;

	return *this;
}

void SpatialData::Translate(Vector3 dir, float speed)
{
	float magnitude = sqrtf(pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2));
	if (magnitude == 0) return;

	position.x += (dir.x / magnitude) * speed;
	position.y += (dir.y / magnitude) * speed;
	position.z += (dir.z / magnitude) * speed;
}
void SpatialData::MoveTowards(Vector3 target, float speed, float dt)
{
	Vector3 dir = target - position;
	Translate(dir, speed * dt);
}

void SpatialData::FaceTowards(Vector3 target)
{
	Vector3 dir = target - position;
	if (Vector3Length(dir) <= 0.001f) return;

	rotation.y = atan2(dir.x, dir.z) * RAD2DEG;

	float horrizontalDist = sqrtf(dir.x * dir.x + dir.z * dir.z);
	rotation.x = atan2(-dir.y, horrizontalDist) * RAD2DEG;
}