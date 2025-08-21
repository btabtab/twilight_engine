#include "UserIncludes.hpp"
/*
	Hello!
	This file will let you easily add your own code
	to run. "userSetup" will run once at the start,
	and "userLoop" will run once every frame.
*/

void TwilightEngine::userSetup()
{

	Camera3D* camera = new Camera3D();
	// Define the camera to look into our 3d world
    camera->position = (Vector3){ 0.0f, 0.0f, 16.0f }; // Camera position
    camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera->fovy = 45.0f;                                // Camera field-of-view Y
    camera->projection = CAMERA_PERSPECTIVE;             // Camera projection type

	renderer.addCamera(camera);

	renderer.current_camera = 0;
	std::cout << "Camera added.\n";
	std::cout << "Welcome to the Twilight Engine!\n";
	std::cout << "You can use the C key to take a screenshot.\n";
	std::cout << "You can use the V key to clear the console.\n";

	renderer.addRenderObject3D(new MagicCube(8.0f));

	startGIFRecording("magic_cube_rotation");
	std::cout << "GIF recording started.\n";
}

void TwilightEngine::userLoop()
{
	recordGIFFrame();

	if(120 < GIF_frame_counter)
	{
		stopGIFRecording();
		std::cout << "GIF recording stopped.\n";
	}
}