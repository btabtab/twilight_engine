#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
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

	! !
		Heavy Disclaimer - AI was used to help smooth out
		parts of the code and some comments it generated have stuck
		around, but I'll be working on rewriting most of the code
		myself so that it truly is my own BSP implementation.
	! !
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

// Helper function to compute signed distance from point to line (Ax + By + C = 0) // Written with AI assistance
inline float signedDistance(const Line2D &line, const Point<float> &p) // Written with AI assistance
{																	   // Written with AI assistance
	float x1 = line.getA().getX(), y1 = line.getA().getY();			   // Written with AI assistance
	float x2 = line.getB().getX(), y2 = line.getB().getY();			   // Written with AI assistance
	float A = y2 - y1;												   // Written with AI assistance
	float B = x1 - x2;												   // Written with AI assistance
	float C = x2 * y1 - y2 * x1;									   // Written with AI assistance
	return A * p.getX() + B * p.getY() + C;							   // Written with AI assistance
} // Written with AI assistance

// Simple struct for bounding box
class Bounds: public TwilightNode
{
private:
	std::vector<Line2D> edges;
	float minX, minY, maxX, maxY;
	Color color;
public:
	Bounds(float new_minX = 0, float new_minY = 0, float new_maxX = 0, float new_maxY = 0, Color c = WHITE)
		: minX(new_minX), minY(new_minY), maxX(new_maxX), maxY(new_maxY), color(c)
	{
		Point<float> tl(minX, minY);
		Point<float> tr(maxX, minY);
		Point<float> br(maxX, maxY);
		Point<float> bl(minX, maxY);
		edges.push_back(Line2D(tl, tr, color)); // Top
		edges.push_back(Line2D(tr, br, color)); // Right
		edges.push_back(Line2D(br, bl, color)); // Bottom
		edges.push_back(Line2D(bl, tl, color)); // Left
	}
	float getMinX() const { return minX; }
	float getMinY() const { return minY; }
	float getMaxX() const { return maxX; }
	float getMaxY() const { return maxY; }
	std::string getType() override { return "Bounds"; }
	void draw() override {
		for (auto& edge : edges) {
			edge.draw();
		}
	}
};

class BSPNode : public TwilightNode
{
private:
	BSPNode *front_child;
	BSPNode *back_child;
	BSPNode *parent;

	Line2D splitting_line;
	Line2D original_splitting_line;
	std::vector<Line2D> front_lines;
	std::vector<Line2D> back_lines;
	std::string node_label;

	int depth;

	bool is_leaf;
	std::vector<Line2D> leaf_lines;

public:
	// Returns the bounding box of all lines in this node (leaf)
	Bounds getBoundingBox(Color c = WHITE) {
		if (leaf_lines.empty()) return Bounds(0, 0, 0, 0, c);
		float minX = leaf_lines[0].getA().getX(), maxX = leaf_lines[0].getA().getX();
		float minY = leaf_lines[0].getA().getY(), maxY = leaf_lines[0].getA().getY();
		for (auto& line : leaf_lines) {
			float ax = line.getA().getX(), ay = line.getA().getY();
			float bx = line.getB().getX(), by = line.getB().getY();
			minX = std::min(minX, std::min(ax, bx));
			maxX = std::max(maxX, std::max(ax, bx));
			minY = std::min(minY, std::min(ay, by));
			maxY = std::max(maxY, std::max(ay, by));
		}
		return Bounds(minX, minY, maxX, maxY, c);
	}
	BSPNode(Line2D new_splitting_line, bool leaf = false, int new_depth = 0, BSPNode *new_parent = nullptr, std::string label = "root")
		: TwilightNode(), splitting_line(new_splitting_line.extrapolate(10.0f)), original_splitting_line(new_splitting_line), is_leaf(leaf), front_child(nullptr), back_child(nullptr),
		  leaf_lines(), node_label(label)
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
	void dumpEntireTreeAsText(std::string prefix = "", bool isLeft = false)
	{
		// Print current node
		std::cout << prefix;
		std::cout << (isLeft ? "├── " : "└── ");
		
		// Print node info
		if (is_leaf) {
			std::cout << "[LEAF] depth:" << depth << " lines: " << front_lines.size() + back_lines.size() << "\n";
		} else {
			std::cout << "[NODE] depth:" << depth 
					<< " front:" << front_lines.size() 
					<< " back:" << back_lines.size() << "\n";
		}

		// Prepare prefix for children
		std::string childPrefix = prefix + (isLeft ? "│   " : "    ");

		// Recursively print front child (left in the tree)
		if (front_child) {
			front_child->dumpEntireTreeAsText(childPrefix, true);
		}

		// Recursively print back child (right in the tree)
		if (back_child) {
			back_child->dumpEntireTreeAsText(childPrefix, false);
		}
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
		std::string label = (side == Side::FRONT) ? "left" : "right";
		if (side == Side::FRONT)
		{
			if (front_child)
			{
				return front_child;
			}
			if (front_lines.empty())
			{
				return nullptr;
			}
			front_child = new BSPNode(front_lines.at(0), false, depth + 1, this, label);
			std::vector<Line2D> remaining_lines = front_lines;
			remaining_lines.erase(remaining_lines.begin());
			front_child->splitLines(remaining_lines);
			return front_child;
		}
		if (back_child)
		{
			return back_child;
		}
		if (back_lines.size() == 0)
		{
			std::cout << "\n";
			std::cerr << "[back_lines.size() == 0]\nIn:\n\tBSPNode *birthNewChild(Side side)\nBelonging to: " << this << "\n";
			dumpChildrenAsText();
			std::cout << "\n";
			return nullptr;
		}
		back_child = new BSPNode(back_lines.at(0), false, depth + 1, this, label);
		back_child->splitLines(back_lines);
		return back_child;
	}

