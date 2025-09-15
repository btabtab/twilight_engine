#pragma once

#include <vector>

#include "Renderables/RenderObject.hpp"
#include "Renderables/TwilightTexture.hpp"
class TextureManager : TwilightNode
{
	private:
	std::vector<TwilightTexture> textures;
	public:
	TextureManager()
	{
	}

	void addTexture(std::string file_name, int texture_ID_to_use)
	{
		// file_name = "resources/" + file_name;
		textures.push_back(TwilightTexture(file_name, texture_ID_to_use));
	}

	TwilightTexture* getTwilightTextureData(int search_ID)
	{
		for(int i = 0; i != textures.size(); i++)
		{
			if(textures.at(i).doesIDMatch(search_ID))
			{
				return &textures.at(i);
			}
		}
		std::cout << "[ Error ] :> texture ID " << search_ID << " not found...";
		exit(0);
	}
	
	size_t getBytesConsumed()
	{
		return sizeof(*this);
	}

	void list()
	{
		std::cout << "Texture IDs:\n";
		for(auto texture : textures)
		{
			std::cout << "\t";
			texture.list();
		}
	}
};