#pragma once

#include <vector>
#include <list>
#include "Spell.h"

using namespace std;

class Spells
{
	private:
		int size;					//table size
		vector<spell> spellTable;	//vector of spell structures
		list<spell*> spellList;		//linked list for secondary index
	public:
		Spells();					//constructor
		int HashF(string key);		//hash function
		bool Insert(string key, spell value);
		bool Update(vector<string> values);
		bool Select(vector<string> values);
		bool Delete(vector<string> values);
		void Write();
		vector<spell> getTable();
};