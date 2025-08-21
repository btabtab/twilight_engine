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
	Line3D edges[12] = {
		Line3D(Point3D<float>(1, 1, 1), Point3D<float>(-1, 1, 1), RED),
		Line3D(Point3D<float>(-1, 1, 1), Point3D<float>(-1, -1, 1), GREEN),
		Line3D(Point3D<float>(-1, -1, 1), Point3D<float>(1, -1, 1), BLUE),
		Line3D(Point3D<float>(1, -1, 1), Point3D<float>(1, 1, 1), YELLOW),
		Line3D(Point3D<float>(1, 1, -1), Point3D<float>(-1, 1, -1), ORANGE),
		Line3D(Point3D<float>(-1, 1, -1), Point3D<float>(-1, -1, -1), BLUE),
		Line3D(Point3D<float>(-1, -1, -1), Point3D<float>(1, -1, -1), PURPLE),
		Line3D(Point3D<float>(1, -1, -1), Point3D<float>(1, 1, -1), MAGENTA),
		Line3D(Point3D<float>(1, 1, 1), Point3D<float>(1, 1, -1), WHITE),
		Line3D(Point3D<float>(-1, 1, 1), Point3D<float>(-1, 1, -1), WHITE),
		Line3D(Point3D<float>(-1, -1, 1), Point3D<float>(-1, -1, -1), WHITE),
		Line3D(Point3D<float>(1, -1, 1), Point3D<float>(1, -1, -1), WHITE)
	};
public:
	MagicCube(float speed = 1.0f):
	RenderObject3D(), rotation_speed(speed), rotation_angle(0.0f)
	{
		setColour(WHITE);
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
		for(auto& edge : edges)
		{
			edge.setA(edge.getA() + Point3D<float>(0, 0, 0.25));
			edge.setB(edge.getB() + Point3D<float>(0, 0, 0.25));
			if(1.0f < edge.getA().getZ())
			{
			}
		}
	}
};