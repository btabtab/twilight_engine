#pragma once

#include <string>
#include "Point.hpp"

#include "Renderables/RenderObject.hpp"
#include "Rendering.hpp"
#include "TwilightNode.hpp"
#include "CollisionMan.hpp"
#include "TwilightBSP.hpp"

#include "Ball.hpp"

class TwilightEngine
{
private:
	//Used for psuedorandom-ness.
	int frame_ID;
	//The label for the frame. Used for screenshots.
	std::string frame_label;
	//This will determine the name of the window.
	std::string session_name;

	Point<float> window_size;
	int max_fps;

	//Wether or not the engine has started.
	bool has_started;

	//This will be true if something has gone wrong.
	bool emergency_exit;

	//The amount of errors left before the program stops.
	int errors_left;
	//The amount of warnings left before the program stops.
	int warnings_left;

	//True if the engine is in a paused state.
	bool is_engine_paused;

	//If true this will suspend the engine upon a warning happening.
	bool suspend_on_warning;

	Renderer renderer;

	int GIF_frame_counter = 0;
	bool is_recording_gif = false;
	std::string gif_name;
public:
	TwilightEngine(Point<float> new_window_size, std::string new_name);

	void startGIFRecording(std::string name)
	{
		is_recording_gif = true;
		gif_name = name;
	}
	void stopGIFRecording()
	{
		is_recording_gif = false;
		GIF_frame_counter = 0;
	}
	void recordGIFFrame()
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
	//Enters the main loop.
	void enter();
	//Takes a screenshot with the name.
	void takeScreenshot(std::string name);
	//Will take a screenshot with a random name.
	void takeScreenshot();

	//Clears the screen for rendering.
	void clearScreen();
	//Renders the next frame.
	void renderNextFrame();
	//If the engine has stopped then return.
	bool isEngineClosed();

	//Puts an error message into the console.
	void postError(std::string message);
	//Puts a warning into the console.
	void postWarning(std::string message);

	/*
		This will pause the engin and dump information into the console
		as to what is happening.
	*/
	void suspendEngine();

	/*
		This is a function for anyone making use of the
		engine to do their own setup.
	*/
	void userSetup();
	/*
		Lets someone using the engine do their own looping
		stuff.
	*/
	void userLoop();
};