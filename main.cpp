#include <raylib.h>
#include <iostream>

#include "TwilightEngineCore/TwilightEngine.hpp"
#include "TwilightEngineCore/Rendering.hpp"
int main()
{
	Renderer renderer(400, 400);
	TwilightEngine core(Point<float>(400, 400), "Twilight Engine", false);
	core.addRenderer(&renderer);
	core.enter();
}