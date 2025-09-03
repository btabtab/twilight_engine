#pragma once
#include "TwilightNode.hpp"

class Ball: public RenderObject
{
private:
protected:
	Point<float> position;
	float radius;
	Color colour;
	float weight;
	
public:
	Ball(Point<float> position, float radius, Color colour):
	RenderObject(), position(position), radius(radius), colour(colour)
	{
	}
	virtual void draw() override
	{
		DrawCircleV((Vector2){position.getX(), position.getY()}, radius, colour);
	}
	virtual void update() override
	{
		position = (position + Point<float>(1.0f, 0.0f));
	}
	virtual std::string getType() override
	{
		return "Ball";
	}
};