	void splitLines(std::vector<Line2D> lines)
	{
		if (lines.size() == 0)
		{
			std::cout << "0 lines to cut?\n";
			return;
		}
		if (lines.size() <= 2)
		{
			// Always make a leaf and include all lines and the splitting line
			is_leaf = true;
			leaf_lines.clear();
			for (auto &l : lines) leaf_lines.push_back(l);
			leaf_lines.push_back(original_splitting_line);
			return;
		}

		splitting_line.setColour(PURPLE);				 // Written with AI assistance
		Color front_colour = splitting_line.getColour(); // Written with AI assistance
		Color back_colour = splitting_line.getColour();	 // Written with AI assistance

		front_colour.r /= 1.5; // Written with AI assistance
		back_colour.b /= 1.5;  // Written with AI assistance

		Axis side_to_cardinalise_for = splitting_line.getGradient();						 // Written with AI assistance
		for (auto &line : lines)															 // Written with AI assistance
		{																					 // Written with AI assistance
			Line2D front_line;																 // Written with AI assistance
			Line2D back_line;																 // Written with AI assistance
			line.cardinalise(side_to_cardinalise_for);										 // Written with AI assistance
			if (splitting_line.intersects(line))											 // Written with AI assistance
			{																				 // Written with AI assistance
				Point<float> intersection_point = splitting_line.getIntersectionPoint(line); // Written with AI assistance

				// Swap these if your convention is reversed
				if (signedDistance(splitting_line, line.getA()) >= 0)
				{																			// Written with AI assistance
					front_line = Line2D(line.getA(), intersection_point, line.getColour()); // Written with AI assistance
					back_line = Line2D(intersection_point, line.getB(), line.getColour());	// Written with AI assistance
				}
				else
				{																			// Written with AI assistance
					back_line = Line2D(line.getA(), intersection_point, line.getColour());	// Written with AI assistance
					front_line = Line2D(intersection_point, line.getB(), line.getColour()); // Written with AI assistance
				}
			} // Written with AI assistance
			else														// Written with AI assistance
			{															// Written with AI assistance
				float dA = signedDistance(splitting_line, line.getA()); // Written with AI assistance
				float dB = signedDistance(splitting_line, line.getB()); // Written with AI assistance

				if (dA >= 0 && dB >= 0) // Written with AI assistance
				{						// Written with AI assistance
					front_line = line;	// Written with AI assistance
				} // Written with AI assistance
				else if (dA <= 0 && dB <= 0) // Written with AI assistance
				{							 // Written with AI assistance
					back_line = line;		 // Written with AI assistance
				} // Written with AI assistance
				// If endpoints are on opposite sides, this should not happen here // Written with AI assistance
			} // Written with AI assistance
			if (front_line.getA() != front_line.getB())
			{										// Written with AI assistance
				front_line.setColour(front_colour); // Written with AI assistance
				front_lines.push_back(front_line);	// Written with AI assistance
			} // Written with AI assistance
			if (back_line.getA() != back_line.getB())
			{									  // Written with AI assistance
				back_line.setColour(back_colour); // Written with AI assistance
				back_lines.push_back(back_line);  // Written with AI assistance
			} // Written with AI assistance
		} // Written with AI assistance
		splitting_line.setColour((Color){200, 122, 255, 255 / 2}); // Written with AI assistance

		// After splitting, check for single lines in front/back and leaf them
		if (front_lines.size() == 1 && !front_child)
		{
			front_child = new BSPNode(front_lines[0], true, depth + 1, this);
			front_child->leaf_lines.clear();
			front_child->leaf_lines.push_back(front_lines[0]);
			front_child->leaf_lines.push_back(original_splitting_line);
		}
		if (back_lines.size() == 1 && !back_child)
		{
			back_child = new BSPNode(back_lines[0], true, depth + 1, this);
			back_child->leaf_lines.clear();
			back_child->leaf_lines.push_back(back_lines[0]);
			back_child->leaf_lines.push_back(original_splitting_line);
		}
	} // Written with AI assistance

