#pragma once

#include <raylib.h>
#include <iostream>
#include <string>

#include "../TwilightEngineCore/Renderables/RenderClasses.hpp"

class Floor : public RenderObject3D
{
private:
	Line3D edges[4];
	Point3D<float> center;
public:
	Floor(Point3D<float> new_center):
	RenderObject3D(), center(new_center)
	{
		setColour(WHITE);
		
		setPosition(Point3D<float>(0, 0, 0));
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
		// setPosition(getPosition() + Point3D<float>(0, 0, 0.1f));
	}
	void setPosition(Point3D<float> new_position)
	{
		center = new_position;
		edges[0] = Line3D(center + Point3D<float>(+1, -0, +1), center + Point3D<float>(0, 0, 0), RED);
		edges[1] = Line3D(center + Point3D<float>(-1, -0, +1), center + Point3D<float>(0, 0, 0), GREEN);
		edges[2] = Line3D(center + Point3D<float>(-1, -0, -1), center + Point3D<float>(0, 0, 0), BLUE);
		edges[3] = Line3D(center + Point3D<float>(+1, -0, -1), center + Point3D<float>(0, 0, 0), YELLOW);
	}
	Point3D<float> getPosition()
	{
		return center;
	}
	std::string getType() override
	{
		return "Floor";
	}
};