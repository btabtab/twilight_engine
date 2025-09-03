#include "UserIncludes.hpp"
/*
	Hello!
	This file will let you easily add your own code
	to run. "userSetup" will run once at the start,
	and "userLoop" will run once every frame.
*/

void TwilightEngine::userSetup()
{
	renderer.addRenderObject(new CosSinGrid());
}

void TwilightEngine::userLoop()
{
}