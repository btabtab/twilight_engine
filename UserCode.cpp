#include "UserIncludes.hpp"
#include "TwilightEngineCore/LightMap.hpp"
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
    camera->position = (Vector3){ 0.0f, 3.0f, 5.0f }; // Camera position
    camera->target = (Vector3){ 0.0f, 0.f, 0.0f };      // Camera looking at point
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera->fovy = 45.0f;                                // Camera field-of-view Y
    camera->projection = CAMERA_PERSPECTIVE;             // Camera projection type

	renderer.addCamera(camera);

	renderer.current_camera = 0;
	std::cout << "Camera added.\n";
	std::cout << "Welcome to the Twilight Engine!\n";
	std::cout << "You can use the C key to take a screenshot.\n";
	std::cout << "You can use the V key to clear the console.\n";
	
	renderer.addRenderObject(new LightBreakdown(
												new Room(),
												new Light(Point<float>(200, 200), WHITE, 100.0f)
												)
							);
	LightBreakdown* light_breakdown = (LightBreakdown*)renderer.getRenderObjects()->back();
	light_breakdown->getRoom()->addWall(Point<float>(24.f, 26.f), Point<float>(379.f, 24.f), WHITE);
	light_breakdown->getRoom()->addWall(Point<float>(379.f, 24.f), 	Point<float>(381.f, 364.f), WHITE);
	light_breakdown->getRoom()->addWall(Point<float>(381.f, 364.f), Point<float>(19.f, 378.f), WHITE);
	light_breakdown->getRoom()->addWall(Point<float>(19.f, 378.f), Point<float>(24.f, 26.f), WHITE);

	light_breakdown->getRoom()->addWall(Point<float>(177.f, 67.f), Point<float>(62.f, 205.f), WHITE);

	light_breakdown->buildLightLines();
	light_breakdown->cleanUpLightLines();

}

void TwilightEngine::userLoop()
{
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Point<float> mouse_pos = Point<float>(GetMouseX(), GetMouseY());
		std::cout << mouse_pos.stringify() << "\n";
	}
}