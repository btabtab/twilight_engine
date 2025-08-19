#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

template <typename T>
class Point
{
private:
	T x, y, z;

public:
	Point(T new_x, T new_y, T new_z = 0) : x(new_x), y(new_y), z(new_z)
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
	T getZ() const
	{
		return z;
	}

	void setX(T new_x)
	{
		x = new_x;
	}
	void setY(T new_y)
	{
		y = new_y;
	}
	void setZ(T new_z)
	{
		z = new_z;
	}

	// Grabs the midpoint between this and another vector<t>.
	Point<T> midpoint(const Point<T> &other) const
	{
		return Point<T>((x + other.getX()) / 2, (y + other.getY()) / 2, (z + other.getZ()) / 2);
	}
	/*
		Used to get the midpoint between
		a group of other points.
	*/
	Point<T> midpoint(const std::vector<Point<T>> &other)
	{
		Point<T> ret(0, 0, 0);
		for (int i = 0; i != other.size(); i++)
		{
			ret += other.at(i);
		}
		ret = ret / other.size();
		return ret;
	}

	Point<T> operator+(const Point<T> &other) const
	{
		return Point<T>(x + other.getX(), y + other.getY(), z + other.getZ());
	}
	void operator+=(const Point<T> &other)
	{
		x += other.getX();
		y += other.getY();
		z += other.getZ();
	}

	void set(Point<T> new_vector)
	{
		setX(new_vector.getX());
		setY(new_vector.getY());
		setZ(new_vector.getZ());
	}

	Point<T> operator-(const Point<T> &other) const
	{
		return Point<T>(x - other.getX(), y - other.getY(), z - other.getZ());
	}

	Point<T> operator*(const T &scalar) const
	{
		return Point<T>(x * scalar, y * scalar, z * scalar);
	}

	Point<T> operator/(const T &scalar) const
	{
		if (scalar == 0)
		{
			std::cout << "0 Division occurred :(\n";
			return Point<T>(0, 0);
		}
		return Point<T>(x / scalar, y / scalar, z / scalar);
	}

	bool operator==(const Point<T> &other) const
	{
		return (x == other.getX() && y == other.getY() && z == other.getZ());
	}
	bool operator!=(const Point<T> &other) const
	{
		return !(*this == other);
	}

	// Z-ify from here on out...
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
		return "Point(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	// Rotation code here plox... <3
	void rotateAroundPoint(Point<T> center, double degrees)
	{
	}
	float distanceTo(Point<T> other)
	{
		float dx = x - other.getX();
		float dy = y - other.getY();
		return std::sqrt(dx * dx + dy * dy);
	}
};