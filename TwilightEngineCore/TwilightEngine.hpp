#pragma once

#include <string>
#include "Point.hpp"

#include "Renderables/RenderObject.hpp"
#include "Rendering.hpp"
#include "TwilightNode.hpp"
#include "CollisionMan.hpp"
#include "TwilightBSP.hpp"
#include "TextureManager.hpp"

#include "Ball.hpp"

#include "WizardPanel.hpp"
#include "Renderables/Sprite.hpp"

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
	TextureManager texture_manager;

	int GIF_frame_counter = 0;
	bool is_recording_gif = false;
	std::string gif_name;

	/*
		The wizard being present means that
		there will be information about the
		engine in a panel on the right side
		of the screen.
	*/
	bool is_wizard_present;

	/*
		Keeping this as a pointer, for any low memory
		uses (Raspberry pi) this engine might be used
		on...
	*/
	WizardPanel* wizard_panel;

public:
	TwilightEngine(int argc, char* argv[], Point<float> new_window_size, std::string new_name);
	~TwilightEngine();
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
	
	/*
		Looks for any Twilight Nodes that
		have a deletion request and will
		free and then delete any that have.
	*/
	void handleDeletionRequests();
	
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
	
	//GIF handling, might move this over somewhere else soon.
	void startGIFRecording(std::string name);
	void stopGIFRecording();
	void recordGIFFrame();

	void addRenderObject(RenderObject2D* new_object)
	{
		renderer.addRenderObject(new_object);
		std::cout << " t = " << new_object->getType() << "\n";
		if(new_object->getType() == "sprite")
		{
			std::cout << "assigning texture to sprite...\n";
			Sprite* sprite_object = ((Sprite*)new_object);
			sprite_object->setTexture(texture_manager.getTwilightTextureData(sprite_object->getSearchID()));
		}
	}
	void addRenderObject3D(RenderObject3D* new_object)
	{
		renderer.addRenderObject3D(new_object);
	}
	void addTexture(std::string file_name, int texture_ID)
	{
		texture_manager.addTexture(file_name, texture_ID);
	}
	void lockAllInputs()
	{
		for(auto object : *renderer.getRenderObjects())
		{
			object->lockInput();
		}
		for(auto object : *renderer.getRenderObjects3D())
		{
			object->lockInput();
		}
	}
	void unlockAllInputs()
	{
		for(auto object : *renderer.getRenderObjects())
		{
			object->unlockInput();
		}
		for(auto object : *renderer.getRenderObjects3D())
		{
			object->unlockInput();
		}
	}
};