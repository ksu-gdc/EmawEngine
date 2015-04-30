#include "stdafx.h"
#include "Vector2.h"


Vector2::Vector2() : x(0.f), y(0.f)
{
}


Vector2::Vector2(f32 x, f32 y) : x(x), y(y)
{
}

Vector2::Vector2(f32 s) : x(s), y(s)
{
}

Vector2::Vector2(const Vector2& otherV) : x(otherV.x), y(otherV.y)
{
}

bool Vector2::Equals(Vector2 other, f32 tolerance)
{
	return (abs(this->x - other.x) < E) && (abs(this->y - other.y) < EPSILON);
}
