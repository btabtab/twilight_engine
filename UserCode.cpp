#include "UserIncludes.hpp"
/*
	Hello!
	This file will let you easily add your own code
	to run. "userSetup" will run once at the start,
	and "userLoop" will run once every frame.
*/

void TwilightEngine::userSetup()
{
	renderer.addRenderObject(new TwilightExtensionDemo());
	renderer.addRenderObject3D(new MagicCube(Point3D<float>(0, 0, 0)));
	renderer.addRenderObject3D(new MagicCube(Point3D<float>(5, 5, 0)));
	renderer.addRenderObject3D(new MagicCube(Point3D<float>(10, -5, 0)));
	renderer.addRenderObject3D(new MagicCube(Point3D<float>(15, 5, 0)));

	Camera3D* camera = new Camera3D();

	camera->position = (Vector3){ 0.0f, 3.0f, 16.0f };
	camera->target = (Vector3){ -3.0f, -3.0f, 3.0f };
	camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera->fovy = 45.0f;
	camera->projection = CAMERA_PERSPECTIVE;

	renderer.addCamera(camera);

	renderer.current_camera = 0;
}

void TwilightEngine::userLoop()
{
	MagicCube* last_magic_cube = nullptr;
	for(int i = renderer.getRenderObjects()->size() - 1; i != 0; i--)
	{
		if(renderer.getRenderObjects()->at(i)->getType() == "MagicCube")
		{
			last_magic_cube = (MagicCube*)renderer.getRenderObjects()->at(i);
		}
	}
	if(last_magic_cube)
	{
		renderer.getCurrentCamera()->target.x = last_magic_cube->getPosition().getX();
		renderer.getCurrentCamera()->target.y = last_magic_cube->getPosition().getY();
		renderer.getCurrentCamera()->target.z = last_magic_cube->getPosition().getZ();
	}
	if(IsKeyPressed(KEY_Q))
	{
		renderer.addRenderObject3D(new MagicCube(Point3D<float>(0, 0, 0)));
		for(int i = -20; i != 20; i++)
		{
			renderer.addRenderObject3D(new MagicCube(Point3D<float>(i, sin(i), -i)));
		}

	}
}