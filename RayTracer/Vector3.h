#pragma once

#include <cmath>

class Vector3
{
public:
	Vector3();
	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	Vector3(const Vector3 &cpy) : x(cpy.x), y(cpy.y), z(cpy.z) {}
	~Vector3();

	double x, y, z;

	Vector3 operator + (const Vector3 &vec)
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3 operator - (const Vector3 &vec)
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 operator * (const double scalar)
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 operator / (const double scalar)
	{
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	double DotProduct(const Vector3 &vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	Vector3 CrossProduct(const Vector3 &vec) const
	{
		return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
	}

	Vector3 Normalized() const
	{
		double mag = Magnitude();
		return Vector3(x / mag, y / mag, z / mag);
	}

	double Magnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	static Vector3 random()
	{
		return Vector3(rand() % 10000, rand() % 10000, rand() % 10000).Normalized();
	}
};