	void draw() override
	{
		// splitting_line.draw();
		if (is_leaf)
		{
			int line_index = 0;
			// Color logic: left = more red, right = more blue, deeper = more green, start white
			int base = 60;
			int maxDepth = 10; // You can adjust this if you know the max tree depth
			int green = std::min(255, base + depth * 40); // More drastic green
			int red = (node_label == "left") ? 255 : base;
			int blue = (node_label == "right") ? 255 : base;
			if (node_label == "root") { red = blue = 255; }
			Color popColor = { (unsigned char)red, (unsigned char)green, (unsigned char)blue, 255 };
			Color bboxColor = { (unsigned char)red, (unsigned char)green, (unsigned char)blue, 80 };
			for (auto &line : leaf_lines)
			{
				// std::cout << "\n\t\t\t" << leaf_lines.size() << " lines in leaf node.\n";
				// Start white, then pop color
				line.setColour(WHITE);
				line.draw();
				line.setColour(popColor);
				line.draw();
				DrawText((node_label + " " + std::to_string(depth) + ", leaf " + std::to_string(line_index)).c_str(), line.getMidPoint().getX(), line.getMidPoint().getY(), 10, popColor);
				// Draw a circle at the midpoint of each line
				DrawCircle((int)line.getMidPoint().getX(), (int)line.getMidPoint().getY(), 6, popColor);
				line_index++;
			}
			// Get bounding box and draw it
			// Bounds bboxWhite = getBoundingBox(WHITE);
			// Bounds bboxCol = getBoundingBox(bboxColor);
			// bboxWhite.draw();
			// bboxCol.draw();
			return;
		}
		else
		{
			DrawText(
				(node_label + " " + std::to_string(depth) + " splitter").c_str(),
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
		if (is_leaf) return;

		if (!front_child && !front_lines.empty())
		{
			std::cout << "\t\tGrowing Front Node...\n";
			front_child = birthNewChild(Side::FRONT);
			if (front_child) front_child->grow();
		}
		if (!back_child && !back_lines.empty())
		{
			std::cout << "\t\tGrowing Back Node...\n";
			back_child = birthNewChild(Side::BACK);
			if (back_child) back_child->grow();
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

	// Returns pointer to the node whose bounding box contains p, or nullptr if not found
	BSPNode* findNodeContainingPoint(const Point<float>& p) {
		// Always search children first
		if (front_child) {
			BSPNode* found = front_child->findNodeContainingPoint(p);
			if (found) return found;
		}
		if (back_child) {
			BSPNode* found = back_child->findNodeContainingPoint(p);
			if (found) return found;
		}
		// For leaf nodes, check bounding box
		if (is_leaf) {
			Bounds bbox = getBoundingBox();
			if (p.getX() >= bbox.getMinX() && p.getX() <= bbox.getMaxX() &&
				p.getY() >= bbox.getMinY() && p.getY() <= bbox.getMaxY()) {
				return this;
			}
		}
		return nullptr;
	}

	virtual ~BSPNode()
	{
		eliminateAllChildren();
	}
};