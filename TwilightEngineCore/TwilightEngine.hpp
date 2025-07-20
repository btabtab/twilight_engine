#pragma once

#include <string>
#include "Vectors.hpp"

#include "Renderables/RenderObject.hpp"
#include "Rendering.hpp"
#include "TwilightNode.hpp"
#include "CollisionMan.hpp"
#include "TwilightBSP.hpp"

#include "Ball.hpp"

class TwilightEngine
{
private:
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
public:
	TwilightEngine(Point<float> new_window_size, std::string new_name);

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
};