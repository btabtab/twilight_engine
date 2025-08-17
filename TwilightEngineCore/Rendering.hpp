#pragma once

#include <raylib.h>
#include <vector>

#include "Renderables/RenderClasses.hpp"

class Renderer
{
private:
	std::vector<RenderObject*> render_objects;
public:
	RenderTexture2D render_texture;
	Renderer(int width, int height);
	~Renderer();

	void setRenderTextureSize(int width, int height);
	void setRenderTexture(RenderTexture2D new_texture);

	RenderTexture2D getRenderTexture();
	std::vector<RenderObject*>* getRenderObjects();

	void addRenderObject(RenderObject* new_object);
	void clearScreen();
	void startDrawing();
	void stopDrawing();
	void drawContents();

	void drawRenderTexture(RenderTexture2D texture, int x, int y, Color tint = WHITE);
};