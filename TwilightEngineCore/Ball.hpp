#pragma once
#include "TwilightNode.hpp"

class Ball: public TwilightNode
{
private:
protected:
	Vector<float> position;
	float radius;
	Color colour;
	float weight;
	
public:
	Ball(Vector<float> position, float radius, Color colour):
	TwilightNode(0), position(position), radius(radius), colour(colour)
	{
	}
	virtual void draw() override
	{
		DrawCircleV((Vector2){position.getX(), position.getY()}, radius, colour);
	}
	virtual void update() override
	{
		position = (position + Vector<float>(1.0f, 0.0f));
	}
	virtual std::string getType() override
	{
		return "Ball";
	}
};