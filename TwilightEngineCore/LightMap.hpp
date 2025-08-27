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

class LightBreakdown : public RenderObject
{
private:
	Room *room;
	Light *light;

	bool is_in_error_state;

	bool draw_light_lines;

	std::vector<Line2D> stored_light_lines;

public:
	LightBreakdown(Room *new_room, Light *new_light)
		: RenderObject(), room(new_room), light(new_light)
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
	/*
		Build the lines that will be used to draw
		the polygons for the floor, ceiling and
		handle drawing the walls.
	*/
	void buildLightLines()
	{
	}
	/*
		Run through the wall lines and the light lines
		and remove any light lines that will be blocked
		by any walls.
	*/
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
	}

	Room *getRoom() const { return room; }
	Light *getLight() const { return light; }
	bool isInErrorState() const { return is_in_error_state; }

	std::string getType() override { return "LightBreakdown"; }
};