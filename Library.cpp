#include "library.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

extern Spells spells;
extern Items items;
extern Customers customers;

//get input file name from user
void getUserInput()
{
  ifstream fin;
  stringstream strstream;
  string userInput, line;
  string table1, table2, table3;
  string file1, file2, file3;
  vector<string> tuple;
  
  cout << "Enter name of input file: ";
  cin >> userInput;
  fin.open(userInput.c_str());
  //get table files
  fin >> file1; fin >> table1;
  fin >> file2; fin >> table2;
  fin >> file3; fin >> table3;
  
  //determine which files to open
  if (table1 == "items")
  {
	  getSpellInput(file1);
  }
  else if (table1 == "spells")
  {
    getSpellInput(file1);
  }
  else
  {
	  getCustomerInput(file1);
  }
  
  if (table2 == "items")
  {
   getItemInput(file2);
  }
  else if (table2 == "spells")
  {
	  getSpellInput(file2);
  }
  else
  {
	  getCustomerInput(file2);
  }
  
  if (table3 == "items")
  {
	  getItemInput(file3);
  }
  else if (table3 == "spells")
  {
	  getSpellInput(file3);
  }
  else
  {
	  getCustomerInput(file3);
  }

  getline(fin,line);
fin.clear();
fin.ignore();
  
  while (getline(fin, line))
  {
	  tuple = parseString(line);	  
	  
	  if (tuple.at(0) == "DISPLAY")
	  {
		 Display();
	  }
	  else if (tuple.at(0) == "INSERT")
	  {
		 Insert(tuple.at(2), tuple.at(1));
	  }
	  else if (tuple.at(0) == "UPDATE")
	  {
		 Update(tuple.at(2), tuple.at(1));
	  }
	  else if (tuple.at(0) == "SELECT")
	  {
		  Select(tuple.at(2), tuple.at(1));
	  }
	  else if (tuple.at(0) == "DELETE")
	  {
		  Delete(tuple.at(2), tuple.at(1));
	  }
	  else if (tuple.at(0) == "WRITE")
	  {
		  Write();
	  }
  }

  fin.close();
}

//parses line from input file
//returns vector with up to three different strings
//only one string for Dipslay and Write funcions
//others functions return string for function call, scheme, and table name
vector<string> parseString(string input)
{
	string copy = input;
	vector<string>temp;
	temp.push_back(copy);
	int size = input.size();
	copy[size - 1] = '=';
	stringstream sstream;
	sstream << copy;
	vector<string> tuple;

	getline(sstream, copy, '(');
	tuple.push_back(copy);
	if (tuple.at(0) == "DISPLAY" || tuple.at(0) == "WRITE")
	{
		sstream.clear();
		return tuple;
	}

	getline(sstream, copy, '(');
	getline(sstream, copy, '=');
	sstream.clear();
	string copy2 = copy;
	reverse(copy2.begin(), copy2.end());
	sstream << copy2;
	getline(sstream, copy2, ',');
	tuple.push_back(copy2);
	reverse(tuple.at(1).begin(), tuple.at(1).end());

	for (int i = 0; i < tuple.at(1).size() + 2; i++)
	{
		copy.pop_back();
	}

	tuple.push_back(copy);
	sstream.clear();
}

//determines which object insert function to call
void Insert(string scheme, string tableName)
{
	stringstream sstream;
	sstream << scheme;
	bool isSuccess;
	string temp = scheme;
	
	if (tableName == "spells")
	{
		spell tempSpell;

		for (int i = 0; i < 7; i++)
		{
			getline(sstream, scheme, '|');
			if (i == 0)
			{
				tempSpell.name = scheme;
			}
			else if (i == 1)
			{
				tempSpell.level = scheme;
			}
			else if (i == 2)
			{
				tempSpell.school = scheme;
			}
			else if (i == 3)
			{
				tempSpell.casting_time = scheme;
			}
			else if (i == 4)
			{
				tempSpell.range = scheme;
			}
			else if (i == 5)
			{
				tempSpell.components = scheme;
			}
			else
			{
				tempSpell.duration = scheme;
			}
		}
		sstream.clear();

		isSuccess = spells.Insert(tempSpell.name, tempSpell); //insert tuple into table after successfull hash

		if (isSuccess == false)
		{
			cout << "failed to insert (" << temp << ") into " << tableName << endl;
		}
		else
		{
			cout << "Inserted (" << temp << ") into " << tableName << endl;
		}
		return;
	}

	else if (tableName == "customers")
	{
		customer tempCustomer;
	
		for (int i = 0; i < 6; i++)
		{
			getline(sstream, scheme, '|');
			if (i == 0)
			{
				int id = 0;
				stringstream s(scheme);
				s >> id;
				s.clear();
				tempCustomer.id = id;
			}
			else if (i == 1)
			{
				tempCustomer.name = scheme;
			}
			else if (i == 2)
			{
				tempCustomer.race = scheme;
			}
			else if (i == 3)
			{
				tempCustomer.level = scheme;
			}
			else if (i == 4)
			{
				tempCustomer.clss = scheme;
			}
			else
			{
				tempCustomer.debt = scheme;
			}
		}
		sstream.clear();

		isSuccess = customers.Insert(tempCustomer.id, tempCustomer);

		if (isSuccess == false)
		{
			cout << "failed to insert (" << temp << ") into " << tableName << endl;
		}
		else
		{
			cout << "Inserted (" << temp << ") into " << tableName << endl;
		}
		return;
	}

	else
	{
		item tempItem;

		for (int i = 0; i < 5; i++)
		{
			getline(sstream, scheme, '|');
			if (i == 0)
			{
				int id = 0;
				stringstream s(scheme);
				s >> id;
				s.clear();
				tempItem.id = id;
			}
			else if (i == 1)
			{
				tempItem.name = scheme;
			}
			else if (i == 2)
			{
				tempItem.type = scheme;
			}
			else if (i == 3)
			{
				tempItem.rarity = scheme;
			}
			else
			{
				tempItem.price = scheme;
			}

		}
		sstream.clear();

		isSuccess = items.Insert(tempItem.id, tempItem);

		if (isSuccess == false)
		{
			cout << "failed to insert (" << temp << ") into " << tableName << endl;
		}
		else
		{
			cout << "Inserted (" << temp << ") into " << tableName << endl;
		}

	}
}

