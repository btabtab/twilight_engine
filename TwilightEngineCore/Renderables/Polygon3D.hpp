#pragma once

#include "RenderObject3D.hpp"
#include <cmath> // For NAN

class Polygon3D : public RenderObject3D
{
protected:
	Point3D<float> a, b, c;
public:
	Polygon3D();
	Polygon3D(Point3D<float> new_a, Point3D<float> new_b, Point3D<float> new_c, Color new_colour);

	virtual void draw() override
	{
		DrawTriangle3D(
						(Vector3){a.getX(), a.getY(), a.getZ()},
						(Vector3){b.getX(), b.getY(), b.getZ()},
						(Vector3){c.getX(), c.getY(), c.getZ()},
						colour
						);
	}

	Point3D<float> getA() const { return a; }
	Point3D<float> getB() const { return b; }
	Point3D<float> getC() const { return c; }

	void setA(const Point3D<float>& new_a) { a = new_a; }
	void setB(const Point3D<float>& new_b) { b = new_b; }
	void setC(const Point3D<float>& new_c) { c = new_c; }

	Polygon3D extrapolate(float factor) const;

	std::string getType() override { return "Polygon3D"; }
};