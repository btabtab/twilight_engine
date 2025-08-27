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
		// This will be the function that builds the light lines
		// from the room and light.
		if (is_in_error_state)
		{
			return;
		}

		stored_light_lines.clear();

		// For each wall in the room, create a line from the light to each endpoint of the wall
		for (auto &wall : *room->getWalls())
		{
			/*
				Lines get shortened here so that they don't
				clip with their origin wall which will lead
				to incorrect "light lines" being removed.
			*/
			stored_light_lines.push_back(Line2D(light->getPosition(), wall.getA(), RED));
			stored_light_lines.back().shorten(3);
			stored_light_lines.push_back(Line2D(light->getPosition(), wall.getB(), RED));
			stored_light_lines.back().shorten(3);
		}

		// Sort the lines by angle around the light source
		std::sort(stored_light_lines.begin(), stored_light_lines.end(),
				  [this](const Line2D &a, const Line2D &b)
				  {
					  Point<float> dir_a = a.getB() - light->getPosition();
					  Point<float> dir_b = b.getB() - light->getPosition();
					  float angle_a = std::atan2(dir_a.getY(), dir_a.getX());
					  float angle_b = std::atan2(dir_b.getY(), dir_b.getX());
					  return angle_a < angle_b;
				  });
	}
	/*
		Run through the wall lines and the light lines
		and remove any light lines that will be blocked
		by any walls.
	*/
	void cleanUpLightLines()
	{
		for (size_t i = 0; i < stored_light_lines.size(); i++)
		{
			// Ensure point B is the further away point from the light
			Line2D &line = stored_light_lines[i];
			float distA = std::sqrt(std::pow(line.getA().getX() - light->getPosition().getX(), 2) +
								std::pow(line.getA().getY() - light->getPosition().getY(), 2));
			float distB = std::sqrt(std::pow(line.getB().getX() - light->getPosition().getX(), 2) +
								std::pow(line.getB().getY() - light->getPosition().getY(), 2));
			if (distA > distB)
			{
				line.swapPoints();
			}

			for (int k = 0; k < room->getWalls()->size(); k++)
			{
				std::cout << "Checking light line " << i << " against wall " << k << "\n";
				Line2D wall = room->getWalls()->at(k);
				if (stored_light_lines.at(i).intersects(wall))
				{
					// stored_light_lines.at(i).setColour(YELLOW);

					stored_light_lines.erase(stored_light_lines.begin() + i);
					i--;
					std::cout << "Intersection detected between light line and wall!\n";
					// break;
				}
				else
				{
					stored_light_lines.at(i).setColour(BLUE);
				}
			}
		}
	}
	void draw() override
	{
		if (room && light)
		{
			room->draw();
			light->draw();
		}
		if (draw_light_lines)
		{
			for (auto &line : stored_light_lines)
			{
				line.extrapolate(10).draw();
			}
			for(int i = 0; i < stored_light_lines.size() - 1; i++)
			{
				Point<float> a = stored_light_lines.at(i).getB();
				Point<float> b = stored_light_lines.at(i + 1).getB();
				Polygon poly(
					light->getPosition(),
					a,
					b,
					Color{255, 255, 0, 255});
				poly.draw();
			}
			
		}
	}

	Room *getRoom() const { return room; }
	Light *getLight() const { return light; }
	bool isInErrorState() const { return is_in_error_state; }

	std::string getType() override { return "LightBreakdown"; }
};