#include "UserIncludes.hpp"
/*
	Hello!
	This file will let you easily add your own code
	to run. "userSetup" will run once at the start,
	and "userLoop" will run once every frame.
*/

BeetleNode* top_dog;

void TwilightEngine::userSetup()
{
	// renderer.addRenderObject(new TwilightExtensionDemo());
	// renderer.addRenderObject3D(new MagicCube(Point3D<float>(0, 0, 0)));
	// renderer.addRenderObject3D(new MagicCube(Point3D<float>(5, 5, 0)));
	// renderer.addRenderObject3D(new MagicCube(Point3D<float>(10, -5, 0)));
	// renderer.addRenderObject3D(new MagicCube(Point3D<float>(15, 5, 0)));

	Camera3D* camera = new Camera3D();

	camera->position = (Vector3){ 0.0f, 3.0f, 16.0f };
	camera->target = (Vector3){ -3.0f, -3.0f, 3.0f };
	camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera->fovy = 45.0f;
	camera->projection = CAMERA_PERSPECTIVE;

	renderer.addCamera(camera);

	renderer.current_camera = 0;
	//This is abysmal practice but yk, I'm just messing around rn.
	top_dog = new BeetleNode();
	top_dog->giveChild(new BeetleNode(top_dog));
	renderer.addRenderObject(top_dog);
}

void TwilightEngine::userLoop()
{
	if(IsKeyPressed(KEY_Y))
	{
		top_dog->handChildDown(new BeetleNode());
	}
}