#ifndef SPATIAL_DATA_H
#define SPATIAL_DATA_H

#include <raylib.h>
#include "Utils.h"

struct SpatialData
{
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	SpatialData();

	SpatialData& operator= (const SpatialData& other);

	void Translate(Vector3 dir, float speed);
	void MoveTowards(Vector3 target, float speed, float dt);

	void FaceTowards(Vector3 target);
};

#endif // !SPATIAL_DATA_H
