#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>

#include "Renderables/RenderClasses.hpp"
#include "Renderables/RenderObject.hpp"
#include "Renderables/RenderObject3D.hpp"

#include "TwilightMetrics.hpp"

#include "WizardPage.hpp"

class WizardPanel : public RenderObject2D
{
private:
	RenderTexture metrics_grid_render_texture;
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

	TwilightMetrics* twilight_metrics;

public:
	WizardPanel(bool run_with_twilight_metrics = false);
	void grabRenderObjectLists(
								std::vector<RenderObject2D*>* main_render_object_vector,
								std::vector<RenderObject3D*>* main_render_object_3D_vector
							);
	void produceRenderTexture();
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

	void drawTwilightMetricsGraph();
	void updateMetricsGrid();
	void drawMetricsGridLine(float value_to_draw, std::string label, Color colour);
	void drawMetricsAsLines(std::vector<float>* vector_to_draw, Color colour, float divide_amount);
	void updateMetrics()
	{
		twilight_metrics->generalUpdate(getEngineMemoryUsage(), GetFPS());
	}

	int getEngineMemoryUsage()
	{
		size_t space_consumed = getBytesConsumed();
		
		for(int i = 0; i != render_object_vector->size(); i++)
		{
			space_consumed += render_object_vector->at(i)->getBytesConsumed();
		}
		for(int i = 0; i != render_object_3D_vector->size(); i++)
		{
			space_consumed += render_object_3D_vector->at(i)->getBytesConsumed();
		}
		return space_consumed;
	}
	virtual size_t getBytesConsumed() override
	{
		size_t ret = 0;
		ret += sizeof(*this);

		for(auto page : pages)
		{
			ret += page->getBytesConsumed();
		}
		
		if(twilight_metrics)
		{
			ret += twilight_metrics->getBytesConsumed();
		}

		return ret;
	}

};