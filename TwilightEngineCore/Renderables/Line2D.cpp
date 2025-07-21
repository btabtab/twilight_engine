#include "Line2D.hpp"
#include <algorithm> // For std::min, std::max
#include <cmath> // For NAN

Line2D::Line2D()
: RenderObject(MAGENTA), a(0, 0), b(0, 0)
{
}

Line2D::Line2D(Point<float> new_a, Point<float> new_b, Color new_colour)
: RenderObject(new_colour), a(new_a), b(new_b)
{
    // std::cout << "New Line2D created\n";
    layer = Layers::MIDDLE;
    cardinalise(Axis::HORIZONTAL);
}

Line2D Line2D::extrapolate(float factor) const
{
	Point<float> direction_b = b - a;
	Point<float> new_b = b + direction_b * factor;
	Point<float> direction_a = a - b;
	Point<float> new_a = a + direction_a * factor;
	return Line2D(new_a, new_b, colour);
}

void Line2D::draw()
{
    DrawLine(a.getX(), a.getY(), b.getX(), b.getY(), colour);
}

bool Line2D::intersects(const Line2D& other) const
{
    float x1 = a.getX(), y1 = a.getY();
    float x2 = b.getX(), y2 = b.getY();
    float x3 = other.a.getX(), y3 = other.a.getY();
    float x4 = other.b.getX(), y4 = other.b.getY();

    float denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if (denom == 0) return false; // Lines are parallel

    float px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / denom;
    float py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / denom;

    auto between = [](float a, float b, float c) { return c >= std::min(a, b) && c <= std::max(a, b); };
    return between(x1, x2, px) && between(y1, y2, py) &&
           between(x3, x4, px) && between(y3, y4, py);
}

Point<float> Line2D::getIntersectionPoint(const Line2D& other) const
{
    float x1 = a.getX(), y1 = a.getY();
    float x2 = b.getX(), y2 = b.getY();
    float x3 = other.a.getX(), y3 = other.a.getY();
    float x4 = other.b.getX(), y4 = other.b.getY();

    float denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if (denom == 0) return Point<float>(NAN, NAN); // Lines are parallel

    float px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / denom;
    float py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / denom;

    auto between = [](float a, float b, float c) { return c >= std::min(a, b) && c <= std::max(a, b); };
    if (between(x1, x2, px) && between(y1, y2, py) &&
        between(x3, x4, px) && between(y3, y4, py))
    {
        return Point<float>(px, py);
    }
    return Point<float>(NAN, NAN);
}

void Line2D::cardinalise(Axis axis)
{
	if (a.getX() < b.getX() && axis == Axis::HORIZONTAL)
	{
		std::swap(a, b);
	}
	if (a.getY() < b.getY() && axis == Axis::VERTICAL)
	{
		std::swap(a, b);
	}
}

Point<float> Line2D::getMidPoint()
{
    return Point<float>((a.getX() + b.getX()) / 2, (a.getY() + b.getY()) / 2);
}

Line2D Line2D::getSplitLine(Point<float> split_point, Side side)
{
    if(side == Side::FRONT)
    {
        return Line2D(a, split_point, colour);
    }
    return Line2D(split_point, b, colour);
}