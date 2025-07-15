#pragma once
#include "TwilightNode.hpp"
#include "Renderables/Line2D.hpp"

class CollisionMan: public TwilightNode
{
private:
protected:
    Line2D* a;
    Line2D* b;
    Vector<float> collision_position;
    bool is_there_a_collision = false;
public:
	CollisionMan(Line2D* new_a, Line2D* new_b):
	TwilightNode(0), a(new_a), b(new_b), collision_position(Vector<float>(0, 0))
	{
	}
	virtual void draw() override
	{
        if(is_there_a_collision)
        {
            DrawCircleV((Vector2){collision_position.getX(), collision_position.getY()}, 5, RED);
        }
	}
	virtual void update() override
	{
        if(a->intersects(*b))
        {
            collision_position = a->getIntersectionPoint(*b);
            is_there_a_collision = true;
        }
	}
	virtual std::string getType() override
	{
		return "CollisionMan";
	}
};