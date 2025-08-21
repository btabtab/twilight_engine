#pragma once

#include "Line2D.hpp"
#include "../Point.hpp"
#include <vector>

class Polygon: public RenderObject
{
private:
	std::vector<Line2D> edges;

public:
	Polygon(std::vector<Point<float>> points)
	{
		if (points.size() < 3)
		{
			throw std::invalid_argument("A polygon must have at least 3 points.");
		}

		for (size_t i = 0; i < points.size(); ++i)
		{
			Point<float> start = points[i];
			Point<float> end = points[(i + 1) % points.size()];
			edges.emplace_back(start, end, WHITE);
		}
	}
	Polygon(std::vector<Line2D> new_edges)
	{
		if(new_edges.size() < 3)
		{
			return;
		}
		edges = new_edges;
	}
	void draw() override
	{
		Vector2 points_for_bezier[edges.size() * 2];
		for(int i = 0; i != edges.size() * 2; i += 2)
		{
			points_for_bezier[i] = {edges.at(i / 2).getA().getX(), edges.at(i / 2).getA().getY()};
			points_for_bezier[i+1] = {edges.at(i / 2).getB().getX(), edges.at(i / 2).getB().getY()};
		}
		// for(int i = 0; i != points_for_bezier->size(); i += 3)
		{
			DrawTriangleStrip(
							points_for_bezier,
							edges.size() * 2,
							LIME
						);
		}
		// for (int i = 0; i < edges.size(); ++i)
		// {
		//     edges.at(i).draw();
		// }
		
	}

	void cardinalise()
	{
		for(size_t i = 0; i < edges.size(); ++i)
		{
			edges.at(i).cardinalise(Axis::HORIZONTAL);
		}
	}

	const std::vector<Line2D>& getEdges() const
	{
		return edges;
	}
};