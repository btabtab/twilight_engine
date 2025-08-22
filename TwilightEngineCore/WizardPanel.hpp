#include <iostream>
#include <string>
#include <vector>

#include "Renderables/RenderObject.hpp"

#include "WizardPage.hpp"

class WizardPanel : public RenderObject
{
private:
	bool showing = false;
	std::vector<std::string> text_to_show;
	int current_page;
	std::vector<WizardPage*> pages;
public:
	WizardPanel()
	{
		current_page = 0;
		std::cout << "\"Hello\" - The Wizard\n";
		pages.push_back(new WizardPage("KeyBinds"));
		pages.back()->addText(std::string("L-ALT + H - Show/Hide wizard panel\n"));
		pages.back()->addText(std::string("L-ALT + Left - Next page\n"));
		pages.back()->addText(std::string("L-ALT + Right - Last page\n"));
		pages.back()->addText(std::string("L-ALT + X + Y - Close Application\n"));
	}
	void addTextToPanel()
	{
	}

	void draw() override
	{
		std::cout << "showing " << showing << "\n";
		if(!showing)
		{
			return;
		}
		if(pages.empty())
		{
			showing = false;
			return;
		}
		Point<int> screen(GetScreenWidth(), GetScreenHeight());
		DrawRectangle(0, 0, screen.getX(), screen.getY(), BLACK);
		pages.at(current_page)->draw();
	}

	void handleInputs()
	{
		if(IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_H))
		{
			showing = !showing;
			std::cout << "Toggling Wizard Panel...\n";
		}
	}

	std::string getType() override { return "Wizard Panel"; }

	~WizardPanel()
	{
		std::cout << "\"Goodbye\" - The Wizard.\n";
	}
};