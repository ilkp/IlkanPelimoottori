#pragma once
#include <ostream>
#include <string>
#include <sstream>
#include <iomanip>

class Vector3d
{
public:
	double x, y, z;

	Vector3d()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	Vector3d(double x, double y, double z) : x(x), y(y), z(z) {}

	std::string& ToString()
	{
		std::string s = "Vector3d( " + std::to_string(x) + " ; " + std::to_string(y) + " ; " + std::to_string(z) + " )\n";
		return s;
	}

	std::string ToString(int precision)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(precision);
		ss << "Vector3d( " << x << " ; " << y << " ; " << z << " )\n";
		return ss.str();
	}

	Vector3d operator+(Vector3d rhs)
	{
		Vector3d v;
		v.x = this->x + rhs.x;
		v.y = this->y + rhs.y;
		v.z = this->z + rhs.z;
		return v;
	}

	Vector3d operator*(double rhs)
	{
		Vector3d v;
		v.x = this->x * rhs;
		v.y = this->y * rhs;
		v.z = this->z * rhs;
		return v;
	}

	void operator+=(Vector3d rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
	}

	void operator*=(double rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
	}
};