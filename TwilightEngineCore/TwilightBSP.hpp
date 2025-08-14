#pragma once
#include <vector>
#include <string>
#include "TwilightNode.hpp"
#include "Renderables/Line2D.hpp"
#include "Renderables/Polygon.hpp"
#include "Renderables/Plane.hpp"

/*
	I'm being honest with this...
	My entire approach on this is
	based pretty much exclusively
	on the wikipedia page for
	Binary Space Partitioning...

	Even down to the demo lines.
	https://en.wikipedia.org/wiki/Binary_space_partitioning

	Also probably some youtube videos at some point.
*/

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

// Helper function to compute signed distance from point to line (Ax + By + C = 0) // document
inline float signedDistance(const Line2D &line, const Point<float> &p) // document
{																	   // document
	float x1 = line.getA().getX(), y1 = line.getA().getY();			   // document
	float x2 = line.getB().getX(), y2 = line.getB().getY();			   // document
	float A = y2 - y1;												   // document
	float B = x1 - x2;												   // document
	float C = x2 * y1 - y2 * x1;									   // document
	return A * p.getX() + B * p.getY() + C;							   // document
} // document

class BSPNode : public TwilightNode
{
private:
	BSPNode *front_child;
	BSPNode *back_child;
	BSPNode *parent;

	Line2D splitting_line;
	// Lines that are "infront" of the split.
	std::vector<Line2D> front_lines;
	// Lines that are "behind" the split.
	std::vector<Line2D> back_lines;

	// This doesn't get set later on, so a "Setter" is not needed.
	int depth;

	/*
		This will be true if the node is an end
		point, basically just a line rlly.

		LEAF == NO CHILDREN, at ALL.
		!!! DO NOT OPERATE ON A LEAF NODE !!!
	*/
	bool is_leaf;
	Line2D leaf_line;

public:
	BSPNode(Line2D new_splitting_line, bool leaf = false, int new_depth = 0, BSPNode *new_parent = nullptr)
		: TwilightNode(), splitting_line(new_splitting_line.extrapolate(10.0f)), is_leaf(leaf), front_child(nullptr), back_child(nullptr),
		  leaf_line()
	{
		depth = new_depth;
		front_child = nullptr;
		back_child = nullptr;
		splitting_line.setColour((Color){30, 30, 30, 75});
		// splitting_line.getColour().a = 0xFF >> 1; // Semi-transparent
		parent = new_parent;
	}
	BSPNode *getParent()
	{
		return parent;
	}
	BSPNode *getTopParent()
	{
		BSPNode *ret = this;

		while (ret != nullptr)
		{
			if (ret->parent == nullptr)
			{
				return ret;
			}
		}
		return this;
	}

	int getDepth()
	{
		return depth;
	}
	bool isLeaf()
	{
		return is_leaf;
	}

	void dumpNodeAsText()
	{
		std::cout << this << " Depth: " << std::to_string(this->depth) << "\n\t front lines: [" << front_lines.size() << "] back lines: [" << back_lines.size() << "]\n";
	}
	void dumpChildrenAsText()
	{
		if (front_child)
		{
			front_child->dumpChildrenAsText();
		}
		else
		{
			dumpNodeAsText();
		}

		if (back_child)
		{
			back_child->dumpChildrenAsText();
		}
		else
		{
			dumpNodeAsText();
		}
	}
	void dumpTreeAsText()
	{
	}

	void setFrontChild(BSPNode *child) { front_child = child; }
	void setBackChild(BSPNode *child) { back_child = child; }

	BSPNode *getFrontChild() { return front_child; }
	BSPNode *getBackChild() { return back_child; }
	BSPNode *getChildBasedOnSide(Side side)
	{
		if (side == Side::FRONT)
		{
			return getFrontChild();
		}
		return getBackChild();
	}

	void eliminateAllChildren()
	{
		if (front_child)
		{
			front_child->eliminateAllChildren();
			delete front_child;
			front_child = nullptr;
			std::cout << "front_child deleted...\n";
		}

		if (back_child)
		{
			back_child->eliminateAllChildren();
			delete back_child;
			back_child = nullptr;
			std::cout << "back_child deleted...\n";
		}
	}

