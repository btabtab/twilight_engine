#include "TwilightNode.hpp"

//The ID will be equal to -1 if it is not set.
TwilightNode::TwilightNode(int new_id)
: ID(new_id)
{
    if(!new_id)
    {
        ID = rand() % 0xffff;
    }
}
int TwilightNode::getID() { return ID; }

void TwilightNode::setName(std::string new_name)
{
    name = new_name;
}

std::string TwilightNode::getName()
{
    return name;
}

void TwilightNode::update() {
    // Default implementation
}

std::string TwilightNode::getType() {
    return "TwilightNode";
}
