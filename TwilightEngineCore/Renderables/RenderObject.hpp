#pragma once

#include <raylib.h>
#include <iostream>

#include "../TwilightNode.hpp"

#include "../Point.hpp"

enum class DrawLayer
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

class RenderObject2D : public TwilightNode
{
protected:
	//Used to make sure that certain things are drawn over/under each other.
	DrawLayer layer;
	Color colour;
	/*
		Will be used for rendering sub
		objects for any BSP esque effects.
	*/
	RenderObject2D* sub_render_object;
	bool is_visible;
public:
	RenderObject2D();
	RenderObject2D(Color new_colour);
	void setColour(Color new_colour);
	void toggleVisibility();
	bool isVisible() const;
	virtual void draw();
	void drawChildren();
	virtual void update() override;
	DrawLayer getLayer();
	Color getColour() const;

	//This handles updating the node and defines it's behaviour.
	virtual std::string getType() override
	{
		return "RawRenderObject2D";
	}
	virtual ~RenderObject2D() = default;

	virtual size_t getBytesConsumed() override
	{
		size_t ret = 0;
		ret += sizeof(*this);
		
		if(sub_render_object)
		{
			ret += sub_render_object->getBytesConsumed();
		}
		return ret;
	}
};