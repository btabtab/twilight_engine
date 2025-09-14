#pragma once

#include "Grublings.hpp"
#include "../TwilightEngineCore/Renderables/RenderClasses.hpp"

/*
	This demo will be like the "Grublings" demo except
	it they will all manage each other and be able to
	talk to each other in a meaningful way.
*/
class BeetleNode : public Grubling
{
protected:
	BeetleNode* child;
	BeetleNode* parent;
public:
	BeetleNode(BeetleNode* new_parent = nullptr, BeetleNode* new_child = nullptr)
	{
		child = new_child;
		parent = new_parent;
	}
	void handChildDown(BeetleNode* new_child)
	{
		if(new_child == nullptr)
		{
			return;
		}
		if(child == nullptr)
		{
			child = new_child;
			child->setParent(this);
			return;
		}
		child->handChildDown(new_child);
	}
	
	/*
		Really morbid naming here...
		might keep it for the funnies.
	*/
	void tellParentImGoingToDie()
	{
	}
	
	void setChild(BeetleNode* new_child)
	{
		child = new_child;
		child->setParent(this);
	}

	Line2D getAttachmentLine()
	{
		if(child != nullptr)
		{
			return Line2D(getPosition(), getPosition());
		}
		return Line2D(getPosition(), child->getPosition());
	}
	
	void checkForTangle()
	{
		Line2D tangle_line = getAttachmentLine();
		Line2D child_tangle_line = child->getAttachmentLine();
		
		if(child == nullptr && child->getChild() == nullptr)
		{
			return;
		}
		
		if(tangle_line.intersects(child_tangle_line))
		{
		}
	}

	void reattachToOtherBeetle(BeetleNode* other_beetle)
	{
		parent = other_beetle;
		other_beetle->setChild(this);
	}

	void setParent(BeetleNode* new_parent)
	{
		parent = new_parent;
	}
	void giveChild(BeetleNode* new_child)
	{
		if(child != nullptr)
		{
			//Return here because it already has a child.
			return;
		}
		child = new_child;
	}
	void draw() override
	{
		if(child != nullptr)
		{
			Line2D(
					getPosition(),
					child->getPosition(),
					WHITE
					).draw();
			child->draw();
		}
		Grubling::draw();
	}
	void update() override
	{
		Grubling::update();
		setAge();

		if(child != nullptr)
		{
			child->update();
		}
	}
	BeetleNode* getChild()
	{
		return child;
	}
};