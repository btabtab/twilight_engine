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
    BeginDrawing();
    clearScreen();
    // DrawFPS(10, 10); // Display FPS in the top-left corner
    // DrawText("Twilight Engine", 10, 30, 20, WHITE); // Display engine name
}
void Renderer::stopDrawing()
{
    EndDrawing();
}
std::vector<RenderObject*>* Renderer::getRenderObjects()
{
	return &render_objects;
}

void Renderer::drawContents()
{
    startDrawing();

    /*
        TODO:
        Make this sort the list by layers only when
        a new element is added to the list.
    */

    /*
        This awful series of FOR loops is responsible,
        for now at least, for rendering objects with layers.
    */
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
    stopDrawing();
}