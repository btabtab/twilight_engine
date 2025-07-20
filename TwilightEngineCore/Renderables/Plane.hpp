#pragma once

#include "Line2D.hpp"

enum Direction
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
};

/*
	A line that will have a direction to face.
	Used for rendering the line in 3D and will
	and will determine visibility and draw
	order...
*/
class Plane: public Line2D
{
private:
	/*
		A normalised value that will point
		in the direction that the direction
		that the plane is facing.
	*/
	Point<float> facing;
public:
	Plane(Direction direction, Point<float> new_a, Point<float> new_b, Color new_colour)
	: Line2D(new_a, new_b, new_colour), facing(0, 1)
	{
		makePlaneFaceDirection(direction);
	}
	Plane(Direction direction, Line2D line):
	Line2D(line.getA(), line.getB(), line.getColour()), facing(0, 1)
	{
		makePlaneFaceDirection(direction);
	}
	/*
		This makes the plane face a certain direction by
		resetting the planes facing direction and basically
		spins it around in increments of 90 degrees so that
		it matches the direction.
	*/
	void makePlaneFaceDirection(Direction direction)
	{
		/*
			TODO: make it so that instead of it being
			"facing = Point<float>(0, 1);" it makes it
			so that it is a distance of 1 away from
			the midpoint that is rotated 90 degrees
			relative to the slop of the line.
		*/
		//Reset the vector.
		facing = Point<float>(0, 1);
		//Controls the direction the plane ends up facing.
		for(int i = 0; i != direction; i++)
		{
			facing.rotateAroundPoint(getMidPoint(), 90 * i);
		}
	}
	void draw() override
	{
		DrawLine(
					a.getX(), a.getY(),
					b.getX(), b.getY(),
					colour
				);
		Point<float> mid_point = getMidPoint();
		DrawLine(
				mid_point.getX(), mid_point.getY(),
				//Facing line is drawn from the center.
				mid_point.getX() + facing.getX(),
				mid_point.getY() + facing.getY(),
				colour
				);
	}
};