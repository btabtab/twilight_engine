#pragma once

#include "Renderables/RenderObject.hpp"
#include "Light.hpp"
#include "Point.hpp"
#include "Room.hpp"
/*
	This is effectively going to
	be some kind of BSP system, except
	implementetd with an end goal.

	FOR LIGHTING! :D
*/

class LightBreakdown : public RenderObject2D
{
private:
	Room *room;
	Light *light;

	bool is_in_error_state;

	bool draw_light_lines;

	std::vector<Line2D> stored_light_lines;

	std::vector<Point<float>> intersection_vertices;

public:
	LightBreakdown(Room *new_room, Light *new_light)
		: RenderObject2D(), room(new_room), light(new_light)
	{
		// Just to ease checking for any errors.
		is_in_error_state = (!new_room || !new_light);

		room = new_room;
		light = new_light;

		draw_light_lines = true;
	}
	~LightBreakdown()
	{
		if (room)
			delete room;
		if (light)
			delete light;
	}
	void buildLightLines()
	{
		//the B point for these will be the vertex point.
		std::vector<Line2D*> light_lines;
		std::vector<Line2D> extrapolated_light_lines;

		for(Line2D line: *room->getWalls())
		{
			
		}
	}
	void cleanUpLightLines()
	{
	}
	void draw() override
	{
		if (room && light)
		{
			room->draw();
			light->draw();
		}
		for(int x = 0; x != intersection_vertices.size() - 1; x++)
		{
			for(int y = x + 1; y != intersection_vertices.size() - 1; y++)
			{
				Line2D(intersection_vertices.at(x), intersection_vertices.at(y), GREEN).draw();
			}
		}
		for(auto vertices: intersection_vertices)
		{
			DrawCircle(vertices.getX(), vertices.getY(), 5, BLUE);
		}
	}

	Room *getRoom() const { return room; }
	Light *getLight() const { return light; }
	bool isInErrorState() const { return is_in_error_state; }

	std::string getType() override { return "LightBreakdown"; }
};