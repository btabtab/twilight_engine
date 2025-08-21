#pragma once
#include <raylib.h>
#include "RenderObject.hpp"

class RenderObject3D: public RenderObject
{
private:
    bool is_drawn_before_2D;
public:
	RenderObject3D(bool new_is_drawn_before_2D = true)
    {
        is_drawn_before_2D = new_is_drawn_before_2D;
    }
    bool getIfDrawnPre2D()
    {
        return is_drawn_before_2D;
    }
};