#include "TwilightEngine.hpp"

TwilightEngine::TwilightEngine(Vector<float> new_window_size, std::string new_name):
window_size(new_window_size), session_name(new_name)
{
	emergency_exit = false;
	max_fps = 60;
}

void TwilightEngine::enter()
{
	InitWindow(window_size.getX(), window_size.getY(), session_name.c_str());
	SetTargetFPS(max_fps);
	warnings_left = 10;
	errors_left = 0;
	has_started = true;

	// renderer.addRenderObject(
	// 			new Line2D(
	// 					Vector<float>(50, 50),
	// 					Vector<float>(200, 200),
	// 					RED
	// 						)
	// 							);
								
	// renderer.addRenderObject(
	// 			new Line2D(
	// 					Vector<float>(200, 50),
	// 					Vector<float>(50, 200),
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
	std::vector<Vector<float>> points;
	for(int i = 0; i != 8; i++)
	{
		points.push_back(Vector<float>(window_size.getX() / 2, window_size.getY() / 2));
	}
	//corner points.
	points.at(0) += Vector<float>(-70, -70);
	points.at(2) += Vector<float>(+70, -70);
	points.at(4) += Vector<float>(+70, +70);
	points.at(6) += Vector<float>(-70, +70);
	
	points.at(1) += Vector<float>(-0, -120);
	points.at(3) += Vector<float>(+120, -0);
	points.at(5) += Vector<float>(+0, +120);
	points.at(7) += Vector<float>(-120, +0);

	Splitter splitter;
	LineMap line_map(points);

	renderer.addRenderObject(&splitter);
	renderer.addRenderObject(&line_map);

	renderer.addRenderObject(new SplitStage(&line_map, &splitter));

	while(!WindowShouldClose() || emergency_exit)
	{
		for(int i = 0; i != renderer.getRenderObjects()->size(); i++)
		{
			renderer.getRenderObjects()->at(i)->update();
		}
		renderer.startDrawing();
		renderer.drawContents();
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