#pragma once

#include <string>

using namespace std;

struct customer
{
	int id;
	string name;
	string race;
	string level;
	string clss;
	string debt;
	bool isEmpty;
	customer() 
	{ 
		isEmpty = true; 
		id = -1;
		name = " ";
		race = " ";
		level = " ";
		clss = " ";
		debt = " ";
	}
};