#pragma once

#include <iostream>
#include <string>
#include <vector>

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
	int generation;
	/*
		Here is a breakdown of how their DNA will work:
		0, 1, 2 -	Their RGB values.
		3, 4 -
		4, 5 -		Their maximum size.
		6, 7, 8, 9 -What foods they enjoy.
		10 -		Their metabolism.
		11 -		How old they can get at maximum.
		31 -		How much they can move.
	*/
	unsigned char DNA[32];

	Point<float> position;

public:
	// Used for the first 3 grublings.
	Grubling() : position((GetScreenWidth() / 2), (GetScreenHeight() / 2)),
				 generation(0)
	{
		age = 0;
		position = position + Point<float>(
								  GetRandomValue(-30, 30),
								  GetRandomValue(-30, 30));
		for (int i = 0; i != 32; i++)
		{
			DNA[i] = rand() % 0xff;
		}
		DNA[11] = 0x0AF0 / 60;
		DNA[31] = rand() % 5;
	}
	// Make a new grubling from 2 parents.
	Grubling(Grubling *mother, Grubling *father) : position(mother->getPosition().getX(), father->getPosition().getY()),
												   generation(mother->getGeneration() + 1)
	{
		age = 0;
		position = position + Point<float>(
								  GetRandomValue(-30, 30),
								  GetRandomValue(-30, 30));
		for (int i = 0; i != 16; i++)
		{
			DNA[i] = (mother->getGene(i) + father->getGene(i));
			if(DNA[i] < 6)
			{
				DNA[i] += GetRandomValue(-5, 5);
			}
			else
			{
				DNA[i] += GetRandomValue(0, 5);
			}
		}
	}
	int getGeneration()
	{
		return generation;
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
			WHITE);
		DrawCircle(
			position.getX(),
			position.getY(),
			10,
			(Color){
				getGene(0),
				getGene(1),
				getGene(11),
				0xff});
	}
	void update()
	{
		position = position + Point<float>(
								  GetRandomValue(-DNA[31], DNA[31]),
								  GetRandomValue(-DNA[31], DNA[31]));
		if(position.getX() < 0)
		{
			position.setX(3);
		}
		if(position.getY() < 0)
		{
			position.setY(3);
		}
		if(GetScreenWidth() < position.getX())
		{
			position.setX(3);
		}
		if(GetScreenHeight() < position.getY())
		{
			position.setY(3);
		}

		age++;
		if (DNA[11] < age)
		{
			deleteMe();
		}
	}

	size_t getBytesConsumed()
	{
		size_t ret = sizeof(DNA);
		ret += sizeof(age);
		ret += sizeof(generation);
		ret += sizeof(position);
		return ret;
	}
};

class GrublingCollisionManager : public RenderObject2D
{
private:
	int amount_of_grublings;
	std::vector<RenderObject2D*>* render_objects;
	std::vector<Grubling*> grublings;

public:
	GrublingCollisionManager(std::vector<RenderObject2D*>* new_render_objects):
	render_objects(new_render_objects)
	{
		amount_of_grublings = 0;
	}
	void draw()
	{
		DrawText(("Grublings: " + std::to_string(amount_of_grublings)).c_str(), 5, 5, 10, WHITE);
	}
	std::string getType()
	{
		return "GrublingCollisionManager";
	}
	void getGrublings(std::vector<RenderObject2D *>* render_objects)
	{
		grublings.clear();
		for (auto current_object : *render_objects)
		{
			if (current_object->getType() == "Grubling")
			{
				grublings.push_back((Grubling*)current_object);
			}
		}
		amount_of_grublings = grublings.size();
	}

	void update()
	{
		std::vector<Grubling*> new_grubling_list;
		for (int i = 0; i < grublings.size(); i++)
		{
			for (int m = 0; m < grublings.size(); m++)
			{
				if (m == i)
				{
					m++;
				}
				if (grublings.size() <= m)
				{
					break;
				}

				if(
					grublings.at(i)->getPosition().getX() - 10 < grublings.at(m)->getPosition().getX()
					&&
					grublings.at(m)->getPosition().getX() < grublings.at(i)->getPosition().getX() + 10 
					&&
					grublings.at(i)->getPosition().getY() - 10 < grublings.at(m)->getPosition().getY()
					&&
					grublings.at(m)->getPosition().getY() < grublings.at(i)->getPosition().getY() + 10
					)
				{
					if(amount_of_grublings < 200 && 50 < GetRandomValue(0, 0x100))
					{
						new_grubling_list.push_back(new Grubling(grublings.at(i), grublings.at(m)));
					}
					if(10 < GetRandomValue(0, 0x100))
					{
						grublings.at(m)->deleteMe();
					}
				}
			}
		}
		for(auto new_grubling : new_grubling_list)
		{
			render_objects->push_back(new_grubling);
		}
	}

	~GrublingCollisionManager()
	{
	}
};