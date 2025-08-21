#pragma once

#include <raylib.h>
#include <iostream>

#include "../Point.hpp"

enum class Layers
{
	/*
		This is for stuff that is to be drawn
		after everything else no matter what.
	*/
	UI,
	FRONT,
	MIDDLE,
	BACK,
};

class RenderObject
{
protected:
	//Used to make sure that certain things are drawn over/under each other.
	Layers layer;
	Color colour;
	/*
		Will be used for rendering sub
		objects for any BSP esque effects.
	*/
	RenderObject* sub_render_object;
public:
	RenderObject();
	RenderObject(Color new_colour);
	void setColour(Color new_colour);
	virtual void draw();
	virtual void update();
	Layers getLayer();
	Color getColour() const;

	//This handles updating the node and defines it's behaviour.
	virtual std::string getType() = 0;
	virtual ~RenderObject() = default;
};