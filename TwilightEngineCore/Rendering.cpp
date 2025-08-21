#include "Rendering.hpp"
void Renderer::addRenderObject3D(RenderObject3D* new_object)
{
	// For now, treat 3D objects as regular render objects
	render_objects_3D.push_back(new_object);
}

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
std::vector<RenderObject *> *Renderer::getRenderObjects()
{
	return &render_objects;
}
std::vector<RenderObject3D *> *Renderer::getRenderObjects3D()
{
	return &render_objects_3D;
}
void Renderer::drawContents()
{
	startDrawing();

	startDrawing3D_Objects();
	for (int i = 0; i != render_objects_3D.size(); i++)
	{
		if (render_objects_3D.at(i)->getIfDrawnPre2D())
		{
			render_objects_3D.at(i)->draw();
		}
	}
	stopDrawing3D_Objects();
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

	startDrawing3D_Objects();
	for (int i = 0; i != render_objects_3D.size(); i++)
	{
		if (!render_objects_3D.at(i)->getIfDrawnPre2D())
		{
			render_objects_3D.at(i)->draw();
		}
	}
	stopDrawing3D_Objects();
	stopDrawing();
}

void Renderer::updateCurrentCamera()
{
	/*
		TODO:
			make cameras an embedded class
			and give them the classifications.
	*/
	UpdateCamera(getCurrentCamera(), CAMERA_ORBITAL);
}

// Gets the desired camera, -WILL- kill the program if none are available.
Camera3D Renderer::getCamera(int index = 0)
{
	return *cameras.at(index);
}
// In case you wanna start stacking cameras.
void Renderer::addCamera(Camera3D *new_camera)
{
	cameras.push_back(new_camera);
}
// If one camera is left function won't do anything.
void Renderer::deleteCamera(int index = 0)
{
	if (1 < cameras.size())
	{
		delete cameras.at(index);
		cameras.erase(cameras.begin() + index);
	}
}

Camera3D *Renderer::getCurrentCamera()
{
	if (cameras.empty())
	{
		std::cout << "\nUSER ERROR: \tRenderer::getCurrentCamera() called with no cameras available.\n";
		exit(ERROR_NO_CAMERA_AVAILABLE);
	}
	return cameras.back();
}

void Renderer::startDrawing3D_Objects()
{
	BeginMode3D(*getCurrentCamera());
}
void Renderer::stopDrawing3D_Objects()
{
	EndMode3D();
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	for(int i = 0; i < render_objects.size(); i++)
	{
		delete render_objects.at(i);
	}
	for(int i = 0; i < render_objects_3D.size(); i++)
	{
		delete render_objects_3D.at(i);
	}
	for(int i = 0; i < cameras.size(); i++)
	{
		delete cameras.at(i);
	}
}