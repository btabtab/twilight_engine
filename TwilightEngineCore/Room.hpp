#pragma once

#include "Renderables/RenderObject.hpp"
#include "Renderables/Line2D.hpp"

/*
	This is going to basically be a wrapper
	for a vector of 2D lines.
*/
class Room : public RenderObject
{
private:
	std::vector<Line2D> walls;
public:
	Room(std::vector<Line2D> new_walls = {}) : walls(new_walls) {}
	void addWall(Line2D wall)
	{
		walls.push_back(wall);
	}
	void addWall(Point<float> a, Point<float> b, Color colour)
	{
		walls.push_back(Line2D(a, b, colour));
	}
	std::vector<Line2D>* getWalls()
	{
		return &walls;
	}
	void draw() override
	{
		for (auto& wall : walls)
		{
			wall.draw();
		}
	}
	std::string getType() override { return "Room"; }
};
