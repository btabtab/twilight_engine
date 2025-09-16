#pragma once

#include "Renderables/Sprite.hpp"
#include "TwilightEngine.hpp"

namespace CursorTextureIDs
{
	const std::string cursor_default_texture_string = "cursor_default_texture.png";
	const int cursor_default_texture = 0xF0;

	const std::string mouse_1_down_texture_string = "mouse_1_down_texture.png";
	const int mouse_1_down_texture = 0xF1;

	const std::string mouse_2_down_texture_string = "mouse_2_down_texture.png";
	const int mouse_2_down_texture = 0xF2;

	const std::string scroll_up_texture_string = "scroll_up_texture.png";
	const int scroll_up_texture = 0xF3;

	const std::string scroll_down_texture_string = "scroll_down_texture.png";
	const int scroll_down_texture = 0xF4;

	void loadTextures(TwilightEngine* engine)
	{
		engine->addTexture(
							CursorTextureIDs::cursor_default_texture_string,
							CursorTextureIDs::cursor_default_texture
							);
		engine->addTexture(
							CursorTextureIDs::mouse_1_down_texture_string,
							CursorTextureIDs::mouse_1_down_texture
							);
		engine->addTexture(
							CursorTextureIDs::mouse_2_down_texture_string,
							CursorTextureIDs::mouse_2_down_texture
							);
		engine->addTexture(
							CursorTextureIDs::scroll_up_texture_string,
							CursorTextureIDs::scroll_up_texture
							);
		engine->addTexture(
							CursorTextureIDs::scroll_down_texture_string,
							CursorTextureIDs::scroll_down_texture
							);
	}
}

class Cursor : public Sprite
{
private:
	
	int frames_until_default;
	bool is_left_click, is_right_click;
	bool is_scroll_up, is_scroll_down;

	Sprite* defualt_state;
	Sprite* mouse_1_down;
	Sprite* mouse_2_down;
	Sprite* scroll_down;
	Sprite* scroll_up;

	Sprite* current_sprite;

public:

	Cursor(TwilightEngine* engine):
	Sprite(0),
	defualt_state(	new Sprite(CursorTextureIDs::cursor_default_texture	)),
	mouse_1_down(	new Sprite(CursorTextureIDs::mouse_1_down_texture	)),
	mouse_2_down(	new Sprite(CursorTextureIDs::mouse_2_down_texture	)),
	scroll_down(	new Sprite(CursorTextureIDs::scroll_down_texture	)),
	scroll_up(		new Sprite(CursorTextureIDs::scroll_up_texture		))
	{
		current_sprite = defualt_state;
		frames_until_default = 0;

		std::cout << "Cursors\n";
		std::cout << "[ current | " << current_sprite << " ]\n";

		std::cout << "[ defualt_state | " << defualt_state << " ]\n";
		std::cout << "[ mouse_1_down | " << mouse_1_down << " ]\n";
		std::cout << "[ mouse_2_down | " << mouse_2_down << " ]\n";
		std::cout << "[ scroll_down | " << scroll_down << " ]\n";
		std::cout << "[ scroll_up | " << scroll_up << " ]\n";
	}

	~Cursor()
	{
		free(defualt_state);
		free(mouse_1_down);
		free(mouse_2_down);
		free(scroll_down);
		free(scroll_up);
	}
	void update() override
	{
		frames_until_default--;

		if(frames_until_default == 0)
		{
			current_sprite = defualt_state;
		}
	}
	void move(Point<int> movement) override
	{
		setPosition(Point<int>(GetMouseX(), GetMouseY()));
		current_sprite->setPosition(getPosition());
	}

	void handleInputs() override
	{
		is_left_click = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
		is_right_click = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
		is_scroll_down = false;
		is_scroll_up = false;
		if(
			is_left_click
			||
			is_left_click
			||
			is_scroll_down
			||
			is_scroll_up
			)
		{
			frames_until_default = 10;
		}

		if(is_left_click)
		{
			current_sprite = mouse_1_down;
			return;
		}
		if(is_right_click)
		{
			current_sprite = mouse_2_down;
			return;
		}
		if(is_scroll_up)
		{
			current_sprite = scroll_up;
			return;
		}
		if(is_scroll_down)
		{
			current_sprite = scroll_down;
			return;
		}
	}

	void draw() override
	{
		current_sprite->draw();
	}
	std::string getType() override
	{
		return "sprite";
	}
};