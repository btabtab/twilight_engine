/*
	This is an attempt at making a sort of "Tracker".
	as in the old DemoScene music machine kind of thing.

	I'm gonna sample some of my Brother's guitars for the
	sounds of the tracker.
*/

#pragma once

#include <raylib.h>
#include <vector>

#include "TwilightNode.hpp"

class SoundLibrary
{
	private:
	std::vector<Sound> sounds;
	public:
	SoundLibrary()
	{
	}
	Sound* getSound(int index)
	{
		return &sounds.at(index);
	}
};

class LakeBeat
{
	private:
	public:

	Sound* chosen_sound;
	int duration;
	void play()
	{
		PlaySound(*chosen_sound);
	}
};

class LakeChannel
{
private:
	std::vector<LakeBeat> beats;
	int position;
public:
	LakeChannel():
		position(0)
	{
	}
	void playNextBeat()
	{
		if(position < beats.size())
		{
			beats.at(position).play();
		}
		position++;
	}
};

class LakeTracker: public TwilightNode
{
	private:
	LakeChannel channels[10];
	public:
	void 
	void play()
	{
		for(int i = 0; i != 10; i++)
		{
			channels[i].playNextBeat();
		}
	}
};