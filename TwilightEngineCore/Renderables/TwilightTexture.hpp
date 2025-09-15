#pragma once

#include <raylib.h>
#include <string>
#include <iostream>

class TwilightTexture
{
private:
	/*
		This is the what will be used to grab the texture from
		the texture manager, as the user will be able to add
		textures and their own IDs.
	*/
	int ID;
	Texture texture;
	public:
	TwilightTexture(std::string file_name, int new_ID)
	{
		ID = new_ID;
		std::cout << "Trying to load texture: " << file_name;
		file_name = "resources/" + file_name;
		std::cout << " from " + file_name << "\n";
		texture = LoadTexture(file_name.c_str());
	}
	//Compares the relevant ID to the objects ID to see if they match.
	bool doesIDMatch(int comparison_ID)
	{
		return ID == comparison_ID;
	}
	Texture* getTextureData()
	{
		return &texture;
	}

	std::string list()
	{
		std::cout << "texture ID = " << ID << "\n";
	}

	~TwilightTexture()
	{
	}
};