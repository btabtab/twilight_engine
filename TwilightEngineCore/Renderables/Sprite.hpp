#include <raylib.h>

#include "../Point.hpp"
#include "RenderObject.hpp"

class Sprite : public RenderObject2D
{
	private:
	//Position goes from top left.
	Point<int> position;
	Texture* texture;
	public:
	Sprite(Texture* texture_to_use, Point<int> new_position):
	position(new_position)
	{
		texture = texture_to_use;
	}
	void draw() override
	{
		DrawTexture(*texture, position.getX(), position.getY(), RAYWHITE);
	}
	size_t getBytesConsumed() override
	{
		return sizeof(this);
	}
	std::string getType() override
	{
		return "Sprite";
	}
};