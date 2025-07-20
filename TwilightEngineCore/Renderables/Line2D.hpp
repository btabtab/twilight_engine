#pragma once

#include "RenderObject.hpp"
#include <cmath> // For NAN

class Line2D : public RenderObject
{
protected:
	Point<float> a, b;
	Color colour;
public:
	Line2D(Point<float> new_a, Point<float> new_b, Color new_colour);
	virtual void draw();
	// Returns true if intersection exists within segments
	bool intersects(const Line2D& other) const;
	// Returns intersection point if it exists, otherwise Point<float>(NAN, NAN)
	Point<float> getIntersectionPoint(const Line2D& other) const;
	Point<float> getA() const { return a; }
	Point<float> getB() const { return b; }
	void setA(const Point<float>& new_a) { a = new_a; }
	void setB(const Point<float>& new_b) { b = new_b; }
	/*
		Used to make sure that lines are
		facing in the same direction.
		Should be useful for bsp stuff.
	*/
	void cardinalise();
	Point<float> getMidPoint();
};