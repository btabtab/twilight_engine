#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Renderables/RenderObject.hpp"

#include "WizardPage.hpp"

class WizardPanel : public RenderObject
{
private:
	bool showing = false;
	std::vector<std::string> text_to_show;
	int current_page;
	std::vector<WizardPage*> pages;

	bool was_step_issued;

	bool is_he_here;
	Texture the_wizard_texture;

	bool request_gif_recording;

	std::vector<RenderObject*>* render_object_vector;
	std::vector<RenderObject3D*>* render_object_3D_vector;
	

public:
	WizardPanel()
	{
		was_step_issued = false;
		current_page = 0;
		std::cout << "\"Hello\" - The Wizard\n";
		pages.push_back(new WizardPage(&the_wizard_texture, "KeyBinds"));
		pages.back()->addText(std::string("L-ALT + H - Show/Hide wizard panel\n"));
		pages.back()->addText(std::string("L-ALT + Left - Next page\n"));
		pages.back()->addText(std::string("L-ALT + Right - Last page\n"));
		pages.back()->addText(std::string("L-ALT + O - SHOW HIM TO ME ! ! !\n"));
		pages.back()->addText(std::string("L-ALT + S - Step (useful if there is a window...)\n"));
		
		pages.back()->addText(std::string("L-ALT + G - start recording GIF\n"));

		pages.back()->addText(std::string("L-ALT + X + Y - Close Application\n"));

		pages.push_back(new WizardPage(&the_wizard_texture, "Window to see what's happening."));
		pages.back()->toggleHole();

		pages.push_back(new WizardPage(&the_wizard_texture, "Debug Information"));
		pages.back()->toggleDebugPage();

		pages.back()->addText("Framerate counter [?]");

		pages.back()->addText("2D object counts");
		pages.back()->addText("3D object counts");

	}
	void grabRenderObjectLists(std::vector<RenderObject*>* main_render_object_vector, std::vector<RenderObject3D*>* main_render_object_3D_vector)
	{
		render_object_vector = main_render_object_vector;
		render_object_3D_vector = main_render_object_3D_vector;
	}

	void loadWizardTexture()
	{
		//Loads the wizard texture.
		the_wizard_texture = LoadTexture("HIM_THE_WIZARD.png");
	}
	void addTextToPanel()
	{
	}
	
	void updateDebugPage()
	{
		if(!pages.at(current_page)->isDebugPage())
		{
			return;
		}
		pages.at(current_page)->getText()->at(0) = "Framerate: " + std::to_string(GetFPS());
		pages.at(current_page)->getText()->at(1) = "2D render objects: " + std::to_string(render_object_vector->size());
		pages.at(current_page)->getText()->at(2) = "3D render objects: " + std::to_string(render_object_3D_vector->size());
	}

	void draw() override
	{
		if(!showing)
		{
			return;
		}
		if(pages.empty())
		{
			showing = false;
			return;
		}
		Point<int> screen(GetScreenWidth(), GetScreenHeight());

		if(pages.at(current_page)->isThereAHole())
		{
			DrawRectangle(0, 0, screen.getX(), 10, (Color){120, 200, 200, 128});
			DrawRectangle(0, screen.getY() - 10, screen.getX(), 10, (Color){120, 200, 200, 128});
		}
		else
		{
			DrawRectangle(0, 0, screen.getX(), screen.getY(), BLACK);
		}
		pages.at(current_page)->draw();
		// DrawText(((std::string)("FPS: " + GetFPS())).c_str(), screen.getX() - 30, screen.getY() - 30, 10, ORANGE;
		DrawText(
				((std::string)("Page: " + std::to_string(current_page + 1)) + "/" + std::to_string(pages.size())).c_str(),
				screen.getX() - 60,
				screen.getY() - 30,
				10,
				ORANGE
				);
	}

	bool isWizardOpen()
	{
		return showing;
	}

	void handleInputs()
	{
		bool is_alt_held_down = IsKeyDown(KEY_LEFT_ALT);
		bool was_hide_show_key_pressed = IsKeyPressed(KEY_H);
		bool was_step_key_pressed = IsKeyPressed(KEY_S);
		bool was_him_toggle_pressed = IsKeyPressed(KEY_O);
		bool was_next_page_pressed = IsKeyPressed(KEY_RIGHT);
		bool was_last_page_pressed = IsKeyPressed(KEY_LEFT);
		bool was_GIF_recording_started = IsKeyPressed(KEY_G);

		was_step_issued = false;

		if(is_alt_held_down && was_hide_show_key_pressed)
		{
			showing = !showing;
			std::cout << "Toggling Wizard Panel...\n";
		}
		if(is_alt_held_down && was_step_key_pressed)
		{
			was_step_issued = true;
		}
		if(is_alt_held_down && was_him_toggle_pressed)
		{
			pages.at(current_page)->summonOrUnsummonHim();
		}
		if(is_alt_held_down && was_next_page_pressed)
		{
			current_page++;
			if(pages.size() - 1 < current_page)
			{
				current_page = pages.size() - 1;
			}
		}
		if(is_alt_held_down && was_last_page_pressed)
		{
			current_page--;
			if(current_page < 0)
			{
				current_page = 0;
			}
		}
		if(is_alt_held_down && was_GIF_recording_started)
		{
			request_gif_recording = true;
		}
	}

	std::string getType() override { return "Wizard Panel"; }

	~WizardPanel()
	{
		std::cout << "\"Goodbye\" - The Wizard.\n";
	}

	bool getWasStepIssued()
	{
		return was_step_issued;
	}

	bool callForGifRecording()
	{
		bool ret = request_gif_recording;
		if(request_gif_recording)
		{
			showing = false;
		}
		request_gif_recording = false;
		return ret;
	}
};