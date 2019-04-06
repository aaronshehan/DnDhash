#include "CustomerTable.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <fstream>

Customers::Customers()		//constructor
{
	size = 500;
	customerTable.resize(size);
}

//inserts tuple into table using mid square hashing and double hash for collision strategy
bool Customers::Insert(int key, customer value)
{
	int position = HashF(key);
	int probed = 0;

	while (probed < size)
	{
		if (customerTable.at(position).isEmpty)
		{
			customerTable.at(position) = value;
			customerTable.at(position).isEmpty = false;
			customerList.push_back(&customerTable.at(position));

			return true;
		}
		else if (!customerTable.at(position).isEmpty && key == customerTable.at(position).id)
		{
			return false;
		}
		
		probed++;

		position = (HashF(key) + (probed * secondHashF(key))) % size;
	}

	return false;
}

//Updates table if match found
bool Customers::Update(vector<string> values)
{
	int key = stoi(values.at(0));
	int position = HashF(key);
	int probed = 0;
	customer value;
	value.id = key;
	value.name = values.at(1);
	value.race = values.at(2);
	value.level = values.at(3);
	value.clss = values.at(4);
	value.debt = values.at(5);
	value.isEmpty = false;


	while (probed < size)
	{
		if (customerTable.at(position).id == key)
		{
			customerTable.at(position) = value;

			return true;
		}
		probed++;

		position = (HashF(key) + (probed * secondHashF(key))) % size;
	}
	return false;
}

//Outputs all possible matches given the input provided
bool Customers::Select(vector<string> values)
{
	customer value;
	value.name = values.at(1);
	value.race = values.at(2);
	value.level = values.at(3);
	value.clss = values.at(4);
	value.debt = values.at(5);
	value.isEmpty = false;

	if (values.at(0) != "*")
	{
		int key = stoi(values.at(0));
		int position = HashF(key);
		int probed = 0;
		value.id = key;

		while (probed < size)
		{
			if (customerTable.at(position).id == key && customerTable.at(position).name == value.name && customerTable.at(position).race == value.race && customerTable.at(position).level == value.level && customerTable.at(position).clss == value.clss && customerTable.at(position).debt == value.debt)
			{
				cout << "Found (" << customerTable.at(position).id << "|" << customerTable.at(position).name << "|" << customerTable.at(position).race << "|" << customerTable.at(position).level << "|" << customerTable.at(position).clss << "|" << customerTable.at(position).debt << ")" << endl;
				return true;
			}

			probed++;

			position = (HashF(key) + (probed * secondHashF(key))) % size;
		}

		return false;
	}
	else
	{
		int counter = 0;
		list<customer*>::iterator it;

		for (it = customerList.begin(); it != customerList.end(); ++it)
		{
			if (value.name == (*it)->name || value.name == "*")
			{
				if (value.race == (*it)->race || value.race == "*")
				{
					if (value.level == (*it)->level || value.level == "*")
					{
						if (value.clss == (*it)->clss || value.clss == "*")
						{
							if (value.debt == (*it)->debt || value.debt == "*")
							{
								if (counter == 0)
								{
									cout << "Found ";
								}
								counter++;
								cout << "(" << (*it)->id << "|" << (*it)->name << "|" << (*it)->race << "|" << (*it)->level << "|" << (*it)->clss << "|" << (*it)->debt << ")" << endl;

							}
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

//Deletes all possible matches
bool Customers::Delete(vector<string> values)
{
	customer value;
	value.name = values.at(1);
	value.race = values.at(2);
	value.level = values.at(3);
	value.clss = values.at(4);
	value.debt = values.at(5);
	value.isEmpty = false;

	if (values.at(0) != "*")
	{
		int key = stoi(values.at(0));
		int position = HashF(key);
		int probed = 0;
		value.id = key;

		while (probed < size)
		{
			if (customerTable.at(position).id == key && customerTable.at(position).name == value.name && customerTable.at(position).race == value.race && customerTable.at(position).level == value.level && customerTable.at(position).clss == value.clss && customerTable.at(position).debt == value.debt)
			{
				cout << "Deleted (" << customerTable.at(position).id << "|" << customerTable.at(position).name << "|" << customerTable.at(position).race << "|" << customerTable.at(position).level << "|" << customerTable.at(position).clss << "|" << customerTable.at(position).debt << ")" << endl;
				customerTable.at(position).id = -1;
				customerTable.at(position).name = " ";
				customerTable.at(position).race = " ";
				customerTable.at(position).level = " ";
				customerTable.at(position).clss = " ";
				customerTable.at(position).debt = " ";
				customerTable.at(position).isEmpty = true;
				return true;
			}

			probed++;

			position = (HashF(key) + (probed * secondHashF(key))) % size;
		}

		return false;
	}
	else
	{
		int counter = 0;
		list<customer*>::iterator it;

		for (it = customerList.begin(); it != customerList.end(); ++it)
		{
			if (value.name == (*it)->name || value.name == "*")
			{
				if (value.race == (*it)->race || value.race == "*")
				{
					if (value.level == (*it)->level || value.level == "*")
					{
						if (value.clss == (*it)->clss || value.clss == "*")
						{
							if (value.debt == (*it)->debt || value.debt == "*")
							{
								if (counter == 0)
								{
									cout << "Deleted ";
								}
								cout << "(" << (*it)->id << "|" << (*it)->name << "|" << (*it)->race << "|" << (*it)->level << "|" << (*it)->clss << "|" << (*it)->debt << ")" << endl;

								(*it)->id = -1;
								(*it)->name = " ";
								(*it)->race = " ";
								(*it)->level = " ";
								(*it)->clss = " ";
								(*it)->debt = " ";
								(*it)->isEmpty = true;
								//delete *it;
								counter++;
							}
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

//mid square hash
int Customers::HashF(int key)
{
	int R = ceil(log10(size));
	int pos = key * key;
	string spos = to_string(pos);
	string mpos = spos.substr((floor(spos.size() / 2)), R);
	return stoi(mpos) % size;

}

//Second hash function used for double hash collision strategy
int Customers::secondHashF(int key) 
{
	return key % 7;
}

vector<customer> Customers::getTable()
{
	return customerTable;
}

//writes table data to a file
void Customers::Write()
{
	ofstream fout;
	fout.open("customersOutput.txt");

	list<customer*>::iterator it;
	fout << "ID" << endl;
	fout << "ID,NAME,RACE,LEVEL,CLASS,DEBT" << endl;


	for (it = customerList.begin(); it != customerList.end(); ++it)
	{
		if ((*it)->isEmpty == false)
		{
			fout << (*it)->id << "|" << (*it)->name << "|" << (*it)->race << "|" << (*it)->level << "|" << (*it)->clss << "|" << (*it)->debt << endl;
		}
	}
	fout.close();
}