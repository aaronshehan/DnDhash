#pragma once

#include <vector>
#include <list>
#include "Customer.h"

class Customers
{
	private:
	  int size;								//table size
	  vector<customer> customerTable;		//vector stores customer structure
	  list<customer*> customerList;			//linked list for secondary index
	public:
	  Customers();							//constructor
	  bool Insert(int key, customer value);
	  bool Update(vector<string> values);
	  bool Select(vector<string> values);
	  bool Delete(vector<string> values);
	  void Write();
	  int HashF(int key);					//hash function
	  int secondHashF(int key);
	  vector<customer> getTable();
};