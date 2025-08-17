#include "TwilightEngine.hpp"

TwilightEngine::TwilightEngine(Point<float> new_window_size, std::string new_name):
window_size(new_window_size), session_name(new_name)
{
	emergency_exit = false;
	max_fps = 20;
}

void TwilightEngine::enter()
{
	frame_ID = 0;
	InitWindow(window_size.getX(), window_size.getY(), session_name.c_str());
	SetTargetFPS(max_fps);
	warnings_left = 10;
	errors_left = 0;
	has_started = true;
	system("clear");

	// renderer.addRenderObject(
	// 			new Line2D(
	// 					Point<float>(50, 50),
	// 					Point<float>(200, 200),
	// 					RED
	// 						)
	// 							);
								
	// renderer.addRenderObject(
	// 			new Line2D(
	// 					Point<float>(200, 50),
	// 					Point<float>(50, 200),
	// 					RED
	// 						)
	// 							);

	// renderer.addRenderObject(
	// 			new CollisionMan(
	// 					(Line2D*)renderer.getRenderObjects()->at(0),
	// 					(Line2D*)renderer.getRenderObjects()->at(1)
	// 						)
	// 							);

	/*
		The "zero" points are so that I can quickly
		make them pop out so that the test looks cooler.
	*/
	std::vector<Point<float>> points;
	for(int i = 0; i != 8; i++)
	{
		points.push_back(Point<float>(window_size.getX() / 2, window_size.getY() / 2));
	}
	//corner points.
	// points.at(0) += Point<float>(-70, -70);
	// points.at(2) += Point<float>(+70, -70);
	// points.at(4) += Point<float>(+70, +70);
	// points.at(6) += Point<float>(-70, +70);
	
	// points.at(1) += Point<float>(-0, -120);
	// points.at(3) += Point<float>(+120, -0);
	// points.at(5) += Point<float>(+0, +120);
	// points.at(7) += Point<float>(-120, +0);

	/*
		Original demo lines,
		roughly adapted from:
		https://en.wikipedia.org/wiki/Binary_space_partitioning
	*/
	//A
	points.at(0) += Point<float>(-25, 0);
	points.at(1) += Point<float>(25, 0);

	//B
	points.at(2) += Point<float>(-30, -20);
	points.at(3) += Point<float>(-30, +20);

	//C
	points.at(4) += Point<float>(-60, +40);
	points.at(5) += Point<float>(-20, -60);

	//D
	points.at(6) += Point<float>(+50, +30);
	points.at(7) += Point<float>(+20, -40);

	//Extra lines for testing reasons.

	points.push_back(Point<float>(74, 308));
	points.push_back(Point<float>(341, 269));
	points.push_back(Point<float>(341, 269));
	points.push_back(Point<float>(275, 90));

	points.push_back(Point<float>(275, 90));
	points.push_back(Point<float>(190, 90));
	points.push_back(Point<float>(190, 90));
	points.push_back(Point<float>(135, 65));

	points.push_back(Point<float>(135, 65));
	points.push_back(Point<float>(44, 128));
	points.push_back(Point<float>(44, 128));
	points.push_back(Point<float>(74, 308));

	LineSet line_set;
	for(int i = 0; i != points.size(); i += 2)
	{
		line_set.addLine(points.at(i), points.at(i + 1), (Color){0xFF, 0xFF, 0xFF, 0xFF >> 1});
	}

	BSPNode bsp_node(line_set.getLines()->at(0), false, 0);
	BSPNode* current = &bsp_node;
	bsp_node.splitLines(*line_set.getLines());
	renderer.addRenderObject(&bsp_node);
	frame_label = "<Default_state>, depth = ";

	Side current_side = Side::FRONT;
	// bsp_node.grow();
	
	while(!WindowShouldClose() || emergency_exit)
	{
		frame_ID++;
		for(int i = 0; i != renderer.getRenderObjects()->size(); i++)
		{
			renderer.getRenderObjects()->at(i)->update();
		}
		renderer.startDrawing();
		DrawText(frame_label.c_str(), 5, 5, 10, WHITE);
		// DrawFPS(GetMouseX(), GetMouseY());
		renderer.drawContents();

		// --- INPUT POLLING SECTION ---
		if(IsKeyPressed(KEY_C))
		{
			TakeScreenshot(("screenshots/screenshot-" + std::to_string(frame_ID) + "-.png").c_str());
			std::cout << "Screenshot taken\n";
		}
		if(IsKeyPressed(KEY_P))
		{
			std::cout << "P pressed\n";
			current->birthNewChild(current_side);
			if(current->getChildBasedOnSide(current_side))
			{
				std::cout << "getting new child... with depth of " << current->getDepth() << "\n" ;
				current = current->getChildBasedOnSide(current_side);
				current->dumpNodeAsText();
			}
		}
		if(IsKeyPressed(KEY_G))
		{
			TakeScreenshot("screenshots/screenshot-Pre Split-.png");
			current->grow();
			current->dumpEntireTreeAsText();
		}
		if(IsKeyPressed(KEY_U))
		{
			std::cout << "Getting Parent\n";
			if(current->getParent())
			{
				current = current->getParent();
			}
			frame_label = "Gone up a layer (depth = " + std::to_string(current->getDepth()) + ")";
		}
		if(IsKeyPressed(KEY_UP))
		{
			std::cout << "UP\n";
			current_side = Side::FRONT;
			frame_label = "Front, depth = " + std::to_string(current->getDepth());
		}
		if(IsKeyPressed(KEY_DOWN))
		{
			std::cout << "DOWN\n";
			current_side = Side::BACK;
			frame_label = "Back, depth = " + std::to_string(current->getDepth());
		}
		if(IsKeyPressed(KEY_V))
		{
			system("clear");
		}
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			std::cout << "\nPoint<float>(" + std::to_string(GetMouseX()) + ", " + std::to_string(GetMouseY()) + ")\n";
			// Test: Draw bounding box for node containing mouse
			Point<float> mouse_pt(GetMouseX(), GetMouseY());
			BSPNode* containing_node = bsp_node.findNodeContainingPoint(mouse_pt);
			if (containing_node) {
				Bounds bbox = containing_node->getBoundingBox();
				bbox.draw();
				std::cout << "Mouse is inside node at depth " << containing_node->getDepth() << "\n";
			} else {
				std::cout << "Mouse is not inside any node's bounding box\n";
			}
		}
		// --- END INPUT POLLING SECTION ---
		renderer.stopDrawing();
	}
}

void TwilightEngine::postError(std::string message)
{
	std::cout << "| Error | : [" << message << "]\n";
	if(errors_left == 0 || warnings_left == 0)
	{
		std::cout << "No Errors left to give, quitting program\n";
		emergency_exit = true;
	}
	errors_left--;
}

void TwilightEngine::postWarning(std::string message)
{
	std::cout << "| warning | : [" << message << "]\n";
	if(warnings_left == 0)
	{
		std::cout << "No Warnings left to give, quitting program\n";
		emergency_exit = true;
	}
	warnings_left--;
}