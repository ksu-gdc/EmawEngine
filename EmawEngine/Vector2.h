#pragma once

#include "Types.h"
#include "MathCore.h"
#include <iostream>

struct Vector2
{
public:
	f32 x;
	f32 y;

	Vector2();
	Vector2(f32 x, f32 y);
	Vector2(f32 s);
	Vector2(const Vector2& otherV);

	inline Vector2 operator-() const { return Vector2(-x, -y); }

	inline Vector2& operator=(const Vector2& other) { x = other.x; y = other.y; return *this; }

	inline Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
	inline Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
	inline Vector2 operator+(const f32 val) const { return Vector2(x + val, y + val); }
	inline Vector2& operator+=(const f32 val) { x += val; y += val; return *this; }

	inline Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
	inline Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
	inline Vector2 operator-(const f32 val) const { return Vector2(x - val, y - val); }
	inline Vector2& operator-=(const f32 val) { x -= val; y -= val; return *this; }

	inline Vector2 operator*(const Vector2& other) const { return Vector2(x * other.x, y * other.y); }
	inline Vector2& operator*=(const Vector2& other) { x *= other.x; y *= other.y; return *this; }
	inline Vector2 operator*(const f32 v) const { return Vector2(x * v, y * v); }
	inline Vector2& operator*=(const f32 v) { x *= v; y *= v; return *this; }

	inline Vector2 operator/(const Vector2& other) const { return Vector2(x / other.x, y / other.y); }
	inline Vector2& operator/=(const Vector2& other) { x /= other.x; y /= other.y; return *this; }
	inline Vector2 operator/(const f32 v) const { f32 i = (f32)1.0 / v; return Vector2(x * i, y * i); }
	inline Vector2& operator/=(const f32 v) { f32 i = (f32)1.0 / v; x *= i; y *= i; return *this; }

	inline float DotProduct(const Vector2 vector) const
	{
		return x*vector.x + y*vector.y;
	}

	inline f32 Length()
	{
		return 1.f / sqrt(x*x + y*y);
	}

	inline Vector2 Normalize()
	{
		f32 length = Length();
		x = x * length;
		y = y * length;
		return *this;
	}

	inline Vector2 GetNormalized()
	{
		Vector2 retVal = Vector2(*this);
		return retVal.Normalize();
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ")";
		return os;
	}

	inline static Vector2 UnitX() { return Vector2(1.f, 0.f); }
	inline static Vector2 UnitY() { return Vector2(0.f, 1.f); }

	bool Equals(Vector2 other, f32 tolerance = EPSILON);
};

