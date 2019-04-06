#pragma once

#include <string>

using namespace std;

struct item
{
	int id;
	string name;
	string type;
	string rarity;
	string price;
	bool isEmpty;
	item() 
	{ 
		isEmpty = true;
		id = -1;
		name = " ";
		type = " ";
		rarity = " ";
		price = " ";
	}
};