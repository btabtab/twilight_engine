#pragma once
#include <vector>
#include "TwilightNode.hpp"
#include "Renderables/Line2D.hpp"
#include "Renderables/Polygon.hpp"
#include "Renderables/Plane.hpp"

/*
	I nuked the previous code for reason technical debt
	reasons, it was written with a different approach
	and structure that couldn't have EVER fit with what
	was actually being worked towards.
*/

class LineSet : public TwilightNode
{
private:
	std::vector<Line2D> lines;

public:
	LineSet() : TwilightNode(), lines() {}
	LineSet(std::vector<Line2D> new_lines) : lines(new_lines) {}

	void addLine(Point<float> a, Point<float> b, Color colour)
	{
		lines.push_back(Line2D(a, b, colour));
	}
	void addLine(Line2D line) { lines.push_back(line); }
	void removeLine(int victim_index)
	{
		if (victim_index < 0 || victim_index >= lines.size())
		{
			std::cerr << "Invalid index for line removal: " << victim_index << std::endl;
			return;
		}
		lines.erase(lines.begin() + victim_index);
	}
	std::vector<Line2D> *getLines() { return &lines; }
	Line2D *getLine(int index)
	{
		if (index < 0 || index >= lines.size())
		{
			std::cerr << "Invalid index for line retrieval: " << index << std::endl;
			return nullptr;
		}
		return &lines.at(index);
	}
	virtual std::string getType() override { return "LineSet"; }
	void draw() override
	{
		for (auto &line : lines)
		{
			line.draw();
		}
	}
};

class BSPNode : public TwilightNode
{
private:
	BSPNode *front_child;
	BSPNode *back_child;
	Line2D splitting_line;
	// Lines that are "infront" of the split.
	std::vector<Line2D> front_lines;
	// Lines that are "behind" the split.
	std::vector<Line2D> back_lines;

	/*
		This will be true if the node is an end
		point, basically just a line rlly.

		LEAF == NO CHILDREN, at ALL.
		!!! DO NOT OPERATE ON A LEAF NODE !!!
	*/
	bool is_leaf;

public:
	BSPNode(Line2D new_splitting_line, bool leaf = false)
		: TwilightNode(), splitting_line(new_splitting_line.extrapolate(10.0f)), is_leaf(leaf), front_child(nullptr), back_child(nullptr)
	{
		front_child = nullptr;
		back_child = nullptr;
		splitting_line.setColour(WHITE);
		// splitting_line.getColour().a = 0xFF >> 1; // Semi-transparent
	}

	void setFrontChild(BSPNode *child) { front_child = child; }
	void setBackChild(BSPNode *child) { back_child = child; }

	BSPNode *getFrontChild() { return front_child; }
	BSPNode *getBackChild() { return back_child; }

	void eliminateAllChildren()
	{
		if(front_child)
		{
			front_child->eliminateAllChildren();
			delete front_child;
			front_child = nullptr;
			std::cout << "front_child deleted...\n";
		}

		if(back_child)
		{
			back_child->eliminateAllChildren();
			delete back_child;
			back_child = nullptr;
			std::cout << "back_child deleted...\n";
		}
	}

	void eliminateChild(Side side)
	{
		if(side == Side::FRONT)
		{
			front_child->eliminateAllChildren();
			delete front_child;
		}

		if(side == Side::BACK)
		{
			back_child->eliminateAllChildren();
			delete back_child;
		}
	}

	BSPNode* birthNewChild(Side side)
	{
		if (side == Side::FRONT)
		{
			if(front_child)
			{
				return front_child;
			}
			front_child = new BSPNode(front_lines.at(0), false);
			front_child->splitLines(front_lines);
			return front_child;
		}
		if(back_child)
		{
			return back_child;
		}
		back_child = new BSPNode(back_lines.at(1), false);
		back_child->splitLines(back_lines);
		return back_child;
	}

	void splitLines(std::vector<Line2D> lines)
	{
		splitting_line.setColour(PURPLE);
		Color front_colour = splitting_line.getColour(); // Semi-transparent red
		Color back_colour = splitting_line.getColour();// Semi-transparent blue

		front_colour.r /= 1.5;
		back_colour.b /= 1.5;

		Axis side_to_cardinalise_for = splitting_line.getGradient();
		for (auto &line : lines)
		{
			Line2D front_line;
			Line2D back_line;
			line.cardinalise(Axis::VERTICAL);
			if (splitting_line.intersects(line))
			{
				Point<float> intersection_point = splitting_line.getIntersectionPoint(line);
				
				// If the intersection point is valid, we can split the line.
				// Create two new lines from the intersection point.
				front_line = line.getSplitLine(intersection_point, Side::FRONT);
				back_line = line.getSplitLine(intersection_point, Side::BACK);
				
				//If the splitting line doesn't intersect the extrapolated one up top
				//check if it is left or right


				// DrawCircle3D(intersection_point)

				// std::cout << ":^D\n";
			}
			else
			{

				if(
					line.getA().getX() < splitting_line.getA().getX()
					||
					line.getA().getY() < splitting_line.getA().getY()
					||
					line.getB().getX() < splitting_line.getB().getX()
					||
					line.getB().getY() < splitting_line.getB().getY()
					)
				{
					front_line = line;
				}
				else
				{
					back_line = line;
				}
				// std::cout << ":^(\n";
			}
			front_line.setColour(front_colour);
			back_line.setColour(back_colour);
			front_lines.push_back(front_line);
			back_lines.push_back(back_line);
		}
		front_lines.push_back(lines.at(0));
	}

	void draw() override
	{
		if(!front_child && !back_child)
		{
			splitting_line.draw();
			for (auto &line : front_lines)
			{
				line.draw();
			}
			for (auto &line : back_lines)
			{
				line.draw();
			}
		}
		// if (is_leaf)
		// {
		// 	return;
		// }
		if (front_child)
		{
			front_child->draw();
		}
		if (back_child)
		{
			back_child->draw();
		}
	}

	virtual void update() override
	{
		if (front_child)
		{
			front_child->update();
		}
		if (back_child)
		{
			back_child->update();
		}
	}
	virtual std::string getType() override { return "BSPNode"; }

	virtual ~BSPNode()
	{
		eliminateAllChildren();
	}
};