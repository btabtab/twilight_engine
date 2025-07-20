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
	LineMap(std::vector<Point<float>> points, bool make_lines_floating)
	{
		layer = Layers::BACK;
		colour = RED; // Default color for lines

		if(points.size() < 2)
		{
			std::cerr << "Error: Not enough points to create a line map.\n";
			return;
		}
		if(make_lines_floating)
		{
			for(size_t i = 0; i < points.size(); i += 2)
			{
				lines.emplace_back(
					Point<float>(points[i].getX(), points[i].getY()),
					Point<float>(points[i + 1].getX(), points[i + 1].getY()),
					WHITE
				);
				lines.back().cardinalise(Axis::VERTICAL); // Ensure lines are facing the same direction
				// lines.at(i).cardinalise();
			}
		}
		else
		{
			points.push_back(points[0]); // Close the loop
			for(size_t i = 0; i < points.size() - 1; i++)
			{
				lines.emplace_back(points[i], points[i + 1], WHITE);
				// lines.at(i).cardinalise();
			}
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
		return;
		for(int i = 0; i != lines.size(); i++)
		{
			lines.at(i).draw();
		}
		// lines.at(0).extrapolate(3.f).draw(); // Example of extrapolation
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

	void setSplitter(Line2D new_split_line)
	{
		split_line = new_split_line;
	}

	virtual void draw() override
	{
		return;
		split_line.draw();
		// DrawLine(position.getX(), 0, position.getX(), GetScreenHeight(), RED);
	}
	virtual void update() override
	{
		position.setX(GetMouseX());
		position.setY(GetMouseY());
		// split_line = 
		// split_line = Line2D(
		// 					Point<float>(
		// 								position.getX() - 25,
		// 								0),
		// 					Point<float>(
		// 								position.getX() + 25,
		// 								GetScreenHeight()),
		// 								GREEN
		// 					);
	}
	virtual std::string getType() override
	{
		return "Splitter";
	}
};

/*
	This contains the result of each split
	in the BSP process.
*/
class BSPNode: public TwilightNode
{
private:
	Line2D splitter;
	std::vector<Line2D> front;
	std::vector<Line2D> back;
	//The previous node in the BSP tree.
	BSPNode* parent;
	//The nodes containing splits for the front lines.
	BSPNode* front_child = nullptr;
	//The nodes containing splits for the back lines.
	BSPNode* back_child = nullptr;
protected:
public:
	BSPNode(Line2D new_splitter, BSPNode* new_parent = nullptr):
	TwilightNode(0), splitter(new_splitter), parent(new_parent)
	{
		layer = Layers::MIDDLE;
	}
	
	void setFrontChild(BSPNode* child)
	{
		front_child = child;
	}
	void setBackChild(BSPNode* child)
	{
		back_child = child;
	}
	BSPNode* getFrontChild()
	{
		return front_child;
	}
	BSPNode* getBackChild()
	{
		return back_child;
	}

	void addFront(Line2D line)
	{
		front.push_back(line);
		front.back().setColour((Color){255, 0, 0, 255}); // Set back lines to blue
	}
	void addBack(Line2D line)
	{
		back.push_back(line);
		back.back().setColour((Color){0, 0, 255, 255}); // Set back lines to blue
	}
	
	virtual void draw() override
	{
		splitter.draw();
		for(auto& line : front)
		{
			line.draw();
		}
		for(auto& line : back)
		{
			line.draw();
		}
	}
	virtual void update() override
	{
		// Update logic if needed
	}
	virtual std::string getType() override
	{
		return "BSPNode";
	}
	
	std::vector<Line2D> getFrontLines() const
	{
		return front;
	}
	std::vector<Line2D> getBackLines() const
	{
		return back;
	}
	Line2D getSplitter() const
	{
		return splitter;
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
	std::vector<Line2D> left_lines;
	std::vector<Line2D> right_lines;

	Point<float> intersection_center;

	std::vector<Point<float>> split_positions;

	//The current BSPNode that this stage is working on.
	BSPNode* bsp_node = nullptr;

	bool was_thing_done;
public:
	SplitStage(LineMap* new_line_map, Splitter* new_splitter):
	TwilightNode(0),  line_map(new_line_map), splitter(new_splitter),
	intersection_center(0, 0)
	{
		was_thing_done = false;
	}
	
	virtual void draw() override
	{
		if(bsp_node != nullptr)
		{
			bsp_node->draw();
		}
		return;
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
				//Get the intersection points
				Point<float> intersection = line.getIntersectionPoint(splitter->getSplitter());
				//This sets the points for each split position.
				split_positions.push_back(intersection);

				intersection_center = intersection_center.midpoint(split_positions);
				left_lines.push_back(Line2D(
					Point<float>(line.getA().getX(), line.getA().getY()),
					intersection,
					(Color){255, 0, 0, 255}
				));
				right_lines.push_back(Line2D(
					intersection,
					Point<float>(line.getB().getX(), line.getB().getY()),
					(Color){0, 0, 255, 255}
				));
			}
		}
		
		//If the BSP node is null, then create it.
		if(
			bsp_node == nullptr
			&&
			(
				0 < left_lines.size()
				||
				0 < right_lines.size()
			)
			)
		{
			//Populate the BSPNode with the splitter and the lines.
			bsp_node = new BSPNode(splitter->getSplitter());
			bsp_node->addFront(left_lines.back());
			bsp_node->addBack(right_lines.back());
		}
	}
	virtual std::string getType() override
	{
		return "SplitStage";
	}
};