	void eliminateChild(Side side)
	{
		if (side == Side::FRONT)
		{
			front_child->eliminateAllChildren();
			delete front_child;
		}

		if (side == Side::BACK)
		{
			back_child->eliminateAllChildren();
			delete back_child;
		}
	}

	BSPNode *birthNewChild(Side side)
	{
		if (is_leaf)
		{
			return nullptr;
		}
		std::cout << "Birthing a new child with depth of: " << depth + 1 << "\n";
		if (side == Side::FRONT)
		{
			if (front_child)
			{
				std::cout << "front_child already exists, giving it back to you.\n";
				return front_child;
			}
			std::cout << "\t\tfront_lines.size() = " << front_lines.size() << " out of " << back_lines.size() + front_lines.size() << "\n";

			if (front_lines.empty())
			{
				return nullptr;
			}
			front_child = new BSPNode(front_lines.at(0), false, depth + 1, this);
			std::vector<Line2D> remaining_lines = front_lines;
			remaining_lines.erase(remaining_lines.begin()); // Remove the splitting line
			front_child->splitLines(remaining_lines);
			return front_child;
		}
		if (back_child)
		{
			std::cout << "back_child already exists, giving it back to you.\n";
			return back_child;
		}
		std::cout << "\t\tback_lines.size() - 1" << back_lines.size() << " out of " << back_lines.size() + front_lines.size() << "\n";
		if (back_lines.size() == 0)
		{
			std::cout << "\n";
			std::cerr << "[back_lines.size() == 0]\nIn:\n\tBSPNode *birthNewChild(Side side)\nBelonging to: " << this << "\n";
			dumpChildrenAsText();
			std::cout << "\n";
			return nullptr;
		}
		back_child = new BSPNode(back_lines.at(0), false, depth + 1, this);
		// back_lines.pop_back();
		// back_lines.erase(back_lines.begin() + back_lines.size() / 3); // document
		back_child->splitLines(back_lines);
		return back_child;
	}

	void splitLines(std::vector<Line2D> lines)
	{
		std::cout << "Lines = " << lines.size() << "\n";
		if (lines.size() == 0)
		{
			std::cout << "0 lines to cut?\n";
			return;
		}
		if (lines.size() == 1)
		{
			std::cout << "Leaf found...";
			leaf_line = lines.back();
			is_leaf = true;
			return;
		}
		if (lines.size() == 2)
		{
			// Determine which side each line is on
			int front_count = 0, back_count = 0;
			std::vector<Line2D> front, back;
			for (auto &line : lines)
			{
				float dA = signedDistance(splitting_line, line.getA());
				float dB = signedDistance(splitting_line, line.getB());
				if (dA >= 0 && dB >= 0)
				{
					front.push_back(line);
					front_count++;
				}
				else if (dA <= 0 && dB <= 0)
				{
					back.push_back(line);
					back_count++;
				}
				else
				{
					// Line crosses the split, treat as split
					Point<float> intersection_point = splitting_line.getIntersectionPoint(line);
					if (dA >= 0)
					{
						front.push_back(Line2D(line.getA(), intersection_point, line.getColour()));
						back.push_back(Line2D(intersection_point, line.getB(), line.getColour()));
					}
					else
					{
						back.push_back(Line2D(line.getA(), intersection_point, line.getColour()));
						front.push_back(Line2D(intersection_point, line.getB(), line.getColour()));
					}
				}
			}

			// If both lines are on the same side, make a leaf for each
			if (front.size() == 2 && back.size() == 0)
			{
				// Both lines in front
				is_leaf = true;
				leaf_line = front[0];
				// Optionally, handle the second line (could create a sibling node or store both)
				return;
			}
			else if (back.size() == 2 && front.size() == 0)
			{
				// Both lines in back
				is_leaf = true;
				leaf_line = back[0];
				// Optionally, handle the second line
				return;
			}
			else if (front.size() == 1 && back.size() == 1)
			{
				// One line on each side, create two leaf nodes
				front_lines.clear();
				back_lines.clear();
				front_lines.push_back(front[0]);
				back_lines.push_back(back[0]);
				return;
			}
			else
			{
				// If splitting doesn't reduce, force leaf creation to avoid infinite recursion
				is_leaf = true;
				leaf_line = lines[0];
				return;
			}
		}

		splitting_line.setColour(PURPLE);				 // document
		Color front_colour = splitting_line.getColour(); // document
		Color back_colour = splitting_line.getColour();	 // document

		front_colour.r /= 1.5; // document
		back_colour.b /= 1.5;  // document

		Axis side_to_cardinalise_for = splitting_line.getGradient();						 // document
		for (auto &line : lines)															 // document
		{																					 // document
			Line2D front_line;																 // document
			Line2D back_line;																 // document
			line.cardinalise(side_to_cardinalise_for);										 // document
			if (splitting_line.intersects(line))											 // document
			{																				 // document
				Point<float> intersection_point = splitting_line.getIntersectionPoint(line); // document

				// Swap these if your convention is reversed
				if (signedDistance(splitting_line, line.getA()) >= 0)
				{																			// document
					front_line = Line2D(line.getA(), intersection_point, line.getColour()); // document
					back_line = Line2D(intersection_point, line.getB(), line.getColour());	// document
				}
				else
				{																			// document
					back_line = Line2D(line.getA(), intersection_point, line.getColour());	// document
					front_line = Line2D(intersection_point, line.getB(), line.getColour()); // document
				}
			} // document
			else														// document
			{															// document
				float dA = signedDistance(splitting_line, line.getA()); // document
				float dB = signedDistance(splitting_line, line.getB()); // document

				if (dA >= 0 && dB >= 0) // document
				{						// document
					front_line = line;	// document
				} // document
				else if (dA <= 0 && dB <= 0) // document
				{							 // document
					back_line = line;		 // document
				} // document
				// If endpoints are on opposite sides, this should not happen here // document
			} // document
			if (front_line.getA() != front_line.getB())
			{										// document
				front_line.setColour(front_colour); // document
				front_lines.push_back(front_line);	// document
			} // document
			if (back_line.getA() != back_line.getB())
			{									  // document
				back_line.setColour(back_colour); // document
				back_lines.push_back(back_line);  // document
			} // document
		} // document
		splitting_line.setColour((Color){200, 122, 255, 255 / 2}); // document
	} // document