//determines which object update method function to call
void Update(string scheme, string tableName)
{
	bool isSuccess;
	vector<string> temp = breakTuple(scheme, tableName);

	if (tableName == "spells")
	{
		isSuccess = spells.Update(temp);
	}
	else if (tableName == "customers")
	{
		isSuccess = customers.Update(temp);
	}
	else
	{
		isSuccess = items.Update(temp);

	}

	if (isSuccess == true)
	{
		cout << "Updated (" << scheme << ") in " << tableName << endl;
	}
	else
	{
		cout << "failed to update (" << scheme << ") in " << tableName << endl;
	}
}

//determines which object update method function to call
void Select(string scheme, string tableName)
{
	bool isSuccess;
	vector<string> temp = breakTuple(scheme, tableName);

	if (tableName == "spells")
	{
		isSuccess = spells.Select(temp);
	}
	else if (tableName == "customers")
	{
		isSuccess = customers.Select(temp);
	}
	else
	{
		isSuccess = items.Select(temp);

	}

	if (isSuccess == true)
	{
		//cout << "Selected (" << scheme << ") in " << tableName << endl;
	}
	else
	{
		cout << "failed to select (" << scheme << ") in " << tableName << endl;
	}
}

//parses string tuple and places each parsed element into a vector
vector<string> breakTuple(string tuple, string tableName) 
{
	stringstream sstream;
	vector<string> temp;
	int size;

	if (tableName == "spells")
	{
		size = 7;
	}
	else if (tableName == "customers")
	{
		size = 6;
	}
	else
	{
		size = 5;
	}
	sstream << tuple;
	for (int i = 0; i < size; i++)
	{
		getline(sstream, tuple, '|');
		temp.push_back(tuple);
	}
	sstream.clear();
	return temp;
}

//determines which object delete method to call
void Delete(string scheme, string tableName)
{
	vector<string> parsedTuple = breakTuple(scheme, tableName);
	bool isSuccess;

	if (tableName == "spells")
	{
		isSuccess = spells.Delete(parsedTuple);
	}
	else if (tableName == "customers")
	{
		isSuccess = customers.Delete(parsedTuple);
	}
	else
	{
		isSuccess = items.Delete(parsedTuple);
	}

	if (isSuccess == false)
	{
		cout << "Failed to delete (" << scheme << ") in " << tableName << endl;
	}
}

//calls all table object write methods
void Write()
{
	items.Write();
	spells.Write();
	customers.Write();
}


//get file input for Items table
void getItemInput(string filename)
{
  item tempItem;
  ifstream fin;
  bool isSuccess;
  stringstream sstream;
  
  
  
  fin.open(filename.c_str());
  
  string key, scheme, line;
  
  getline(fin, key);
  getline(fin, scheme);
  while(getline(fin, line))
  {
    sstream << line;
    for (int i = 0; i < 5; i++)
    {
      getline(sstream, line, '|');
      if (i == 0)
      {
        int id = 0;
        stringstream s(line);
        s >> id;
        s.clear();
        tempItem.id = id;
      }
      else if (i == 1)
      {
      tempItem.name = line;
      }
      else if (i == 2)
      {
      tempItem.type = line;
      }
      else if (i == 3)
      {
        tempItem.rarity = line;
      }
      else
      {
         tempItem.price = line;
      }
      
    }
    sstream.clear();
  
   isSuccess = items.Insert(tempItem.id, tempItem);
   
   if(isSuccess == false)
   {
     cout << "Item with id: " << tempItem.id << " could not be inserted" << endl;
   }
  }
  fin.close();
}

