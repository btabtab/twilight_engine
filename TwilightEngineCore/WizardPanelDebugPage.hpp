#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <algorithm>

#include "WizardPage.hpp"
#include "TwilightMetrics.hpp"

class WizardDebugPage : public WizardPage
{
private:
	RenderTexture metrics_grid_render_texture;
	std::vector<RenderObject2D *> *render_object_vector;
	std::vector<RenderObject3D *> *render_object_3D_vector;
	TwilightMetrics twilight_metrics;

public:
	void startRenderTextures()
	{
		metrics_grid_render_texture = LoadRenderTexture(GetScreenWidth() - 20, 200);
	}
	std::string getType() override
	{
		return "WizardDebugPage";
	}
	void updateMetricsGrid()
	{
		Point<int> dimensions(metrics_grid_render_texture.texture.width, metrics_grid_render_texture.texture.height);
		BeginTextureMode(metrics_grid_render_texture);
		ClearBackground(BLACK);

		Color hollow_green =
			(Color){
				0,
				0xff,
				0,
				0xff >> 1};

		for (int x = 0; x <= dimensions.getX(); x += 10)
		{
			Line2D(
				Point<float>(x, 20),
				Point<float>(x, dimensions.getY()),
				hollow_green)
				.draw();
		}
		for (int y = 20; y <= dimensions.getY(); y += 10)
		{
			Line2D(
				Point<float>(0, y),
				Point<float>(dimensions.getX(), y),
				hollow_green)
				.draw();
		}

		float current_memory_usage_in_kilobytes = (getEngineMemoryUsage() / 1024.f);

		drawMetricsAsLines(twilight_metrics.getMemoryConsumedHistory(), RED, 1024);
		drawMetricsAsLines(twilight_metrics.getFramerateHistory(), ORANGE, 1);

		drawMetricsGridLine(
			current_memory_usage_in_kilobytes,
			"Current Memory Usage in KB: " + std::to_string(current_memory_usage_in_kilobytes),
			BLUE);

		drawMetricsGridLine(
			twilight_metrics.getAverageFramerate(),
			"Current Framerate: " + std::to_string(GetFPS()),
			GREEN);

		DrawText("TwilightMetrics:", 0, 0, 10, WHITE);

		EndTextureMode();
	}

	void updateMetrics()
	{
		twilight_metrics.generalUpdate(getEngineMemoryUsage(), GetFPS());
	}

	int getEngineMemoryUsage()
	{
		size_t space_consumed = getBytesConsumed();

		for (int i = 0; i != render_object_vector->size(); i++)
		{
			space_consumed += render_object_vector->at(i)->getBytesConsumed();
		}
		for (int i = 0; i != render_object_3D_vector->size(); i++)
		{
			space_consumed += render_object_3D_vector->at(i)->getBytesConsumed();
		}
		return space_consumed;
	}
	void drawTwilightMetricsGraph()
	{
		Point<int> metrics_box_top_left(10, 50);

		// Draw the render texture flipped to display properly
		Rectangle source = {0.0f, 0.0f, (float)metrics_grid_render_texture.texture.width, -(float)metrics_grid_render_texture.texture.height};
		Rectangle dest = {(float)metrics_box_top_left.getX(), (float)metrics_box_top_left.getY(), (float)metrics_grid_render_texture.texture.width, (float)metrics_grid_render_texture.texture.height};
		Vector2 origin = {0.0f, 0.0f};
		DrawTexturePro(metrics_grid_render_texture.texture, source, dest, origin, 0.0f, RAYWHITE);
	}

	/*
		1. Grab the value, colour, and label,
		2. Draw the line after accounting for dimensions..
	*/
	void drawMetricsGridLine(float value_to_draw, std::string label, Color colour)
	{
		Point<int> dimensions(metrics_grid_render_texture.texture.width, metrics_grid_render_texture.texture.height);

		value_to_draw = dimensions.getY() - value_to_draw;

		DrawLine(0, value_to_draw, dimensions.getX(), value_to_draw, BLUE);

		DrawText(
			label.c_str(),
			10,
			value_to_draw - 10,
			10,
			colour);
	}

	void drawMetricsAsLines(std::vector<float> *vector_to_draw, Color colour, float divide_amount)
	{
		if (vector_to_draw == nullptr || vector_to_draw->empty())
		{
			// If the vector is null or empty, there's nothing to draw.
			return;
		}

		Point<int> dimensions(metrics_grid_render_texture.texture.width, metrics_grid_render_texture.texture.height);

		Point<float> last_point(0, dimensions.getY());

		for (size_t i = 0; i < vector_to_draw->size(); ++i)
		{
			// Scale the value using divide_amount to ensure it fits within the grid's height.
			float scaled_value = vector_to_draw->at(i) / divide_amount;
			float value_to_draw = dimensions.getY() - std::clamp(scaled_value, 0.0f, (float)dimensions.getY());

			Point<float> new_point(
				// Scale x-coordinate to fit within the texture width.
				(static_cast<float>(dimensions.getX()) / vector_to_draw->size()) * i,
				value_to_draw);

			Line2D(
				last_point,
				new_point,
				colour)
				.draw();

			last_point = new_point;
		}
	}

	void update() override
	{
		getText()->at(0) = "Framerate: " + std::to_string(GetFPS());
		getText()->at(1) = "2D render objects: " + std::to_string(render_object_vector->size());
		getText()->at(2) = "3D render objects: " + std::to_string(render_object_3D_vector->size());

		getText()->at(3) = "Space consumed in MB: " + std::to_string((((float)getEngineMemoryUsage() / 1024.f) / 1024.f));

		updateMetricsGrid();

	}
	void setVectors(std::vector<RenderObject2D *> *main_render_object_vector, std::vector<RenderObject3D *> *main_render_object_3D_vector)
	{
		render_object_vector = main_render_object_vector;
		render_object_3D_vector = main_render_object_3D_vector;
	}

	void draw() override
	{
		/*
			OMG this is such a game changer this is so cool.
			So basically I'm pretty sure that this allows for me
			to use the default implementation for the class function
			in any children of the class, and thus any higher up
			classes in the chain.
		*/
		WizardPage::draw();// <- THIS IS AMAZING I LOVE THIS.
		drawTwilightMetricsGraph();
	}

	WizardDebugPage(std::vector<RenderObject2D *> *main_render_object_vector, std::vector<RenderObject3D *> *main_render_object_3D_vector) : render_object_vector(main_render_object_vector),
																																			 render_object_3D_vector(main_render_object_3D_vector),
																																			 WizardPage((Texture2D *)nullptr, "Metrics Panel", std::vector<std::string>())
	{
		getText()->push_back("FPS");
		getText()->push_back("2D objects");
		getText()->push_back("3D objects");
		getText()->push_back("Space consumed (MB)");

	}
};