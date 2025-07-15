#pragma once
#include <vector>
#include "TwilightNode.hpp"
#include "Renderables/Line2D.hpp"
/*
	A set of lines before the BSP process
	is applied.
*/
class LineMap: public RenderObject
{
private:
	std::vector<Line2D> lines;
public:
	LineMap(std::vector<Vector<float>> points)
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
		}
	}
	LineMap(std::vector<Line2D> new_lines):
	lines(new_lines)
	{
		layer = Layers::BACK;
		colour = YELLOW// Default color for lines
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
	Vector<float> position;
	Line2D split_line;
public:
	Splitter():
	TwilightNode(0), position(Vector<float>(0, 0)), split_line(Vector<float>(0, 0), Vector<float>(0, GetScreenHeight()), RED)
	{
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
							Vector<float>(
										position.getX(),
										0),
							Vector<float>(
										position.getX(),
										GetScreenHeight()),
										GREEN
							);
	}
	virtual std::string getType() override
	{
		return "Splitter";
	}
};

class SplitStage: public TwilightNode
{
private:
protected:
	LineMap* line_map;
	Splitter* splitter;
	std::vector<Line2D> left_lines;
	std::vector<Line2D> right_lines;

	std::vector<Vector<float>> split_positions;
public:
	SplitStage(LineMap* new_line_map, Splitter* new_splitter):
	TwilightNode(0),  line_map(new_line_map), splitter(new_splitter)
	{
	}
	
	virtual void draw() override
	{
		for(int i = 0; i != split_positions.size(); i++)
		{
			DrawCircleV((Vector2){split_positions.at(i).getX(), split_positions.at(i).getY()}, 5, RED);
		}
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
				Vector<float> intersection = line.getIntersectionPoint(splitter->getSplitter());
				split_positions.push_back(intersection);
				left_lines.push_back(Line2D(
					Vector<float>(line.getA().getX(), line.getA().getY()),
					intersection,
					(Color){255, 0, 0, 255}
				));
				right_lines.push_back(Line2D(
					intersection,
					Vector<float>(line.getB().getX(), line.getB().getY()),
					(Color){0, 0, 255, 255}
				));
			}
		}
	}
	virtual std::string getType() override
	{
		return "SplitStage";
	}
};

class LineOrganiser: public LineMap
{
private:
protected:
public:
	LineOrganiser(std::vector<Line2D> new_lines):
	LineMap(new_lines)
	{
	}
	void organiseLines()
	{
	}
};