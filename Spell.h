#pragma once

#include <string>

using namespace std;

struct spell
{
	string name;
	string level;
	string school;
	string casting_time;
	string range;
	string components;
	string duration;
	bool isEmpty;
	spell() 
	{ 
		isEmpty = true; 
		name = " ";
		level = " ";
		school = " ";
		casting_time = " ";
		range = " ";
		components = " ";
		duration = " ";
	}
};
