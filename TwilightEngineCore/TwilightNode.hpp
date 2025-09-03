#pragma once

#include <raylib.h>
#include <vector>
#include <string>

class TwilightNode
{
private:
protected:
	int ID;
	std::string name;
public:
	int getID();
	TwilightNode(int new_id = -1);
	virtual ~TwilightNode() = default;
	virtual void update();
	virtual std::string getType();
};