//get file input for Spells table
void getSpellInput(string filename)
{
  spell tempSpell;
  ifstream fin;
  bool isSuccess;
  stringstream sstream;
  
  
  
  fin.open(filename.c_str());
  
  string key, scheme, line;
  
  getline(fin, key);
  getline(fin, scheme);
  while(getline(fin, line))
  {
    sstream << line;
    for (int i = 0; i < 7; i++)
    {
      getline(sstream, line, '|');
      if (i == 0)
      {
        tempSpell.name = line;
      }
      else if (i == 1)
      {
        tempSpell.level = line;
      }
      else if (i == 2)
      {
        tempSpell.school = line;
      }
      else if (i == 3)
      {
        tempSpell.casting_time = line;
      }
      else if (i == 4)
      {
        tempSpell.range = line;
      }
      else if (i == 5)
      {
        tempSpell.components = line;
      }
      else
      {
        tempSpell.duration = line;
      }
    }
    sstream.clear();
   
   isSuccess = spells.Insert(tempSpell.name, tempSpell); //insert tuple into table after successfull hash
   
   if(isSuccess == false)
   {
     cout << "Spell with name: " << tempSpell.name << " could not be inserted" << endl;
   }
  }
  fin.close();
}


//get file input for Customers table
void getCustomerInput(string filename)
{
	customer tempCustomer;
	ifstream fin;
	bool isSuccess;
	stringstream sstream;



	fin.open(filename.c_str());

	string key, scheme, line;

	getline(fin, key);
	getline(fin, scheme);
	while (getline(fin, line))
	{
		sstream << line;
		for (int i = 0; i < 6; i++)
		{
			getline(sstream, line, '|');
			if (i == 0)
			{
				int id = 0;
				stringstream s(line);
				s >> id;
				s.clear();
				tempCustomer.id = id;
			}
			else if (i == 1)
			{
				tempCustomer.name = line;
			}
			else if (i == 2)
			{
				tempCustomer.race = line;
			}
			else if (i == 3)
			{
				tempCustomer.level = line;
			}
			else if (i == 4)
			{
				tempCustomer.clss = line;
			}
			else
			{
				tempCustomer.debt = line;
			}
		}
		sstream.clear();

		isSuccess = customers.Insert(tempCustomer.id, tempCustomer);

		if (isSuccess == false)
		{
			cout << "Customer with id: " << tempCustomer.id << " could not be inserted" << endl;
		}
	}
	fin.close();
}

//display all table data
void Display()
{
  ofstream fout;
  fout.open("DisplayOutput.txt");
  vector<item> itemTable = items.getTable();
  vector<spell> spellTable = spells.getTable();
  vector<customer> customerTable = customers.getTable();
  int size = 500;

  fout << "ID" << right << setw(18) << "NAME" << right << setw(25) << "TYPE" << right << setw(22) << "RARITY" << right << setw(18) << "PRICE" << endl;
  
  for (int i = 0; i < size; i++)
  {
    if(!itemTable.at(i).isEmpty)
    {
      fout << left << setw(10) << itemTable.at(i).id << left << setw(30) << itemTable.at(i).name << left << setw(20) << itemTable.at(i).type << left << setw(20) << itemTable.at(i).rarity << itemTable.at(i).price << endl;
    }
  }

  fout << endl << endl;
  fout << "NAME" << right << setw(22) << "LEVEL" << right << setw(17) << "SCHOOL" << right << setw(20) << "CASTING_TIME" << right << setw(17) << "RANGE" << right << setw(36) << "COMPONENTS" << right << setw(58) << "DURATION" << endl;

for (int i = 0; i < size; i++)
{
	if (!spellTable.at(i).isEmpty)
	{
		fout << left << setw(23) << spellTable.at(i).name << left << setw(8) << spellTable.at(i).level << left << setw(20) << spellTable.at(i).school << left << setw(20) << spellTable.at(i).casting_time << left << setw(30) << spellTable.at(i).range << left << setw(60) << spellTable.at(i).components << left << setw(15) << spellTable.at(i).duration << endl;
	}
}

	fout << endl << endl;
	fout << left << setw(10) <<"ID" << right << setw(7) << "NAME" << right << setw(20) << "RACE" << right << setw(15) << "LEVEL" << right << setw(15) << "CLASS" << right << setw(15) << "DEBT" << endl;

	for (int i = 0; i < size; i++)
	{
		if (!customerTable.at(i).isEmpty)
		{
			fout << left << setw(10) << customerTable.at(i).id << left << setw(20) << customerTable.at(i).name << left << setw(18) << customerTable.at(i).race << left << setw(14) << customerTable.at(i).level << left << setw(15) << customerTable.at(i).clss << left << setw(10) << customerTable.at(i).debt <<  endl;
		}
	}
}