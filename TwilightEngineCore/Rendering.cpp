#include "Rendering.hpp"

Renderer::Renderer(int width, int height)
{
	// Default rectangle: full window
	render_rect = (Rectangle){0, 0, (float)width, (float)height};
	render_texture.id = 0; // Not initialized yet
}
void Renderer::initializeTexture()
{
	// Only call after InitWindow
	render_texture = LoadRenderTexture((int)render_rect.width, (int)render_rect.height);
}

Renderer::~Renderer()
{
	UnloadRenderTexture(render_texture);
}
#include "Rendering.hpp"


void Renderer::addRenderObject(RenderObject *new_object)
{
	render_objects.push_back(new_object);
}
void Renderer::clearScreen()
{
	ClearBackground(BLACK);
}
void Renderer::startDrawing()
{
	BeginTextureMode(render_texture);
	clearScreen();
	// DrawFPS(10, 10); // Display FPS in the top-left corner
	// DrawText("Twilight Engine", 10, 30, 20, WHITE); // Display engine name
}
void Renderer::stopDrawing()
{
	EndTextureMode();
}
std::vector<RenderObject*>* Renderer::getRenderObjects()
{
	return &render_objects;
}

void Renderer::drawContents()
{

	// Draw all objects by layer (unchanged)
	for (int i = 0; i != render_objects.size(); i++)
	{
		if (render_objects.at(i)->getLayer() == Layers::BACK)
		{
			render_objects.at(i)->draw();
		}
	}
	for (int i = 0; i != render_objects.size(); i++)
	{
		if (render_objects.at(i)->getLayer() == Layers::MIDDLE)
		{
			render_objects.at(i)->draw();
		}
	}
	for (int i = 0; i != render_objects.size(); i++)
	{
		if (render_objects.at(i)->getLayer() == Layers::FRONT)
		{
			render_objects.at(i)->draw();
		}
	}
	for (int i = 0; i != render_objects.size(); i++)
	{
		if (render_objects.at(i)->getLayer() == Layers::UI)
		{
			render_objects.at(i)->draw();
		}
	}

}
void Renderer::drawRenderTexture(Rectangle dest)
{
	// Draw the render texture as a regular texture in the given rectangle
	DrawTexturePro(render_texture.texture,
				  (Rectangle){0, 0, (float)render_texture.texture.width, -(float)render_texture.texture.height}, // source rect, flip Y
				  dest,
				  (Vector2){0, 0},
				  0.0f,
				  WHITE);
	DrawRectanglePro(dest, (Vector2){dest.x, dest.y}, 70, WHITE);
}

void Renderer::setRenderRect(Rectangle rect)
{
	render_rect = rect;
}

RenderTexture2D Renderer::getRenderTexture()
{
	return render_texture;
}


Rectangle Renderer::getRenderRect() const
{
	return render_rect;
}