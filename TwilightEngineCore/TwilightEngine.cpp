#include "TwilightEngine.hpp"

TwilightEngine::TwilightEngine(Point<float> new_window_size, std::string new_name):
window_size(new_window_size), session_name(new_name)
{
	emergency_exit = false;
	max_fps = 60;
}

void TwilightEngine::enter()
{
	frame_ID = 0;
	InitWindow(window_size.getX(), window_size.getY(), session_name.c_str());
	SetTargetFPS(max_fps);
	warnings_left = 10;
	errors_left = 0;
	has_started = true;

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

	//A
	points.at(0) += Point<float>(-30, 0);
	points.at(1) += Point<float>(30, 0);

	//B
	points.at(2) += Point<float>(-30, -20);
	points.at(3) += Point<float>(-30, +20);

	//C
	points.at(4) += Point<float>(-60, +40);
	points.at(5) += Point<float>(-20, -60);

	//D
	points.at(6) += Point<float>(+50, +30);
	points.at(7) += Point<float>(+20, -40);

	LineSet line_set;
	line_set.addLine(points.at(0), points.at(1), (Color){0xFF, 0xFF, 0xFF, 0xFF >> 1});
	line_set.addLine(points.at(2), points.at(3), (Color){0xFF, 0xFF, 0xFF, 0xFF >> 1});
	line_set.addLine(points.at(4), points.at(5), (Color){0xFF, 0xFF, 0xFF, 0xFF >> 1});
	line_set.addLine(points.at(6), points.at(7), (Color){0xFF, 0xFF, 0xFF, 0xFF >> 1});

	// renderer.addRenderObject(&line_set);

	BSPNode bsp_node(line_set.getLines()->at(0), false);
	bsp_node.splitLines(*line_set.getLines());
	renderer.addRenderObject(&bsp_node);
	frame_label = "<Default_state>";
	while(!WindowShouldClose() || emergency_exit)
	{
		frame_ID++;
		for(int i = 0; i != renderer.getRenderObjects()->size(); i++)
		{
			renderer.getRenderObjects()->at(i)->update();
		}
		renderer.startDrawing();
		DrawText(frame_label.c_str(), 5, 5, 10, WHITE);
		renderer.drawContents();
		renderer.stopDrawing();
		if(IsKeyPressed(KEY_C))
		{
			TakeScreenshot(("screenshots/screenshot-" + std::to_string(frame_ID) + "-.png").c_str());
			std::cout << "Screenshot taken\n";
		}
		if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_UP))
		{
			bsp_node.eliminateAllChildren();
			bsp_node.birthNewChild(Side::FRONT);
			frame_label = "bsp_node.birthNewChild(Side::FRONT); - Purple Line is the split line...";
		}
		if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_DOWN))
		{
			bsp_node.eliminateAllChildren();
			bsp_node.birthNewChild(Side::BACK);
			frame_label = "bsp_node.birthNewChild(Side::BACK); - Purple Line is the split line...";
		}
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