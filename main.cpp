#include <raylib.h>
#include <iostream>

#include "TwilightEngineCore/TwilightEngine.hpp"

int main()
{
	TwilightEngine core(Vector<float>(400, 400), "Twilight Engine");
	core.enter();
}