#pragma once

#include "SpellTable.h"
#include "ItemTable.h"
#include "CustomerTable.h"
#include "Spell.h"
#include "Item.h"
#include "Customer.h"

using namespace std;

void getUserInput();
void getItemInput(string filename);
void getSpellInput(string filename);
void getCustomerInput(string filename);
vector<string> breakTuple(string tuple, string tableName);
vector<string> parseString(string input);
void Insert(string scheme, string tableName);
void Display();
void Update(string scheme, string tableName);
void Select(string scheme, string tableName);
void Write();
void Delete(string scheme, string tableName);