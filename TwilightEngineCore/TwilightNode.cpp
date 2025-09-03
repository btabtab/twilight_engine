#include "TwilightNode.hpp"

//The ID will be equal to -1 if it is not set.
TwilightNode::TwilightNode(int new_id)
: ID(new_id)
{
}
int TwilightNode::getID() { return ID; }

void TwilightNode::update() {
    // Default implementation
}

std::string TwilightNode::getType() {
    return "TwilightNode";
}
