#pragma once

#include "RenderObject.hpp"
#include <cmath> // For NAN

class Line2D : public RenderObject
{
private:
    Vector<float> a, b;
    Color colour;
public:
    Line2D(Vector<float> new_a, Vector<float> new_b, Color new_colour);
    virtual void draw();
    // Returns true if intersection exists within segments
    bool intersects(const Line2D& other) const;
    // Returns intersection point if it exists, otherwise Vector<float>(NAN, NAN)
    Vector<float> getIntersectionPoint(const Line2D& other) const;
    Vector<float> getA() const { return a; }
    Vector<float> getB() const { return b; }
};