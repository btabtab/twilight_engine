#include "UserIncludes.hpp"

/*

	Hello!
	This file will let you easily add your own code
	to run. "userSetup" will run once at the start,
	and "userLoop" will run once every frame.

*/

GrublingCollisionManager *grubling_colision_manager;
Texture test_texture;

void TwilightEngine::userSetup()
{

	CursorTextureIDs::loadTextures(this);

	Camera3D *camera = new Camera3D();
	camera->position = (Vector3){0.0f, 3.0f, 16.0f};
	camera->target = (Vector3){-3.0f, -3.0f, 3.0f};
	camera->up = (Vector3){0.0f, 1.0f, 0.0f};
	camera->fovy = 45.0f;
	camera->projection = CAMERA_PERSPECTIVE;

	renderer.addCamera(camera);
	renderer.current_camera = 0;
	grubling_colision_manager = new GrublingCollisionManager(renderer.getRenderObjects());

	renderer.addRenderObject(grubling_colision_manager);
	addTexture("HIM_THE_WIZARD.png", 0);

	addRenderObject(new Sprite(0, Point<int>(0, 0)));
}

void TwilightEngine::userLoop()
{

	grubling_colision_manager->getGrublings(renderer.getRenderObjects());
	if (IsKeyPressed(KEY_Q))
	{
		renderer.addRenderObject(new Grubling());
		renderer.addRenderObject(new Grubling());
		renderer.addRenderObject(new Grubling());
	}

	grubling_colision_manager->getGrublings(renderer.getRenderObjects());
}