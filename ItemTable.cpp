#include "ItemTable.h"
#include <iostream>
#include <fstream>

Items::Items()					//constructor
{
	size = 500;				//table size initialized
	itemTable.resize(size); //resize table
}


//modulo hash
int Items::HashF(int key)
{
	return key % size;
}

//inserts tuple into hash table using modulo hashing and linear probing for collision strategy
bool Items::Insert(int key, item value)
{
  int position = HashF(key);
  int probed = 0;
  
  while(probed < size)
  {
    if (itemTable.at(position).isEmpty)
    {
      itemTable.at(position) = value;
      itemTable.at(position).isEmpty = false;
	  itemList.push_back(&itemTable.at(position));

      return true;
    }
	else if (!itemTable.at(position).isEmpty && key == itemTable.at(position).id)
	{
		return false;
	}
    
    position = (position + 1) % size;
    probed++;
  }
    
    return false;
}

//Updates specific item in the table
bool Items::Update(vector<string> values)
{
	
	int key = stoi(values.at(0));
	int position = HashF(key);
	int probed = 0;
	item value;
	value.id = key;
	value.name = values.at(1);
	value.type = values.at(2);
	value.rarity = values.at(3);
	value.price = values.at(4);
	value.isEmpty = false;


	while (probed < size)
	{
		if (itemTable.at(position).id == key)
		{
			itemTable.at(position) = value;
			return true;
		}

		position = (position + 1) % size;
		probed++;
	}

	return false;
}

//ouputs all matches from provided input
bool Items::Select(vector<string> values)
{
	item value;
	value.name = values.at(1);
	value.type = values.at(2);
	value.rarity = values.at(3);
	value.price = values.at(4);
	value.isEmpty = false;

	if (values.at(0) != "*")
	{
		int key = stoi(values.at(0));
		value.id = key;
		int position = HashF(key);
		int probed = 0;
		while (probed < size)
		{
			if (itemTable.at(position).id == key && itemTable.at(position).name == value.name && itemTable.at(position).type == value.type && itemTable.at(position).rarity == value.rarity && itemTable.at(position).price == value.price)
			{
				cout << "Found (" << itemTable.at(position).id << "|" << itemTable.at(position).name << "|" << itemTable.at(position).type << "|" << itemTable.at(position).rarity << "|" << itemTable.at(position).price << ")" << endl;
				return true;
			}

			position = (position + 1) % size;
			probed++;
		}

		return false;
	}

	else		//if key is a *
	{
		int counter = 0;
		list<item*>::iterator it;

		for (it = itemList.begin(); it != itemList.end(); ++it)
		{
			if (value.name == (*it)->name || value.name == "*")
			{
				if (value.type == (*it)->type || value.type == "*")
				{
					if (value.rarity == (*it)->rarity || value.rarity == "*")
					{
						if (value.price == (*it)->price || values.at(4) == "*")
						{
							if (counter == 0)
							{
								cout << "Found ";
							}
							counter++;
							cout << "(" << (*it)->id << "|" << (*it)->name << "|" << (*it)->type << "|" << (*it)->rarity << "|" << (*it)->price << ")" << endl;
						}
					}
				}
			}
		}

		if (counter > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

//deletes all possible items given input
bool Items::Delete(vector<string> values)
{
	item value;
	value.name = values.at(1);
	value.type = values.at(2);
	value.rarity = values.at(3);
	value.price = values.at(4);
	value.isEmpty = false;

	if (values.at(0) != "*")
	{
		int key = stoi(values.at(0));
		value.id = key;
		int position = HashF(key);
		int probed = 0;
		while (probed < size)
		{
			if (itemTable.at(position).id == key && itemTable.at(position).name == value.name && itemTable.at(position).type == value.type && itemTable.at(position).rarity == value.rarity && itemTable.at(position).price == value.price)
			{
				cout << "Deleted (" << itemTable.at(position).id << "|" << itemTable.at(position).name << "|" << itemTable.at(position).type << "|" << itemTable.at(position).rarity << "|" << itemTable.at(position).price << ")" << endl;
				itemTable.at(position).id = -1;
				itemTable.at(position).name = " ";
				itemTable.at(position).type = " ";
				itemTable.at(position).rarity = " ";
				itemTable.at(position).price = " ";
				itemTable.at(position).isEmpty = true;
				return true;
			}

			position = (position + 1) % size;
			probed++;
		}

		return false;
	}

	else	//if given *
	{
		int counter = 0;
		list<item*>::iterator it;

		for (it = itemList.begin(); it != itemList.end(); ++it)
		{
			if (value.name == (*it)->name || value.name == "*")
			{
				if (value.type == (*it)->type || value.type == "*")
				{
					if (value.rarity == (*it)->rarity || value.rarity == "*")
					{
						if (value.price == (*it)->price || values.at(4) == "*")
						{
							if (counter == 0)
							{
								cout << "Deleted ";
							}
							counter++;
							cout << "(" << (*it)->id << "|" << (*it)->name << "|" << (*it)->type << "|" << (*it)->rarity << "|" << (*it)->price << ")" << endl;
							(*it)->id = -1;
							(*it)->name = " ";
							(*it)->type = " ";
							(*it)->rarity = " ";
							(*it)->price = " ";
							(*it)->isEmpty = true;
						}
					}
				}
			}
		}

		if (counter > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


vector<item> Items::getTable() 
{
  return itemTable;
}

//writes table data to a file
void Items::Write()
{
	ofstream fout;
	fout.open("itemsOutput.txt");

	list<item*>::iterator it;
	fout << "ID" << endl;
	fout << "ID,NAME,TYPE,RARITY,PRICE" << endl;


	for (it = itemList.begin(); it != itemList.end(); ++it)
	{
		if ((*it)->isEmpty == false)
		{
			fout << (*it)->id << "|" << (*it)->name << "|" << (*it)->type << "|" << (*it)->rarity << "|" << (*it)->price << endl;
		}
	}
	fout.close();
}