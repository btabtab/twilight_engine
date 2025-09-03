#pragma once

#include <raylib.h>
#include "Point.hpp"
#include "Renderables/RenderObject.hpp"
#include "Renderables/Line2D.hpp"
class Light : public RenderObject2D
{
private:
	Point<float> position;
	Color colour;
	float intensity; // How strong the light is
public:
	Light(Point<float> new_position, Color new_colour, float new_intensity)
	: position(new_position), colour(new_colour), intensity(new_intensity)
	{}
	Point<float> getPosition() const { return position; }
	void setPosition(Point<float> new_position) { position = new_position; }
	Color getColour() const { return colour; }
	void setColour(Color new_colour) { colour = new_colour; }
	float getIntensity() const { return intensity; }
	void setIntensity(float new_intensity) { intensity = new_intensity; }

	void draw() override
	{
		DrawCircle(position.getX(), position.getY(), 7.5f, colour);
	}
	std::string getType() override { return "Light"; }
};