#pragma once

#include <raylib.h>
#include <vector>

#include "Renderables/RenderClasses.hpp"

class Renderer
{
private:
	std::vector<RenderObject*> render_objects;
public:
	std::vector<RenderObject*>* getRenderObjects();
	void addRenderObject(RenderObject* new_object);
	void clearScreen();
	void startDrawing();
	void stopDrawing();
	void drawContents();
};