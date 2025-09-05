#pragma once
#include <vector>
#include "TwilightNode.hpp"

#define MEMORY_LOG_MAXIMUM 100
#define FRAMERATE_LOG_MAXIMUM 60

class TwilightMetrics : public TwilightNode
{
private:
	//Best kept to 60 items MAX.
	std::vector<float> framerate_history;
	//Best kept to 100 items MAX.
	std::vector<float> memory_consumed_history;

public:
	TwilightMetrics()
	{
	}

	void addToMemoryHistory(size_t new_entry)
	{
		memory_consumed_history.push_back(new_entry);
		if((MEMORY_LOG_MAXIMUM - 1) < memory_consumed_history.size())
		{
			memory_consumed_history.erase(memory_consumed_history.begin());
		}
	}

	std::vector<float>* getMemoryConsumedHistory()
	{
		return &memory_consumed_history;
	}
	std::vector<float>* getFramerateHistory()
	{
		return &framerate_history;
	}

	void updateFramerateHistory(int new_framerate_value)
	{
		framerate_history.push_back(new_framerate_value);
		if((FRAMERATE_LOG_MAXIMUM - 1) < framerate_history.size())
		{
			framerate_history.erase(framerate_history.begin());
		}
	}
	/*
		Best called after a period of time,
		doing it too frequently will add to
		any lag and make the metrics system
		cause issues it is designed to solve.
	*/
	int getAverageFramerate()
	{
		if(framerate_history.empty())
		{
			return 0;
		}

		int ret = 0;
		for(int value_to_add : framerate_history)
		{
			ret += value_to_add;
		}
		return ret / framerate_history.size();
	}

	void generalUpdate(size_t memory_to_add, int framerate_to_log)
	{
		addToMemoryHistory(memory_to_add);
		updateFramerateHistory(framerate_to_log);
	}

	size_t getBytesConsumed()
	{
		size_t ret = sizeof(this);
		ret += (memory_consumed_history.size() * sizeof(size_t));
		ret += (framerate_history.size() * sizeof(int));
		return ret;
	}
	std::string getType()
	{
		return "TwilightMetrics";
	}
};