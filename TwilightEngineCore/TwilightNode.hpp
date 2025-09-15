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
	bool was_delete_requested;
	bool is_texture_manager_called_for;

public:
	int getID();
	TwilightNode(int new_id = -1);
	void setName(std::string new_name);
	std::string getName();
	virtual ~TwilightNode() = default;
	virtual void update();
	virtual std::string getType();
	
	void deleteMe()
	{
		was_delete_requested = true;
	}
	bool wasDeleteRequested()
	{
		return was_delete_requested;
	}

	//Returns how many bytes the node is consuming.
	virtual size_t getBytesConsumed()
	{
		return sizeof(*this);
	}
};