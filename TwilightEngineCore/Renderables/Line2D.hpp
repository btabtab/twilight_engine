#pragma once

#include "RenderObject.hpp"
#include <cmath> // For NAN

enum class Axis
{
	// HORIZONTAL -> x-axis cardinalisation.
	HORIZONTAL,
	// VERTICAL -> y-axis cardinalisation.
	VERTICAL,
};

enum class Side
{
	FRONT,
	BACK,
};

class Line2D : public RenderObject2D
{
protected:
	Point<float> a, b;

public:
	Line2D();
	Line2D(Point<float> new_a, Point<float> new_b, Color new_colour);
	virtual void draw() override;
	// Returns true if intersection exists within segments
	bool intersects(const Line2D &other) const;
	// Returns intersection point if it exists, otherwise Point<float>(NAN, NAN)
	Point<float> getIntersectionPoint(const Line2D &other) const;
	Point<float> getA() const { return a; }
	Point<float> getB() const { return b; }
	void setA(const Point<float> &new_a) { a = new_a; }
	void setB(const Point<float> &new_b) { b = new_b; }
	Line2D extrapolate(float factor) const;
	/*
			Used to make sure that lines are
			facing in the same direction.
			Should be useful for bsp stuff.
	*/
	void cardinalise(Axis axis);
	Point<float> getMidPoint();
	Line2D getSplitLine(Point<float> split_point, Side side);
	Axis getGradient()
	{
		if (std::abs(b.getX() - a.getX()) < (b.getY() - a.getY()))
		{
			return Axis::HORIZONTAL; // HORIZONTAL
		}
		else
		{
			return Axis::VERTICAL; // VERTICAL
		}
	}

	// Operator overloads for == and !=
	bool operator==(const Line2D &other) const
	{
		return a == other.a && b == other.b && colour.r == other.colour.r && colour.g == other.colour.g && colour.b == other.colour.b && colour.a == other.colour.a;
	}
	bool operator!=(const Line2D &other) const
	{
		return !(*this == other);
	}
	// Shortens the line by a specified amount (integer), moving both endpoints toward the midpoint
	void shorten(int amount)
	{
		Point<float> mid = getMidPoint();
		Point<float> dirA = (mid - a).normalized();
		Point<float> dirB = (mid - b).normalized();
		a = a + dirA * amount;
		b = b + dirB * amount;
	}
	std::string getType() override
	{
	    return "Line2D";
	}
	void swapPoints()
	{
		Point<float> temp = a;
		a = b;
		b = temp;
	}
	virtual size_t getBytesConsumed() override
	{
		return sizeof(*this);
	}
};