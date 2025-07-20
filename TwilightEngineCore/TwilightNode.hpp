#pragma once

#include <raylib.h>
#include <vector>
#include <string>

#include "Renderables/RenderObject.hpp"
class TwilightNode: public RenderObject
{
private:
	int ID;
	std::string name;
	std::vector<TwilightNode*> children;
protected:
public:
	int getID();
	std::vector<TwilightNode*>* getChildren();
	void addChild(TwilightNode* child);
	void removeChild(int target_index);
	void clearChildren();
	void updateChildren();
	void drawChildren();
	TwilightNode(int new_id = -1);
	virtual ~TwilightNode() = default;
	//This handles updating the node and defines it's behaviour.
	virtual std::string getType() = 0;
};