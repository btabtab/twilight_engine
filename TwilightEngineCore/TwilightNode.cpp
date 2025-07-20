#include "TwilightNode.hpp"

//The ID will be equal to -1 if it is not set.
TwilightNode::TwilightNode(int new_id)
: ID(new_id)
{
}
int TwilightNode::getID()
{
	return ID;
}

std::vector<TwilightNode*>* TwilightNode::getChildren()
{
	return &children;
}
void TwilightNode::addChild(TwilightNode* child)
{
	children.push_back(child);
}

void TwilightNode::removeChild(int target_index)
{
	for(int i = 0; i != children.size(); i++)
	{
		if(i == target_index)
		{
			delete children.at(i);
			children.erase(children.begin() + i);
			return;
		}
	}
}

void TwilightNode::clearChildren()
{
	children.clear();
}

std::string TwilightNode::getType()
{
	return "TwilightNode";
}


void TwilightNode::updateChildren()
{
	for(auto& child : children)
	{
		if(child != nullptr)
		{
			child->update();
		}
	}
}
void TwilightNode::drawChildren()
{
	for(auto& child : children)
	{
		if(child != nullptr)
		{
			child->draw();
		}
	}
}
