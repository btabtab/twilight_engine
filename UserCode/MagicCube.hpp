#pragma once

#include <raylib.h>
#include <iostream>
#include <string>

#include "../TwilightEngineCore/Renderables/RenderClasses.hpp"

class MagicCube : public RenderObject3D
{
private:
	float rotation_speed;
	float rotation_angle;
	Line3D edges[12];
	Point3D<float> center;
public:
	MagicCube(Point3D<float> new_center):
	RenderObject3D(), center(new_center)
	{
		setColour(WHITE);
		
		edges[0] = Line3D(	center + Point3D<float>(1, 1, 1),	center + Point3D<float>(-1, 1, 1), RED);
		edges[1] = Line3D(	center + Point3D<float>(-1, 1, 1),	center + Point3D<float>(-1, -1, 1), GREEN);
		edges[2] = Line3D(	center + Point3D<float>(-1, -1, 1),	center + Point3D<float>(1, -1, 1), BLUE);
		edges[3] = Line3D(	center + Point3D<float>(1, -1, 1),	center + Point3D<float>(1, 1, 1), YELLOW);
		edges[4] = Line3D(	center + Point3D<float>(1, 1, -1),	center + Point3D<float>(-1, 1, -1), ORANGE);
		edges[5] = Line3D(	center + Point3D<float>(-1, 1, -1),	center + Point3D<float>(-1, -1, -1), BLUE);
		edges[6] = Line3D(	center + Point3D<float>(-1, -1, -1),center + Point3D<float>(1, -1, -1), PURPLE);
		edges[7] = Line3D(	center + Point3D<float>(1, -1, -1),	center + Point3D<float>(1, 1, -1), MAGENTA);
		edges[8] = Line3D(	center + Point3D<float>(1, 1, 1),	center + Point3D<float>(1, 1, -1), WHITE);
		edges[9] = Line3D(	center + Point3D<float>(-1, 1, 1),	center + Point3D<float>(-1, 1, -1), WHITE);
		edges[10] = Line3D(	center + Point3D<float>(-1, -1, 1),	center + Point3D<float>(-1, -1, -1), WHITE);
		edges[11] = Line3D(	center + Point3D<float>(1, -1, 1),	center + Point3D<float>(1, -1, -1), WHITE);
	}

	void draw() override
	{
		for (auto& edge : edges)
		{
			edge.draw();
		}
	}

	void update() override
	{
		setPosition(getPosition() + Point3D<float>(0, 0, 0.1f));
	}
	void setPosition(Point3D<float> new_position)
	{
		center = new_position;
		
		edges[0] = Line3D(	center + Point3D<float>(1, 1, 1),	center + Point3D<float>(-1, 1, 1), RED);
		edges[1] = Line3D(	center + Point3D<float>(-1, 1, 1),	center + Point3D<float>(-1, -1, 1), GREEN);
		edges[2] = Line3D(	center + Point3D<float>(-1, -1, 1),	center + Point3D<float>(1, -1, 1), BLUE);
		edges[3] = Line3D(	center + Point3D<float>(1, -1, 1),	center + Point3D<float>(1, 1, 1), YELLOW);
		edges[4] = Line3D(	center + Point3D<float>(1, 1, -1),	center + Point3D<float>(-1, 1, -1), ORANGE);
		edges[5] = Line3D(	center + Point3D<float>(-1, 1, -1),	center + Point3D<float>(-1, -1, -1), BLUE);
		edges[6] = Line3D(	center + Point3D<float>(-1, -1, -1),center + Point3D<float>(1, -1, -1), PURPLE);
		edges[7] = Line3D(	center + Point3D<float>(1, -1, -1),	center + Point3D<float>(1, 1, -1), MAGENTA);
		edges[8] = Line3D(	center + Point3D<float>(1, 1, 1),	center + Point3D<float>(1, 1, -1), WHITE);
		edges[9] = Line3D(	center + Point3D<float>(-1, 1, 1),	center + Point3D<float>(-1, 1, -1), WHITE);
		edges[10] = Line3D(	center + Point3D<float>(-1, -1, 1),	center + Point3D<float>(-1, -1, -1), WHITE);
		edges[11] = Line3D(	center + Point3D<float>(1, -1, 1),	center + Point3D<float>(1, -1, -1), WHITE);
	}
	Point3D<float> getPosition()
	{
		return center;
	}
	std::string getType() override
	{
		return "MagicCube";
	}
};