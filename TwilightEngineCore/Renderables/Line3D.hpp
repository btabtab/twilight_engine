#pragma once

#include "RenderObject3D.hpp"
#include <cmath> // For NAN

class Line3D : public RenderObject3D
{
protected:
	Point3D<float> a, b;
public:
	Line3D();
	Line3D(Point3D<float> new_a, Point3D<float> new_b, Color new_colour);
	virtual void draw();
	// Returns true if intersection exists within segments (3D)
	bool intersects(const Line3D& other) const;
	// Returns intersection point if it exists, otherwise Point3D<float>(NAN, NAN, NAN)
	Point3D<float> getIntersectionPoint(const Line3D& other) const;
	Point3D<float> getA() const { return a; }
	Point3D<float> getB() const { return b; }
	void setA(const Point3D<float>& new_a) { a = new_a; }
	void setB(const Point3D<float>& new_b) { b = new_b; }
	Line3D extrapolate(float factor) const;
	/*
		Used to make sure that lines are
		facing in the same direction.
		Should be useful for bsp stuff.
	*/
	void cardinalise(const Point3D<float>& axis);
	Point3D<float> getMidPoint() const;
	// Operator overloads for == and !=
	bool operator==(const Line3D& other) const {
		return a == other.a && b == other.b && colour.r == other.colour.r && colour.g == other.colour.g && colour.b == other.colour.b && colour.a == other.colour.a;
	}
	bool operator!=(const Line3D& other) const {
		return !(*this == other);
	}
	// Rotates either endpoint (A or B) around the other, by axis and degrees
	// If rotateA is true, rotates A around B; else rotates B around A
	void rotateEndPoint(bool rotateA, const Point3D<float>& axis, double degrees)
	{
		if (rotateA) {
			a = Point3D<float>::rotateAroundAxis(a, b, axis, degrees);
		} else {
			b = Point3D<float>::rotateAroundAxis(b, a, axis, degrees);
		}
	}
};