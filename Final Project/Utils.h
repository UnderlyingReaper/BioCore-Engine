#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>
#include <cmath>

inline float Clamp(float value, float min, float max)
{
	if (value < min) return min;
	if (value > max) return max;
	else return value;
}

inline float Distance(Vector3 a, Vector3 b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}
inline float Vector3Length(Vector3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
inline Vector3 Normalize(Vector3 v)
{
    float mag = Vector3Length(v);
    if (mag == 0) return { 0, 0, 0 };

    return { v.x / mag, v.y / mag, v.z / mag };
}

inline Vector3 GetRandomDirection() {
    float rx = (float)GetRandomValue(-100, 100) / 100.0f;
    float ry = (float)GetRandomValue(-100, 100) / 100.0f;
    float rz = (float)GetRandomValue(-100, 100) / 100.0f;

    Vector3 dir = { rx, ry, rz };
    float mag = sqrtf(dir.x * dir.x + dir.z * dir.z);

    dir = Normalize(dir);
    return dir;
}

inline Vector3 VectorUp() { return { 0, 1, 0 }; }
inline Vector3 VectorForward() { return { 0, 0, 1 }; }
inline Vector3 VectorRight() { return { 1, 0, 0 }; }
inline Vector3 ZeroVector() { return { 0, 0, 0 }; }

inline Vector3 operator+(Vector3 a, Vector3 b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
inline Vector3 operator-(Vector3 a, Vector3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
inline Vector3 operator-(Vector3 v) { return { -v.x, -v.y, -v.z }; }
inline Vector3 operator*(Vector3 v, float f) { return { v.x * f, v.y * f, v.z * f }; }
inline Vector3 operator*(Vector3 a, Vector3 b) { return { a.x * b.x, a.y * b.y, a.z * b.z }; }

#endif // !UTILS_H
