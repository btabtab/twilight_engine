#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>

#include "Point.hpp"

class WizardPage
{
private:
	std::string page_title;
	std::vector<std::string> text_to_show;
	std::vector<std::string>* dynamic_text;
public:
	WizardPage(std::string new_page_title, std::vector<std::string> new_text_to_show = {}, std::vector<std::string>* new_dynamic_text = nullptr)
	{
		page_title = new_page_title;
		text_to_show = new_text_to_show;
		dynamic_text = new_dynamic_text;
	}
	void addText(std::string text_to_add)
	{
		text_to_show.push_back(text_to_add);
	}
	void draw()
	{
		DrawText("Wizard Panel", 0, 0, 5, BLACK);
		for(int i = 0; i != text_to_show.size(); i++)
		{
			DrawText(text_to_show.at(i).c_str(), 10, i * 10, 5, BLACK);
		}
	}
};