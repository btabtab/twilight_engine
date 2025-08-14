#include "TwilightEngine.hpp"

TwilightEngine::TwilightEngine(Point<float> new_window_size, std::string new_name):
window_size(new_window_size), session_name(new_name)
{
	emergency_exit = false;
	max_fps = 20;
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
	
	LakeTracker tracker;

	renderer.addRenderObject(&tracker);

	while(!WindowShouldClose() || emergency_exit)
	{
		frame_ID++;
		for(int i = 0; i != renderer.getRenderObjects()->size(); i++)
		{
			renderer.getRenderObjects()->at(i)->update();
		}
		renderer.startDrawing();
		DrawText(frame_label.c_str(), 5, 5, 10, WHITE);
		// DrawFPS(GetMouseX(), GetMouseY());
		renderer.drawContents();
		renderer.stopDrawing();
		if(IsKeyPressed(KEY_C))
		{
			TakeScreenshot(("screenshots/screenshot-" + std::to_string(frame_ID) + "-.png").c_str());
			std::cout << "Screenshot taken\n";
		}
	}
}

void TwilightEngine::postError(std::string message)
{
	std::cout << "| Error | : [" << message << "]\n";
	if(errors_left == 0 || warnings_left == 0)
	{
		std::cout << "No Errors left to give, quitting program\n";
		emergency_exit = true;
	}
	errors_left--;
}

void TwilightEngine::postWarning(std::string message)
{
	std::cout << "| warning | : [" << message << "]\n";
	if(warnings_left == 0)
	{
		std::cout << "No Warnings left to give, quitting program\n";
		emergency_exit = true;
	}
	warnings_left--;
}