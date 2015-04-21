#include "stdafx.h"
#include "Vector3.h"


Vector3::Vector3() : x(0.f), y(0.f), z(0.f)
{
}

Vector3::Vector3(f32 x, f32 y, f32 z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(f32 s) : x(s), y(s), z(s)
{
}

Vector3::Vector3(const Vector3& otherV) : x(otherV.x), y(otherV.y), z(otherV.z)
{
}

bool Vector3::Equals(Vector3 other, f32 tolerance)
{
	return (abs(this->x - other.x) < EPSILON) && (abs(this->y - other.y) < EPSILON) && (abs(this->z - other.z) < EPSILON);
}