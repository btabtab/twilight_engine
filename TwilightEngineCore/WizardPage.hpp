#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>

#include "Renderables/RenderClasses.hpp"
#include "Point.hpp"

class WizardPage
{
private:
	std::string page_title;
	std::vector<std::string> text_to_show;
	bool does_have_a_hole;
	bool is_the_holy_wizard_of_testing_visible;

	Texture* holy_testing_wizard_texture;

	bool is_debug_page;

public:
	WizardPage(
					Texture* wizard_texture,
					std::string new_page_title,
					std::vector<std::string> new_text_to_show = {}
				);
	std::vector<std::string>* getText();
	void toggleHole();
	void toggleDebugPage();
	bool isDebugPage();
	void addText(std::string text_to_add);
	bool heIsThere();
	void summonOrUnsummonHim();
	void draw();
	bool isThereAHole();
	virtual size_t getBytesConsumed()
	{
		size_t ret = 0;
		//General size.
		ret += sizeof(WizardPage);
		//Size consumed by the title.
		ret += sizeof(char) * page_title.size();
		//Size taken up by the text to show...
		for(auto line : text_to_show)
		{
			ret += sizeof(char) * line.size();
		}
		return ret;
	}
};