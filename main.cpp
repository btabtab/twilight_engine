#include <raylib.h>
#include <iostream>
#include <string>
#include "TwilightEngineCore/TwilightEngine.hpp"

int main(int argc, char* argv[])
{
	bool is_the_wizard_here = false;
	for(int i = 0; i != argc; i++)
	{
		if(std::string(argv[i]) == "-wizard")
		{
			is_the_wizard_here = true;
			printf("Wizard found, running with the wizard...\n");
		}
	}

	printf("Clearing Gifs...");
	system("rm -rf screenshots/gifs/*");
	system("rm -rf screenshots/*");

	TwilightEngine core(Point<float>(400, 400), "Twilight Engine", is_the_wizard_here);
	core.enter();
}