#include "TwilightEngine.hpp"

TwilightEngine::TwilightEngine(int argc, char *argv[], Point<float> new_window_size, std::string new_name)
	: window_size(new_window_size), session_name(new_name)
{
	max_fps = 30;
	bool is_the_wizard_here = false;
	bool run_with_metrics_too = false;
	// Basic, non-dependant, arguments.
	for (int i = 0; i != argc; i++)
	{
		if (std::string(argv[i]) == "-wizard")
		{
			is_the_wizard_here = true;
			printf("Wizard found, running with the wizard...\n");
		}
	}
	// For loop to check for arguments that depend on other arguments.
	for (int i = 0; i != argc; i++)
	{
		if (is_the_wizard_here && std::string(argv[i]) == "-metrics")
		{
			run_with_metrics_too = true;
			printf("Running with Metrics Capture as well.\n");
		}
	}

	printf("Clearing Gifs...");
	system("rm -rf screenshots/gifs/*");
	system("rm -rf screenshots/*");
	system("mkdir -p resources/");
	wizard_panel = nullptr;
	is_wizard_present = is_the_wizard_here;
	if (is_wizard_present)
	{
		std::cout << "Running the application with the wizard :3\n";
		wizard_panel = new WizardPanel(run_with_metrics_too);
		wizard_panel->grabRenderObjectLists(renderer.getRenderObjects(), renderer.getRenderObjects3D());
	}
	emergency_exit = false;
}
TwilightEngine::~TwilightEngine()
{
	for (int i = 0; i != renderer.getRenderObjects()->size(); i++)
	{
		delete renderer.getRenderObjects()->at(i);
	}
	renderer.getRenderObjects()->clear();

	for (int i = 0; i != renderer.getRenderObjects3D()->size(); i++)
	{
		delete renderer.getRenderObjects3D()->at(i);
	}
	renderer.getRenderObjects3D()->clear();
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

	if (wizard_panel)
	{
		wizard_panel->loadWizardTexture();
		wizard_panel->produceRenderTextures();
	}

	userSetup();

	bool is_screenshot_being_taken = false;

	while (!WindowShouldClose() || emergency_exit)
	{
		// system("clear");

		frame_ID++;

		bool should_i_pause_updates = false;
		if (wizard_panel)
		{
			should_i_pause_updates = !wizard_panel->isWizardOpen() || wizard_panel->getWasStepIssued();
		}
		if (should_i_pause_updates)
		{
			// std::cout << "updating engine...\n";
			if (!renderer.getRenderObjects3D()->empty())
			{
				for (size_t i = 0; i < renderer.getRenderObjects3D()->size(); i++)
				{
					if (renderer.getRenderObjects3D()->at(i))
					{
						renderer.getRenderObjects3D()->at(i)->update();
					}
				}
			}

			if (!renderer.getRenderObjects()->empty())
			{
				for (size_t i = 0; i < renderer.getRenderObjects()->size(); i++)
				{
					if (renderer.getRenderObjects()->at(i))
					{
						renderer.getRenderObjects()->at(i)->update();
					}
				}
			}

			handleDeletionRequests();

			if (wizard_panel)
			{
				wizard_panel->updateMetrics();
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
			wizard_panel->updateMetrics();
		}

		if (IsKeyPressed(KEY_V))
		{
			system("clear");
		}

		if (wizard_panel)
		{
			if (wizard_panel->callForGifRecording())
			{
				std::cout << "GIF recording started...\n";
				startGIFRecording("UserGIFRecording");
			}
			if (wizard_panel->callForScreenshot())
			{
				is_screenshot_being_taken = true;
			}
		}
		if (is_screenshot_being_taken)
		{
			std::string end_path_name = "screenshots/" + std::to_string(frame_ID) + ".png";
			std::cout << "Screenshot\n";

			TakeScreenshot(end_path_name.c_str());
			is_screenshot_being_taken = false;
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

void TwilightEngine::handleDeletionRequests()
{
	for (int i = renderer.getRenderObjects()->size() - 1; i >= 0; i--)
	{
		if (renderer.getRenderObjects()->at(i)->wasDeleteRequested())
		{
			delete renderer.getRenderObjects()->at(i);
			renderer.getRenderObjects()->erase(renderer.getRenderObjects()->begin() + i);
		}
	}

	for (int i = renderer.getRenderObjects3D()->size() - 1; i >= 0; i--)
	{
		if (renderer.getRenderObjects3D()->at(i)->wasDeleteRequested())
		{
			delete renderer.getRenderObjects3D()->at(i);
			renderer.getRenderObjects3D()->erase(renderer.getRenderObjects3D()->begin() + i);
		}
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