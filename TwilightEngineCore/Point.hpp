#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

template <typename T>
class Point
{
private:
	T x, y;

public:
	Point(T new_x, T new_y) : x(new_x), y(new_y)
	{
	}

	T getX() const
	{
		return x;
	}
	T getY() const
	{
		return y;
	}

	void setX(T new_x)
	{
		x = new_x;
	}
	void setY(T new_y)
	{
		y = new_y;
	}

	// Grabs the midpoint between this and another vector<t>.
	Point<T> midpoint(const Point<T> &other) const
	{
		return Point<T>((x + other.getX()) / 2, (y + other.getY()) / 2);
	}
	/*
		Used to get the midpoint between
		a group of other points.
	*/
	Point<T> midpoint(const std::vector<Point<T>> &other)
	{
		Point<T> ret(0, 0);
		for (int i = 0; i != other.size(); i++)
		{
			ret += other.at(i);
		}
		ret = ret / other.size();
		return ret;
	}

	Point<T> operator+(const Point<T> &other) const
	{
		return Point<T>(x + other.getX(), y + other.getY());
	}
	void operator+=(const Point<T> &other)
	{
		x += other.getX();
		y += other.getY();
	}

	void set(Point<T> new_vector)
	{
		setX(new_vector.getX());
		setY(new_vector.getY());
	}

	Point<T> operator-(const Point<T> &other) const
	{
		return Point<T>(x - other.getX(), y - other.getY());
	}

	Point<T> operator*(const T &scalar) const
	{
		return Point<T>(x * scalar, y * scalar);
	}

	Point<T> operator/(const T &scalar) const
	{
		if (scalar == 0)
		{
			std::cout << "0 Division occurred :(\n";
			return Point<T>(0, 0);
		}
		return Point<T>(x / scalar, y / scalar);
	}

	bool operator==(const Point<T> &other) const
	{
		return (x == other.getX() && y == other.getY());
	}
	bool operator!=(const Point<T> &other) const
	{
		return !(*this == other);
	}

	float length() const
	{
		return std::sqrt(x * x + y * y);
	}

	// Point<T> normalized() const
	// {
	// 	float len = length();
	// 	if (len == 0) throw std::runtime_error("Can't normalize zero-length vector(s)");
	// 	return Point<T>(x / len, y / len);
	// }
	float dot(const Point<T> &other) const
	{
		return x * other.getX() + y * other.getY();
	}

	Point<T> makePerpendicular() const
	{
		return Point<T>(-y, x);
	}

	std::string stringify() const
	{
		return "Point<float>(" + std::to_string(x) + ".f, " + std::to_string(y) + ".f)";
	}

	// Rotate this point around another point by degrees (2D)
	void rotateAroundPoint(const Point<T>& center, double degrees)
	{
		double radians = degrees * M_PI / 180.0;
		T dx = x - center.getX();
		T dy = y - center.getY();
		T cosA = std::cos(radians);
		T sinA = std::sin(radians);
		T rx = dx * cosA - dy * sinA;
		T ry = dx * sinA + dy * cosA;
		x = center.getX() + rx;
		y = center.getY() + ry;
	}
	float distanceTo(Point<T> other)
	{
		float dx = x - other.getX();
		float dy = y - other.getY();
		return std::sqrt(dx * dx + dy * dy);
	}
	Point<T> normalized() const
	{
		float len = length();
		if (len == 0) throw std::runtime_error("Can't normalize zero-length vector(s)");
		return Point<T>(x / len, y / len);
	}
};

// 3D Point/Vector class
template <typename T>
class Point3D
{
	private:
	T x, y, z;
	
	public:
	Point3D(T new_x, T new_y, T new_z) : x(new_x), y(new_y), z(new_z) {}

	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }

	void setX(T new_x) { x = new_x; }
	void setY(T new_y) { y = new_y; }
	void setZ(T new_z) { z = new_z; }

	Point3D<T> operator+(const Point3D<T> &other) const
	{
		return Point3D<T>(x + other.x, y + other.y, z + other.z);
	}
	void operator+=(const Point3D<T> &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}
	Point3D<T> operator-(const Point3D<T> &other) const
	{
		return Point3D<T>(x - other.x, y - other.y, z - other.z);
	}
	Point3D<T> operator*(const T &scalar) const
	{
		return Point3D<T>(x * scalar, y * scalar, z * scalar);
	}
	Point3D<T> operator/(const T &scalar) const
	{

		if (scalar == 0)
		{
			std::cout << "0 Division occurred :(\n";
			return Point3D<T>(0, 0, 0);
		}
		return Point3D<T>(x / scalar, y / scalar, z / scalar);
	}
	bool operator==(const Point3D<T> &other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}
	bool operator!=(const Point3D<T> &other) const
	{
		return !(*this == other);
	}
	float length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}
	float dot(const Point3D<T> &other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}
	Point3D<T> cross(const Point3D<T> &other) const
	{
		return Point3D<T>(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}
	Point3D<T> normalized() const
	{
		float len = length();
		if (len == 0)
			throw std::runtime_error("Can't normalize zero-length vector(s)");
		return Point3D<T>(x / len, y / len, z / len);
	}
	float distanceTo(const Point3D<T> &other) const
	{
		float dx = x - other.x;
		float dy = y - other.y;
		float dz = z - other.z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}
	std::string stringify() const
	{
		return "Point3D(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}
	
	// Static: Rotate a point around an axis and origin by degrees, returns new point
	static Point3D<T> rotateAroundAxis(Point3D<T> point, Point3D<T> origin, Point3D<T> axis, double degrees)
	{
		// Translate point to origin
		Point3D<T> rel = point - origin;
		double radians = degrees * M_PI / 180.0;
		Point3D<T> k = axis.normalized();
		T cosA = std::cos(radians);
		T sinA = std::sin(radians);
		// Rodrigues' rotation formula
		Point3D<T> rotated = rel * cosA + k.cross(rel) * sinA + k * (k.dot(rel)) * (1 - cosA);
		// Translate back
		return origin + rotated;
	}
};