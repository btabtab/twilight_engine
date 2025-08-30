#include <raylib.h>
#include <iostream>
#include <string>
#include "TwilightEngineCore/TwilightEngine.hpp"

int main(int argc, char* argv[])
{
	TwilightEngine core(argc, argv, Point<float>(400, 400), "Twilight Engine");
	core.enter();
}