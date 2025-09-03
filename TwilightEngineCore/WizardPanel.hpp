#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>

#include "Renderables/RenderObject.hpp"
#include "Renderables/RenderObject3D.hpp"

#include "WizardPage.hpp"

class WizardPanel : public RenderObject
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

	std::vector<RenderObject*>* render_object_vector;
	std::vector<RenderObject3D*>* render_object_3D_vector;
	

public:
	WizardPanel();
	void grabRenderObjectLists(
								std::vector<RenderObject*>* main_render_object_vector,
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
};