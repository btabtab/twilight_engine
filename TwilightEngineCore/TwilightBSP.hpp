#pragma once
#include <vector>
#include "TwilightNode.hpp"
#include "Renderables/Line2D.hpp"
#include "Renderables/Polygon.hpp"
#include "Renderables/Plane.hpp"

/*
	A set of lines before the BSP process
	is applied.
*/
class LineMap: public RenderObject
{
private:
	std::vector<Line2D> lines;
public:
	LineMap(std::vector<Point<float>> points)
	{
		points.push_back(points[0]); // Close the loop
		layer = Layers::BACK;
		colour = RED; // Default color for lines

		if(points.size() < 2)
		{
			std::cerr << "Error: Not enough points to create a line map.\n";
			return;
		}

		for(size_t i = 0; i < points.size() - 1; i++)
		{
			lines.emplace_back(points[i], points[i + 1], WHITE);
			// lines.at(i).cardinalise();
		}
	}
	LineMap(std::vector<Line2D> new_lines):
	lines(new_lines)
	{
		layer = Layers::BACK;
		colour = YELLOW; // Default color for lines
	}

	void draw() override
	{
		for(int i = 0; i != lines.size(); i++)
		{
			lines.at(i).draw();
		}
	}
	std::vector<Line2D> getLines()
	{
		return lines;
	}
};

class Splitter: public TwilightNode
{
private:
protected:
	Point<float> position;
	Line2D split_line;
public:
	Splitter():
	TwilightNode(0), position(Point<float>(0, 0)), split_line(Point<float>(0, 0), Point<float>(0, GetScreenHeight()), RED)
	{
		layer = Layers::FRONT;
	}

	Line2D getSplitter()
	{
		return split_line;
	}

	virtual void draw() override
	{
		split_line.draw();
		// DrawLine(position.getX(), 0, position.getX(), GetScreenHeight(), RED);
	}
	virtual void update() override
	{
		position.setX(GetMouseX());
		position.setY(GetMouseY());
		split_line = Line2D(
							Point<float>(
										position.getX() - 25,
										0),
							Point<float>(
										position.getX() + 25,
										GetScreenHeight()),
										GREEN
							);
	}
	virtual std::string getType() override
	{
		return "Splitter";
	}
};

/*
	SplitStage:
		This class contains the data for
		each part of a split, where the
		intersections are. The lines on
		the left, and the Lines on the right.
*/
class SplitStage: public TwilightNode
{
private:
protected:
	LineMap* line_map;
	Splitter* splitter;
	std::vector<Plane> left_lines;
	std::vector<Plane> right_lines;

	Point<float> intersection_center;

	std::vector<Point<float>> split_positions;
public:
	SplitStage(LineMap* new_line_map, Splitter* new_splitter):
	TwilightNode(0),  line_map(new_line_map), splitter(new_splitter),
	intersection_center(0, 0)
	{
	}
	
	virtual void draw() override
	{
		for(int i = 0; i != split_positions.size(); i++)
		{
			DrawCircleV((Vector2){split_positions.at(i).getX(), split_positions.at(i).getY()}, 5, RED);
		}
		
		//(Color){122, 75, 20, 255}
		DrawCircleV((Vector2){intersection_center.getX(), intersection_center.getY()}, 5, YELLOW);

		for(int i = 0; i != left_lines.size(); i++)
		{
			left_lines.at(i).draw();
		}
		for(int i = 0; i != right_lines.size(); i++)
		{
			right_lines.at(i).draw();
		}
		
	}
	virtual void update() override
	{
		split_positions.clear();
		left_lines.clear();
		right_lines.clear();

		for(int i = 0; i != line_map->getLines().size(); i++)
		{
			Line2D line = line_map->getLines().at(i);
			
			if(line.intersects(splitter->getSplitter()))
			{
				Point<float> intersection = line.getIntersectionPoint(splitter->getSplitter());
				split_positions.push_back(intersection);
				intersection_center = intersection_center.midpoint(split_positions);
				// left_lines.push_back(Line2D(
				// 	Point<float>(line.getA().getX(), line.getA().getY()),
				// 	intersection,
				// 	(Color){255, 0, 0, 255}
				// ));
				// right_lines.push_back(Line2D(
				// 	intersection,
				// 	Point<float>(line.getB().getX(), line.getB().getY()),
				// 	(Color){0, 0, 255, 255}
				// ));
			}
		}
	}
	virtual std::string getType() override
	{
		return "SplitStage";
	}
};