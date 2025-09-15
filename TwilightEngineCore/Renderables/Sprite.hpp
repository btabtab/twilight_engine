#pragma once

#include <raylib.h>

#include "../Point.hpp"
#include "RenderObject.hpp"

#include "TwilightTexture.hpp"

class Sprite : public RenderObject2D
{
	private:
	//Position goes from top left.
	Point<int> position;
	TwilightTexture* texture;
	int search_ID;
	public:
	Sprite(int texture_search_ID, Point<int> new_position):
	position(new_position)
	{
		search_ID = texture_search_ID;
		// std::cout << "search ID of : " << search_ID << "\n";
	}
	void move(Point<int> movement)
	{
		position = position + movement;
	}
	Point<int> getPosition()
	{
		return position;
	}
	int getSearchID()
	{
		return search_ID;
	}
	void setTexture(TwilightTexture* texture_to_use)
	{
		texture = texture_to_use;
	}
	void draw() override
	{
		DrawTexture(*texture->getTextureData(), position.getX(), position.getY(), RAYWHITE);
	}
	size_t getBytesConsumed() override
	{
		return sizeof(this);
	}
	std::string getType() override
	{
		return "sprite";
	}
};