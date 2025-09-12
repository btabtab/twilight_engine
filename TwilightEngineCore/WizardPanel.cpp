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

	pages.push_back(new WizardPage(&the_wizard_texture, "Debug Information"));
	pages.back()->toggleDebugPage();

	pages.back()->addText("Framerate counter [?]");

	pages.back()->addText("2D object counts");
	pages.back()->addText("3D object counts");
	pages.back()->addText("Consumed Space");

	if(run_with_twilight_metrics)
	{
		twilight_metrics = new TwilightMetrics();
	}
}

void WizardPanel::produceRenderTexture()
{
	if(twilight_metrics)
	{
		metrics_grid_render_texture = LoadRenderTexture(GetScreenWidth() - 20, 200);
	}
}

void WizardPanel::grabRenderObjectLists(std::vector<RenderObject2D *> *main_render_object_vector, std::vector<RenderObject3D *> *main_render_object_3D_vector)
{
	render_object_vector = main_render_object_vector;
	render_object_3D_vector = main_render_object_3D_vector;
}

void WizardPanel::loadWizardTexture()
{
}
void WizardPanel::addTextToPanel()
{
}

void WizardPanel::updateDebugPage()
{
	if (!pages.at(current_page)->isDebugPage())
	{
		return;
	}
	pages.at(current_page)->getText()->at(0) = "Framerate: " + std::to_string(GetFPS());
	pages.at(current_page)->getText()->at(1) = "2D render objects: " + std::to_string(render_object_vector->size());
	pages.at(current_page)->getText()->at(2) = "3D render objects: " + std::to_string(render_object_3D_vector->size());

	pages.at(current_page)->getText()->at(3) = "Space consumed in MB: " + std::to_string((((float)getEngineMemoryUsage() / 1024.f) / 1024.f));
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
	if(pages.at(current_page)->isDebugPage())
	{
		drawTwilightMetricsGraph();
	}
	
	// DrawText(((std::string)("FPS: " + GetFPS())).c_str(), screen.getX() - 30, screen.getY() - 30, 10, ORANGE;
	DrawText(
		((std::string)("Page: " + std::to_string(current_page + 1)) + "/" + std::to_string(pages.size())).c_str(),
		screen.getX() - 60,
		screen.getY() - 30,
		10,
		ORANGE);
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

void WizardPanel::drawTwilightMetricsGraph()
{
	if(!twilight_metrics)
	{
		DrawText("TwilightMetrics not found...", 10, 50, 10, WHITE);
		return;
	}
	Point<int> metrics_box_top_left(10, 50);
	
	// Draw the render texture flipped to display properly
	Rectangle source = { 0.0f, 0.0f, (float)metrics_grid_render_texture.texture.width, -(float)metrics_grid_render_texture.texture.height };
	Rectangle dest = { (float)metrics_box_top_left.getX(), (float)metrics_box_top_left.getY(), (float)metrics_grid_render_texture.texture.width, (float)metrics_grid_render_texture.texture.height };
	Vector2 origin = { 0.0f, 0.0f };
	DrawTexturePro(metrics_grid_render_texture.texture, source, dest, origin, 0.0f, RAYWHITE);
}

/*
	1. Grab the value, colour, and label,
	2. Draw the line after accounting for dimensions..
*/
void WizardPanel::drawMetricsGridLine(float value_to_draw, std::string label, Color colour)
{
	Point<int> dimensions(metrics_grid_render_texture.texture.width, metrics_grid_render_texture.texture.height);
	
	value_to_draw = dimensions.getY() - value_to_draw;

	DrawLine(0, value_to_draw, dimensions.getX(), value_to_draw, BLUE);
	
	DrawText(
				label.c_str(),
				10,
				value_to_draw - 10,
				10,
				colour
						);
}

void WizardPanel::drawMetricsAsLines(std::vector<float>* vector_to_draw, Color colour, float divide_amount)
{
    if (vector_to_draw == nullptr || vector_to_draw->empty())
    {
        // If the vector is null or empty, there's nothing to draw.
        return;
    }

    Point<int> dimensions(metrics_grid_render_texture.texture.width, metrics_grid_render_texture.texture.height);

    Point<float> last_point(0, dimensions.getY());

    for (size_t i = 0; i < vector_to_draw->size(); ++i)
    {
        // Scale the value using divide_amount to ensure it fits within the grid's height.
        float scaled_value = vector_to_draw->at(i) / divide_amount;
        float value_to_draw = dimensions.getY() - std::clamp(scaled_value, 0.0f, (float)dimensions.getY());

        Point<float> new_point(
            // Scale x-coordinate to fit within the texture width.
            (static_cast<float>(dimensions.getX()) / vector_to_draw->size()) * i,
            value_to_draw
        );

        Line2D(
            last_point,
            new_point,
            colour
        ).draw();

        last_point = new_point;
    }
}

void WizardPanel::updateMetricsGrid()
{
	Point<int> dimensions(metrics_grid_render_texture.texture.width, metrics_grid_render_texture.texture.height);
	BeginTextureMode(metrics_grid_render_texture);
	ClearBackground(BLACK);

	Color hollow_green =
	(Color)
	{
		0,
		0xff,
		0,
		0xff >> 1
	};
	
	for(int x = 0; x <= dimensions.getX(); x += 10)
	{
		Line2D(
				Point<float>(x, 20),
				Point<float>(x, dimensions.getY()),
				hollow_green
							).draw();
	}
	for(int y = 20; y <= dimensions.getY(); y += 10)
	{
		Line2D(
				Point<float>(0, y),
				Point<float>(dimensions.getX(), y),
				hollow_green
							).draw();
	}

	float current_memory_usage_in_kilobytes = (getEngineMemoryUsage() / 1024.f);

	drawMetricsAsLines(twilight_metrics->getMemoryConsumedHistory(), RED, 1024);
	drawMetricsAsLines(twilight_metrics->getFramerateHistory(), ORANGE, 1);

	drawMetricsGridLine(
						current_memory_usage_in_kilobytes,
						"Current Memory Usage in KB: " + std::to_string(current_memory_usage_in_kilobytes),
						BLUE
						);
	
	drawMetricsGridLine(
						twilight_metrics->getAverageFramerate(),
						"Current Framerate: " + std::to_string(GetFPS()),
						GREEN
						);

	DrawText("TwilightMetrics:", 0, 0, 10, WHITE);

	EndTextureMode();
}