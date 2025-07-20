#pragma once

#include "Line2D.hpp"
#include "../Vectors.hpp"
#include <vector>

class Polygon: public RenderObject
{
private:
    std::vector<Line2D> edges;

public:
    Polygon(const std::vector<Point<float>>& points)
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

    void draw() override
    {
        for (int i = 0; i < edges.size(); ++i)
        {
            edges.at(i).draw();
        }
    }

    void cardinalise()
    {
        for(size_t i = 0; i < edges.size(); ++i)
        {
            edges.at(i).cardinalise();
        }
    }

    const std::vector<Line2D>& getEdges() const
    {
        return edges;
    }
};