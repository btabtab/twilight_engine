#pragma once

#include <raylib.h>
#include <vector>

#include "Renderables/RenderClasses.hpp"
#define ERROR_NO_CAMERA_AVAILABLE 2
class Renderer
{
private:
	std::vector<RenderObject2D*> render_objects;
	std::vector<RenderObject3D*> render_objects_3D;

	/*
		Multiple cameras for multiple angles.
	*/
	std::vector<Camera3D*> cameras;

public:
	Renderer();
	~Renderer();
	std::vector<RenderObject2D*>* getRenderObjects();
	std::vector<RenderObject3D*> *getRenderObjects3D();


	void addRenderObject(RenderObject2D* new_object);
	void addRenderObject3D(RenderObject3D* new_object);

	void clearScreen();
	void startDrawing();
	void stopDrawing();
	void drawContents();

	//3D stuff from here on out.

	/*
		The current camera being used,
		if it is out of bounds it only
		gets the back camera.
	*/
	int current_camera;
	//Gets the desired camera, -WILL- kill the program if none are available.
	Camera3D getCamera(int index);
	//In case you wanna start stacking cameras.
	void addCamera(Camera3D* new_camera);
	//If one camera is left function won't do anything.
	void deleteCamera(int index);

	/*
		This is mainly for Raylib as it requires
		an updatecamera esque call for some things.
	*/
	void updateCurrentCamera();

	//Also kills the program if no cameras are present.
	Camera3D* getCurrentCamera();
	/*
		Putting an underscore in the name
		cos it looks ugly and bad to read
		otherwise. >:3
	*/
	void startDrawing3D_Objects();

	/*
		Putting an underscore in the name
		cos it looks ugly otherwise.
	*/
	void stopDrawing3D_Objects();
};