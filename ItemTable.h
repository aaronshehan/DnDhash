#pragma once

#include <vector>
#include <list>
#include "Item.h"

using namespace std;

class Items
{
	private:
		int size;					//table size
		vector<item> itemTable;		//vector that stores item structure
		list<item*> itemList;		//linked list for secondary index
	public:
		Items();					//constructor
		int HashF(int key);			//hash function
		bool Insert(int key, item value);
		bool Update(vector<string> values);
		bool Select(vector<string> values);
		bool Delete(vector<string> values);
		void Write();
		vector<item> getTable();
};