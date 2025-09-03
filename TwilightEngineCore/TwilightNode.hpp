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
	void setName(std::string new_name);
	std::string getName();
	virtual ~TwilightNode() = default;
	virtual void update();
	virtual std::string getType();

	//Returns how many bytes the node is consuming.
	virtual size_t getBytesConsumed()
	{
		return sizeof(*this);
	}
};