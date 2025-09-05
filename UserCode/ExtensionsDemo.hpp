/*
	 -------------------------------------------------------------------------------
	/
	|		This is a file that will be used for showing off and testing all of the
	|		Extra features of the TwilightNodeClass.
	|		Ideally it will also provide handy for later testing and debugging,
	|		but hopefully that won't be needed.
	\
	 -------------------------------------------------------------------------------
*/
#pragma once

#include "../TwilightEngineCore/TwilightNode.hpp"
#include "../TwilightEngineCore/Renderables/RenderClasses.hpp"

class TwilightExtensionDemo : public RenderObject2D
{
	private:
	public:
	TwilightExtensionDemo()
	{
		std::cout << "KB consumed by extensions test class: " << (float)((float)getBytesConsumed() / 1024.f) << "\n";
	}

	std::string getType()
	{
		return "TwilightExtensionDemo";
	}
};