	void draw() override
	{
		if (is_leaf)
		{
			leaf_line.draw();
			DrawText((std::to_string(depth) + ", leaf").c_str(), leaf_line.getMidPoint().getX(), leaf_line.getMidPoint().getY(), 10, WHITE);
			return;
		}
		else
		{
			// splitting_line.draw();
			DrawText(
				(std::to_string(depth) + " splitter").c_str(),
				splitting_line.getMidPoint().getX(),
				splitting_line.getMidPoint().getY() + 20,
				10,
				(Color){255, 100, 255, 255 >> 1});
		}
		if (front_child)
		{
			front_child->draw();
		}
		else
		{
			int line_index = 0;
			for (auto line : front_lines)
			{
				DrawText((std::to_string(depth) + ", " + std::to_string(line_index)).c_str(), line.getMidPoint().getX(), line.getMidPoint().getY(), 10, WHITE);
				line.draw();
				line_index++;
			}
		}

		if (back_child)
		{
			back_child->draw();
		}
		else
		{
			int line_index = 0;
			for (auto line : back_lines)
			{
				DrawText((std::to_string(depth) + ", " + std::to_string(line_index)).c_str(), line.getMidPoint().getX(), line.getMidPoint().getY(), 10, WHITE);
				line.draw();
				line_index++;
			}
		}
	}

	void grow()
	{
		// Don't do anything on a leaf.
		if (is_leaf && getParent()->front_child && getParent()->back_child)
		{
			if (
				getParent()->front_child->is_leaf &&
				getParent()->back_child->is_leaf)
			{
				if (getParent())
				{
					if (getParent()->getParent())
					{
						getParent()->getParent()->grow();
					}
				}
			}
		}

		if (is_leaf)
		{
			getParent()->grow();
			return;
		}

		if (!front_child)
		{
			std::cout << "\t\tGrowing Front Node...\n";
			front_child = birthNewChild(Side::FRONT);
			if (front_child != nullptr)
			{
				front_child->grow();
			}
		}
		if (!back_child)
		{
			std::cout << "\t\tGrowing Back Node...\n";
			back_child = birthNewChild(Side::BACK);
			if (back_child != nullptr)
			{
				back_child->grow();
			}
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