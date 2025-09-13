#include "WizardPanel.hpp"
#include <algorithm>

WizardPanel::WizardPanel(bool run_with_twilight_metrics)
{
	was_step_issued = false;
	keep_running_when_open = false;

	current_page = 0;
	std::cout << "\"Hello\" - The Wizard\n";
	pages.push_back(new WizardPage(&the_wizard_texture, "KeyBinds"));
	pages.back()->addText(std::string("L-ALT + H - Show/Hide wizard panel\n"));
	pages.back()->addText(std::string("L-ALT + Left - Next page\n"));
	pages.back()->addText(std::string("L-ALT + Right - Last page\n"));
	pages.back()->addText(std::string("L-ALT + O - SHOW HIM TO ME ! ! !\n"));
	pages.back()->addText(std::string("L-ALT + S - Step (useful if there is a window...)\n"));

	pages.back()->addText(std::string("L-ALT + G - start recording GIF\n"));
	pages.back()->addText(std::string("L-ALT + C - take screenshot (.png)\n"));
	pages.back()->addText(std::string("L-ALT + D - Play while paused\n"));

	pages.back()->addText(std::string("L-ALT + X + Y - Close Application\n"));
	

	pages.push_back(new WizardPage(&the_wizard_texture, "Window to see what's happening."));
	pages.back()->toggleHole();

	if(run_with_twilight_metrics)
	{
		pages.push_back(new WizardDebugPage(render_object_vector, render_object_3D_vector));
	}
}

void WizardPanel::produceRenderTextures()
{
	for(auto page : pages)
	{
		if(page->getType() == "WizardDebugPage")
		{
			((WizardDebugPage*)page)->startRenderTextures();
		}
	}
}

void WizardPanel::grabRenderObjectLists(std::vector<RenderObject2D *> *main_render_object_vector, std::vector<RenderObject3D *> *main_render_object_3D_vector)
{
	render_object_vector = main_render_object_vector;
	render_object_3D_vector = main_render_object_3D_vector;

	for(auto page : pages)
	{
		if(page->getType() == "WizardDebugPage")
		{
			((WizardDebugPage*)page)->setVectors(main_render_object_vector, main_render_object_3D_vector);
		}
	}
}

void WizardPanel::loadWizardTexture()
{
}
void WizardPanel::addTextToPanel()
{
}

void WizardPanel::draw()
{
	if (!showing)
	{
		return;
	}
	if (pages.empty())
	{
		showing = false;
		return;
	}
	Point<int> screen(GetScreenWidth(), GetScreenHeight());

	if (pages.at(current_page)->isThereAHole())
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
		ORANGE);
	
	for(auto page : pages)
	{
		page->update();
	}
}

bool WizardPanel::isWizardOpen()
{
	return showing;
}

void WizardPanel::handleInputs()
{
	bool is_alt_held_down = IsKeyDown(KEY_LEFT_ALT);
	bool was_hide_show_key_pressed = IsKeyPressed(KEY_H);
	bool was_step_key_pressed = IsKeyPressed(KEY_S);
	bool was_him_toggle_pressed = IsKeyPressed(KEY_O);
	bool was_next_page_pressed = IsKeyPressed(KEY_RIGHT);
	bool was_last_page_pressed = IsKeyPressed(KEY_LEFT);
	bool was_GIF_recording_started = IsKeyPressed(KEY_G);
	bool was_screenshot_taken = IsKeyPressed(KEY_C);
	bool is_thunar_being_opened = IsKeyPressed(KEY_F);
	bool is_play_while_paused = IsKeyPressed(KEY_D);

	was_step_issued = false;

	if (is_alt_held_down && was_hide_show_key_pressed)
	{
		showing = !showing;
		std::cout << "Toggling Wizard Panel...\n";
	}
	if (is_alt_held_down && was_step_key_pressed)
	{
		was_step_issued = true;
	}
	if (is_alt_held_down && was_him_toggle_pressed)
	{
		pages.at(current_page)->summonOrUnsummonHim();
	}

	if(isWizardOpen())
	{
		if (is_alt_held_down && was_next_page_pressed)
		{
			current_page++;
			if (pages.size() - 1 < current_page)
			{
				current_page = pages.size() - 1;
			}
		}
		if (is_alt_held_down && was_last_page_pressed)
		{
			current_page--;
			if (current_page < 0)
			{
				current_page = 0;
			}
		}
	}

	if (is_alt_held_down && was_GIF_recording_started)
	{
		request_gif_recording = true;
	}
	if (is_alt_held_down && was_screenshot_taken)
	{
		request_screenshot = true;
	}
	if (is_alt_held_down && is_thunar_being_opened)
	{
		system("thunar .");
	}
	if (is_alt_held_down && is_play_while_paused)
	{
		keep_running_when_open = !keep_running_when_open;
	}
}

std::string WizardPanel::getType()
{
	return "Wizard Panel";
}

WizardPanel::~WizardPanel()
{
	std::cout << "\"Goodbye\" - The Wizard.\n";
}

bool WizardPanel::getWasStepIssued()
{
	return was_step_issued || keep_running_when_open;
}

bool WizardPanel::callForGifRecording()
{
	bool ret = request_gif_recording;
	if (request_gif_recording)
	{
		showing = false;
	}
	request_gif_recording = false;
	return ret;
}
bool WizardPanel::callForScreenshot()
{
	bool ret = request_screenshot;
	if (request_screenshot)
	{
		showing = false;
	}
	request_screenshot = false;
	return ret;
}