#include "RenderObject.hpp"

RenderObject2D::RenderObject2D()
{
    layer = DrawLayer::MIDDLE;
    //Why didn't I already do this?
    sub_render_object = nullptr;
}

RenderObject2D::RenderObject2D(Color new_colour)
: colour(new_colour)
{
    // std::cout << "New Render Object Constructed...\n";
    layer = DrawLayer::MIDDLE;
    //Why didn't I already do this?
    sub_render_object = nullptr;
}

void RenderObject2D::setColour(Color new_colour)
{
    colour = new_colour;
}

DrawLayer RenderObject2D::getLayer()
{
    return layer;
}
void RenderObject2D::setLayer(DrawLayer new_layer)
{
    layer = new_layer;
}


void RenderObject2D::draw()
{
}
void RenderObject2D::update()
{
}

Color RenderObject2D::getColour() const
{
    return colour;
}

void RenderObject2D::toggleVisibility()
{
    is_visible = !is_visible;
}

bool RenderObject2D::isVisible() const
{
    return is_visible;
}
