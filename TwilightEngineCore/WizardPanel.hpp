#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>

#include "Renderables/RenderObject.hpp"
#include "Renderables/RenderObject3D.hpp"

#include "WizardPage.hpp"

class WizardPanel : public RenderObject2D
{
private:
	bool showing = false;
	std::vector<std::string> text_to_show;
	int current_page;
	std::vector<WizardPage*> pages;

	bool was_step_issued;

	bool is_he_here;
	Texture the_wizard_texture;

	bool request_gif_recording;
	bool request_screenshot;

	/*
		These don't belong to the panel so they won't be
		included in any metrics reports.
	*/

	//The external RenderObject vector that belongs to the rendering core.
	std::vector<RenderObject2D*>* render_object_vector;
	//The external RenderObject3D vector that belongs to the rendering core.
	std::vector<RenderObject3D*>* render_object_3D_vector;
	

public:
	WizardPanel();
	void grabRenderObjectLists(
								std::vector<RenderObject2D*>* main_render_object_vector,
								std::vector<RenderObject3D*>* main_render_object_3D_vector
							);

	void loadWizardTexture();
	void addTextToPanel();
	void updateDebugPage();

	void draw() override;
	bool isWizardOpen();

	void handleInputs();
	std::string getType() override;
	~WizardPanel();

	bool getWasStepIssued();

	bool callForGifRecording();
	bool callForScreenshot();
	
	virtual size_t getBytesConsumed() override
	{
		size_t ret = 0;
		ret += sizeof(*this);

		for(auto page : pages)
		{
			ret += page->getBytesConsumed();
		}
		return ret;
	}

};