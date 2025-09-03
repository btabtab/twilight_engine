#pragma once

#include <math.h>

#include "raylib.h"
#include "../TwilightEngineCore/Renderables/RenderClasses.hpp"

class CosSinGrid : public RenderObject2D
{
private:
	unsigned char grid_width = 0xff, grid_height = 0xff;
	int grid_scale = 1;
	bool grid_states[0xff][0xff];

	int hold_me_close = 0;

	std::vector<Line2D*> lines;

public:
	CosSinGrid()
	{
		for (int x = 0; x != grid_width; x++)
		{
			for (int y = 0; y != grid_height; y++)
			{
				grid_states[x][y] = 0x00;
			}
		}
		for (int i = 0; i != 0xff; i++)
		{
			grid_states[(0xff >> 1) + (int)(sin(i) * 100)][i] = true;
		}
		processLines();
		std::cout << "There are: " << lines.size() << " lines in total, taking up " << sizeof(Line2D) * lines.size() << " bytes\n"; 
		
		return;
		for (int i = 0; i != 4; i++)
		{
			drawBoxOntoGrid(
				Point<int>(
					rand() % 0xfb,
					rand() % 0xfb),
				Point<int>(
					rand() % 0x20,
					rand() % 0x20));
		}
	}
	void processLines()
	{
		std::cout << "Processing Lines\n";
		for(int x = 0; x != 0xff; x++)
		{
			for(int y = 0; y != 0xff; y++)
			{
				if(grid_states[x][y])
				{

					for(int x_2 = x; x_2 != 0xff; x_2++)
					{
						for(int y_2 = y; y_2 != 0xff; y_2++)
						{
							if(grid_states[x_2][y_2])
							{
								lines.push_back(
												new Line2D(
																Point<float>(x, y),
																Point<float>(x_2, y_2),
																WHITE
															)
												);
							}
						}
					}
				}
			}
		}
	}
	
	void drawBoxOntoGrid(Point<int> start, Point<int> dimensions)
	{
		for (int x = start.getX(); x != 0xff && x != (start.getX() + dimensions.getX()); x++)
		{
			grid_states[x][start.getY()] = true;
			grid_states[x][start.getY() + dimensions.getY()] = true;
		}
		for (int y = start.getY(); y != 0xff && y != (start.getY() + dimensions.getY()); y++)
		{
			grid_states[start.getX()][y] = true;
			grid_states[start.getX() + dimensions.getX()][y] = true;
		}
	}

	void draw() override
	{
		if (0xff == hold_me_close)
		{
			hold_me_close = 0;
		}
		for (int x = 0; x != grid_width; x++)
		{
			for (int y = 0; y != grid_height; y++)
			{
				DrawRectangle(
					(x * grid_scale) + grid_scale,
					(y * grid_scale) + grid_scale,
					grid_scale,
					grid_scale,
					(Color){
						(unsigned char)(x * (255 / grid_width)),
						(unsigned char)(y * (255 / grid_height)),
						(unsigned char)((x + y) * (255 / (grid_width + grid_height))),
						0xff});

				int elevated_hold_me_close = hold_me_close + 1;
				if (grid_states[x][y] && (hold_me_close == y || hold_me_close == x))
				{
					// DrawRectangle(
					// (x * grid_scale) + grid_scale,
					// (y * grid_scale) + grid_scale,
					// grid_scale,
					// grid_scale,
					// (Color){
					// 	(unsigned char)(255 - (x * (255 / grid_width))),
					// 	(unsigned char)(255 - (y * (255 / grid_height))),
					// 	(unsigned char)(255 - ((x + y) * (255 / (grid_width + grid_height)))),
					// 	0xff}
					// );
					DrawCircle(x, y, 3.f,
							   (Color){
								   (unsigned char)(255 - (x * (255 / grid_width))),
								   (unsigned char)(255 - (y * (255 / grid_height))),
								   (unsigned char)(255 - ((x + y) * (255 / (grid_width + grid_height)))),
								   0xff});
				}
				// board[x][y] = false;
			}
		}
		drawLineCorrelation();
		hold_me_close++;
	}

	void drawLineCorrelation()
	{
		for(int i = 0; i != lines.size(); i++)
		{
			if(i == hold_me_close)
			{
				lines.at(i)->draw();
			}
		}
	}

	std::string getType() override
	{
		return "DemoGrid";
	}

	~CosSinGrid()
	{
		for(auto line: lines)
		{
			delete line;
		}
	}
};
