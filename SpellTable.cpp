#include "SpellTable.h"
#include <iostream>
#include <fstream>

Spells::Spells()
{
  size = 500;				//initialized table size
  spellTable.resize(size);	//resized table
}

//multiplicative string hash
int Spells::HashF(string key)
{
  int position = 0;
  
  for (char& c : key)
  {
    position = (position * 2) + c;
  }
  
  return position % size;
}

vector<spell> Spells::getTable()
{
	return spellTable;
}

//inserts tuple into table using multiplicative string hashing and quadratic probing for collision strategy
bool Spells::Insert(string key, spell value)
{
  int position = HashF(key);
  int probed = 0;

  
  while (probed < size)
  {
    if(spellTable.at(position).isEmpty)
    {
      spellTable.at(position) = value;
	  spellTable.at(position).isEmpty = false;
	  spellList.push_back(&spellTable.at(position));
      return true;
    }
	else if (!spellTable.at(position).isEmpty && key == spellTable.at(position).name)
	{
		return false;
	}

    probed++;
    position = (HashF(key) + ( 2 * probed) + (3 * probed * probed)) % size;
  }
  return false;
}

//update table
bool Spells::Update(vector<string> values)
{
	
	int position = HashF(values.at(0));
	string key = values.at(0);
	int probed = 0;
	spell value;
	value.name = values.at(0);
	value.level = values.at(1);
	value.school = values.at(2);
	value.casting_time = values.at(3);
	value.range = values.at(4);
	value.components = values.at(5);
	value.duration = values.at(6);
	value.isEmpty = false;

	while (probed < size)
	{
		if (spellTable.at(position).name == key)
		{
			spellTable.at(position) = value;

			return true;
		}

		probed++;
		position = (HashF(key) + (2 * probed) + (3 * probed * probed)) % size;
	}
	return false;
}

//select values from table
bool Spells::Select(vector<string> values)
{
	spell value;
	value.name = values.at(0);
	value.level = values.at(1);
	value.school = values.at(2);
	value.casting_time = values.at(3);
	value.range = values.at(4);
	value.components = values.at(5);
	value.duration = values.at(6);
	value.isEmpty = false;

	if (values.at(0) != "*")
	{
		string key = values.at(0);
		int position = HashF(key);
		int probed = 0;


		while (probed < size)
		{
			if (spellTable.at(position).name == key && spellTable.at(position).level == value.level && spellTable.at(position).school == value.school && spellTable.at(position).casting_time == value.casting_time && spellTable.at(position).range == value.range && spellTable.at(position).components == value.components && spellTable.at(position).duration == value.duration)
			{
				cout << "Found (" << spellTable.at(position).name << "|" << spellTable.at(position).level << "|" << spellTable.at(position).school << "|" << spellTable.at(position).casting_time << "|" <<spellTable.at(position).range << "|" << spellTable.at(position).components << "|" << spellTable.at(position).duration << ")" << endl;
				return true;
			}

			probed++;
			position = (HashF(key) + (2 * probed) + (3 * probed * probed)) % size;
		}
		return false;
	}
	else
	{
		int counter = 0;
		list<spell*>::iterator it;

		for (it = spellList.begin(); it != spellList.end(); ++it)
		{
			if (value.name == (*it)->name || value.name == "*")
			{
				if (value.level == (*it)->level || value.level == "*")
				{
					if (value.school == (*it)->school || value.school == "*")
					{
						if (value.casting_time == (*it)->casting_time || value.casting_time == "*")
						{
							if (value.range == (*it)->range || value.range == "*")
							{
								if (value.components == (*it)->components || value.components == "*")
								{
									if (value.duration == (*it)->duration || value.duration == "*")
									{
										if (counter == 0)
										{
											cout << "Found ";
										}
										counter++;
										cout << "(" << (*it)->name << "|" << (*it)->level << "|" << (*it)->school << "|" << (*it)->casting_time << "|" << (*it)->range << "|" << (*it)->components << "|" << (*it)->duration << ")" << endl;
									}
								}
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

//delete element or elements from table
bool Spells::Delete(vector<string> values)
{
	spell value;
	value.name = values.at(0);
	value.level = values.at(1);
	value.school = values.at(2);
	value.casting_time = values.at(3);
	value.range = values.at(4);
	value.components = values.at(5);
	value.duration = values.at(6);
	value.isEmpty = false;

	if (values.at(0) != "*")
	{
		string key = values.at(0);
		int position = HashF(key);
		int probed = 0;


		while (probed < size)
		{
			if (spellTable.at(position).name == key && spellTable.at(position).level == value.level && spellTable.at(position).school == value.school && spellTable.at(position).casting_time == value.casting_time && spellTable.at(position).range == value.range && spellTable.at(position).components == value.components && spellTable.at(position).duration == value.duration)
			{
				cout << "Deleted (" << spellTable.at(position).name << "|" << spellTable.at(position).level << "|" << spellTable.at(position).school << "|" << spellTable.at(position).casting_time << "|" <<spellTable.at(position).range << "|" << spellTable.at(position).components << "|" << spellTable.at(position).duration << ")" << endl;
				spellTable.at(position).name = " ";
				spellTable.at(position).level = " ";
				spellTable.at(position).school = " ";
				spellTable.at(position).casting_time = " ";
				spellTable.at(position).range = " ";
				spellTable.at(position).components = " ";
				spellTable.at(position).duration = " ";
				spellTable.at(position).isEmpty = true;
				return true;
			}

			probed++;
			position = (HashF(key) + (2 * probed) + (3 * probed * probed)) % size;
		}
		return false;
	}
	else
	{
		int counter = 0;
		list<spell*>::iterator it;

		for (it = spellList.begin(); it != spellList.end(); ++it)
		{
			if (value.name == (*it)->name || value.name == "*")
			{
				if (value.level == (*it)->level || value.level == "*")
				{
					if (value.school == (*it)->school || value.school == "*")
					{
						if (value.casting_time == (*it)->casting_time || value.casting_time == "*")
						{
							if (value.range == (*it)->range || value.range == "*")
							{
								if (value.components == (*it)->components || value.components == "*")
								{
									if (value.duration == (*it)->duration || value.duration == "*")
									{
										if (counter == 0)
										{
											cout << "Deleted ";
										}
										counter++;
										cout << "(" << (*it)->name << "|" << (*it)->level << "|" << (*it)->school << "|" << (*it)->casting_time << "|" << (*it)->range << "|" << (*it)->components << "|" << (*it)->duration << ")" << endl;
										(*it)->name = " ";
										(*it)->level = " ";
										(*it)->school = " ";
										(*it)->casting_time = " ";
										(*it)->range = " ";
										(*it)->components = " ";
										(*it)->duration = " ";
										(*it)->isEmpty = true;
									}
								}
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

//write to file
void Spells::Write()
{
	ofstream fout;
	fout.open("spellsOutput.txt");

	list<spell*>::iterator it;
	
	fout << "NAME" << endl;
	fout << "NAME,LEVEL,SCHOOL,CASTING_TIME,RANGE,COMPONENTS,DURATION" << endl;

	for (it = spellList.begin(); it != spellList.end(); ++it)
	{
		if ((*it)->isEmpty == false)
		{
			fout << (*it)->name << "|" << (*it)->level << "|" << (*it)->school << "|" << (*it)->casting_time << "|" << (*it)->range << "|" << (*it)->components << "|" << (*it)->duration << endl;
		}
	}
	fout.close();
}