#include "TwilightEngine.hpp"

TwilightEngine::TwilightEngine(Point<float> new_window_size, std::string new_name, bool set_is_wizard_present) : window_size(new_window_size), session_name(new_name)
{
	wizard_panel = nullptr;
	is_wizard_present = set_is_wizard_present;
	if (is_wizard_present)
	{
		std::cout << "Running the application with the wizard :3\n";
		wizard_panel = new WizardPanel();
		wizard_panel->grabRenderObjectLists(renderer.getRenderObjects(), renderer.getRenderObjects3D());
	}
	emergency_exit = false;
	max_fps = 30;
}

void TwilightEngine::enter()
{
	frame_ID = 0;
	InitWindow(window_size.getX(), window_size.getY(), session_name.c_str());
	SetTargetFPS(max_fps);
	warnings_left = 10;
	errors_left = 0;
	has_started = true;
	system("clear");


	if(wizard_panel) {wizard_panel->loadWizardTexture();}

	userSetup();

	while (!WindowShouldClose() || emergency_exit)
	{
		frame_ID++;

		bool should_i_pause_updates = false;
		if (wizard_panel)
		{
			should_i_pause_updates = !wizard_panel->isWizardOpen() || wizard_panel->getWasStepIssued();
		}
		if (should_i_pause_updates)
		{
			if (!renderer.getRenderObjects3D()->empty())
			{
				for (int i = 0; i != renderer.getRenderObjects3D()->size(); i++)
				{
					renderer.getRenderObjects3D()->at(i)->update();
				}
			}

			for (int i = 0; i != renderer.getRenderObjects()->size(); i++)
			{
				if (!renderer.getRenderObjects()->empty())
				{
					renderer.getRenderObjects()->at(i)->update();
				}
			}
		}

		renderer.startDrawing();
		// DrawFPS(GetMouseX(), GetMouseY());
		renderer.drawContents();

		DrawText(frame_label.c_str(), 5, 5, 10, WHITE);

		if (wizard_panel)
		{
			wizard_panel->draw();
		}

		renderer.stopDrawing();

		if (wizard_panel)
		{
			wizard_panel->handleInputs();
			wizard_panel->updateDebugPage();
		}

		// --- INPUT POLLING SECTION ---
		if (IsKeyPressed(KEY_C))
		{
			TakeScreenshot(("screenshots/screenshot-" + std::to_string(frame_ID) + "-.png").c_str());
			std::cout << "Screenshot taken\n";
		}
		if (IsKeyPressed(KEY_V))
		{
			system("clear");
		}
		
		if(wizard_panel)
		{
			if (wizard_panel->callForGifRecording())
			{
				std::cout << "GIF recording started...\n";
				startGIFRecording("UserGIFRecording");
			}
		}
		if(wizard_panel)
		{
			if (wizard_panel->callForScreenshot())
			{
				std::cout << "Screenshot\n";
				TakeScreenshot((std::to_string(frame_ID) + ".png").c_str());
			}
		}
		recordGIFFrame();
		if (240 < GIF_frame_counter)
		{
			stopGIFRecording();
			std::cout << "...GIF recording stopped\n";
		}

		userLoop();

		// --- END INPUT POLLING SECTION ---
	}
}

void TwilightEngine::postError(std::string message)
{
	std::cout << "| Error | : [" << message << "]\n";
	if (errors_left == 0 || warnings_left == 0)
	{
		std::cout << "No Errors left to give, quitting program\n";
		emergency_exit = true;
	}
	errors_left--;
}

void TwilightEngine::postWarning(std::string message)
{
	std::cout << "| warning | : [" << message << "]\n";
	if (warnings_left == 0)
	{
		std::cout << "No Warnings left to give, quitting program\n";
		emergency_exit = true;
	}
	warnings_left--;
}

void TwilightEngine::startGIFRecording(std::string name)
{
	is_recording_gif = true;
	gif_name = name;
}
void TwilightEngine::stopGIFRecording()
{
	is_recording_gif = false;
	GIF_frame_counter = 0;
}
void TwilightEngine::recordGIFFrame()
{
	if (is_recording_gif)
	{
		char buf[4];
		sprintf(buf, "%03d", GIF_frame_counter);
		system(("mkdir -p screenshots/gifs/" + gif_name).c_str());
		TakeScreenshot(("screenshots/gifs/" + gif_name + "/" + std::string(buf) + ".png").c_str());
		std::cout << gif_name + " frame " << GIF_frame_counter << " recorded.\n";
		GIF_frame_counter++;
	}
}