#include "RenderObject.hpp"

RenderObject::RenderObject()
{
    layer = Layers::MIDDLE;
}

RenderObject::RenderObject(Color new_colour)
: colour(new_colour)
{
    // std::cout << "New Render Object Constructed...\n";
    layer = Layers::MIDDLE;
}

void RenderObject::setColour(Color new_colour)
{
    colour = new_colour;
}

Layers RenderObject::getLayer()
{
    return layer;
}

void RenderObject::draw()
{
}
void RenderObject::update()
{
}

Color RenderObject::getColour() const
{
    return colour;
}

void RenderObject::toggleVisibility()
{
    is_visible = !is_visible;
}

bool RenderObject::isVisible() const
{
    return is_visible;
}
