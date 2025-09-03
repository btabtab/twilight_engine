#pragma once

#include "Line2D.hpp"
#include "../Point.hpp"
#include <stdexcept>
#include <algorithm>
#include <cmath>

class Polygon: public RenderObject2D
{
private:
	Point<float> a, b, c; // Points defining the polygon
	Color color; // Added member variable for color

public:
	Polygon(Point<float> pointA, Point<float> pointB, Point<float> pointC, Color polygonColor = RED)
		: a(pointA), b(pointB), c(pointC), color(polygonColor)
	{
		// Ensure the points form a valid triangle
		if (a == b || b == c || c == a)
		{
			// throw std::invalid_argument("A polygon must have three DISTINCT points.");
		}
		// Ensure points are in counter-clockwise order
		float cross = (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
		if (cross < 0) {
			std::swap(b, c);
		}
	}

	void draw() override
	{
		Line2D line_ab = Line2D(a, b, color);
		Line2D line_bc = Line2D(b, c, color);
		Line2D line_ca = Line2D(c, a, color);
		line_ab.draw();
		line_bc.draw();
		line_ca.draw();
	}

	void cardinalise()
	{
		a.setX(std::round(a.getX()));
		a.setY(std::round(a.getY()));
		b.setX(std::round(b.getX()));
		b.setY(std::round(b.getY()));
		c.setX(std::round(c.getX()));
		c.setY(std::round(c.getY()));
	}

	std::string getType() override
	{
		return "Polygon";
	}
};