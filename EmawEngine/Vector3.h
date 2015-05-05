#pragma once

#include "Types.h"
#include "MathCore.h"
#include <iostream>

struct Vector3 {
public:
	f32 x;
	f32 y;
	f32 z;

	Vector3();
	Vector3(f32 x, f32 y, f32 z);
	Vector3(f32 s);
	Vector3(const Vector3& otherV);

	inline Vector3 operator-() const { return Vector3(-x, -y, -z); }

	inline Vector3& operator=(const Vector3& other) { x = other.x; y = other.y; z = other.z; return *this; }

	inline Vector3 operator+(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
	inline Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
	inline Vector3 operator+(const f32 val) const { return Vector3(x + val, y + val, z + val); }
	inline Vector3& operator+=(const f32 val) { x += val; y += val; z += val; return *this; }

	inline Vector3 operator-(const Vector3& other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
	inline Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	inline Vector3 operator-(const f32 val) const { return Vector3(x - val, y - val, z - val); }
	inline Vector3& operator-=(const f32 val) { x -= val; y -= val; z -= val; return *this; }

	inline Vector3 operator*(const Vector3& other) const { return Vector3(x * other.x, y * other.y, z * other.z); }
	inline Vector3& operator*=(const Vector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	inline Vector3 operator*(const f32 v) const { return Vector3(x * v, y * v, z * v); }
	inline Vector3& operator*=(const f32 v) { x *= v; y *= v; z *= v; return *this; }

	inline Vector3 operator/(const Vector3& other) const { return Vector3(x / other.x, y / other.y, z / other.z); }
	inline Vector3& operator/=(const Vector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
	inline Vector3 operator/(const f32 v) const { f32 i = (f32)1.0 / v; return Vector3(x * i, y * i, z * i); }
	inline Vector3& operator/=(const f32 v) { f32 i = (f32)1.0 / v; x *= i; y *= i; z *= i; return *this; }

	inline float DotProduct(const Vector3 v) const
	{
		return x*v.x + y*v.y + z*v.z;
	}

	inline Vector3 CrossProduct(const Vector3& p) const
	{
		return Vector3(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}

	inline f32 Length()
	{
		return 1.f / sqrtf(x*x + y*y + z*z);
	}

	inline Vector3 Normalize()
	{
		f32 length = Length();
		x = x * length;
		y = y * length;
		z = z * length;
		return *this;
	}

	inline Vector3 GetNormalized()
	{
		Vector3 ret = Vector3(*this);
		return ret.Normalize();
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector3& v) { os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; return os; }

	inline static Vector3 UnitX() { return Vector3(1.f, 0.f, 0.f); }
	inline static Vector3 UnitY() { return Vector3(0.f, 1.f, 0.f); }
	inline static Vector3 UnitZ() { return Vector3(0.f, 0.f, 1.f); }

	bool Equals(Vector3 other, f32 tolerance = EPSILON);
};
