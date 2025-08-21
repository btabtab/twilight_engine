#include "Line3D.hpp"
#include <cmath>

Line3D::Line3D() : RenderObject3D(), a(Point3D<float>(0,0,0)), b(Point3D<float>(0,0,0)) {}

Line3D::Line3D(Point3D<float> new_a, Point3D<float> new_b, Color new_colour)
	: RenderObject3D(), a(new_a), b(new_b)
{
	setColour(new_colour);
}

void Line3D::draw()
{
	DrawLine3D((Vector3){a.getX(), a.getY(), a.getZ()}, (Vector3){b.getX(), b.getY(), b.getZ()}, getColour());
}
