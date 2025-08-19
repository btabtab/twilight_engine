#pragma once

#include <raylib.h>
#include <vector>

#include "Renderables/RenderClasses.hpp"

class Renderer
{
private:
	std::vector<RenderObject*> render_objects;
	Rectangle render_rect;
	RenderTexture render_texture;

public:
	Renderer(int width, int height);
	~Renderer();

	void initializeTexture();
	void setRenderTextureSize(int width, int height);
	void setRenderTexture(RenderTexture2D new_texture);

	RenderTexture2D getRenderTexture();
	std::vector<RenderObject*>* getRenderObjects();

	void addRenderObject(RenderObject* new_object);
	void clearScreen();
	void startDrawing();
	void stopDrawing();
	void drawContents();

	void drawRenderTexture(Rectangle dest);
	void setRenderRect(Rectangle rect);
	Rectangle getRenderRect() const;
};