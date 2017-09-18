// Software Architecture
// Assignment 3
//
// Inventory class
// Author: Samuel Coley

#include "inventory.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// constructor
inventory::inventory(string filename)
{
  // opening the file
  ifstream inv;
  inv.open(filename);

  int i = 0;
  string data;

  // gets lines from the file
  while(getline(inv, data))
  {
    // delimiter to split string
    string delimiter = "<+";

    // adds data to the arrays
    data.erase(0, data.find(delimiter) + delimiter.length());
    items[i] = data.substr(0, data.find(delimiter));
    data.erase(0, data.find(delimiter) + delimiter.length());
    categories[i] = data.substr(0, data.find(delimiter));
    data.erase(0, data.find(delimiter) + delimiter.length());
    quantities[i] = stoi(data.substr(0, data.find(delimiter)));
    data.erase(0, data.find(delimiter) + delimiter.length());
    prices[i] = stof(data.substr(0, data.find(delimiter)));
    data.erase(0, data.find(delimiter) + delimiter.length());
    descriptions[i] = data.substr(0, data.find(delimiter));

    i++;
  }
}

// prints the items of the inventory
void inventory::printItems()
{
  for(int i = 0; i < 12; i++)
  {
    cout << i+1 << ". " << items[i] << endl;
    cout << "Category: " << categories[i] << endl;
    cout << "Price: " << prices[i] << endl;
    cout << "Inventory: " << quantities[i] << endl;
    cout << "Description: " << descriptions[i] << endl;
    cout << endl;
  }
}

string inventory::getItem(int ID)
{
  // minus one to get the index number
  ID--;

  return items[ID];
}

float inventory::getPrice(int ID)
{
  // minus one to get the index number
  ID--;

  return prices[ID];
}
