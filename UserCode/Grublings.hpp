#pragma once

/*
	This is a demo to stress test the features and tools
	currently in TwilightEngine.
*/

#include "../TwilightEngineCore/Renderables/RenderClasses.hpp"

/*
	Grublings are little creatures with 32 chars of DNA, which
	determines their inherent traits, such as how long they
	live, what they can eat, and their features.
*/
class Grubling : public RenderObject2D
{
private:
	int age;
	/*
		Here is a breakdown of how their DNA will work:
		0, 1, 2 -	Their RGB values.
		3, 4 -		Their maximum age.
		4, 5 -		Their maximum size.
		6, 7, 8, 9 -What foods they enjoy.
		10 -		Their metabolism.
	*/
	unsigned char DNA[32];

	Point<float> position;
public:
	//Used for the first 3 grublings.
	Grubling():
	position((GetScreenWidth() / 2), (GetScreenHeight() / 2))
	{
		for(int i = 0; i != 3; i++)
		{
			DNA[i] = 0xff >> 1;
		}
		for(int i = 3; i != 32; i++)
		{
			DNA[i] =  0x0f;
		}
	}
	//Make a new grubling from 2 parents.
	Grubling(Grubling* mother, Grubling* father):
	position(mother->getPosition().getX(), father->getPosition().getY())
	{
		for(int i = 0; i != 16; i++)
		{
			DNA[i] = mother->getGene(i);
			DNA[i] = father->getGene(16 + i);
		}
	}
	unsigned char getGene(int i)
	{
		return DNA[i];
	}

	std::string getType()
	{
		return "Grubling";
	}
	Point<float> getPosition()
	{
		return position;
	}
	void draw()
	{
		DrawCircle(
			position.getX(),
			position.getY(),
			12,
			WHITE
			);
		DrawCircle(
			position.getX(),
			position.getY(),
			10,
			(Color)
			{
				getGene(0),
				getGene(1),
				getGene(2),
				0xff
			}
			);
	}
};