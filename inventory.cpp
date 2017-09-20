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
  numberItems = 0;

  // gets lines from the file
  while(getline(inv, data))
  {
    // delimiter to split string
    string delimiter = "<+";

    // adds data to the arrays
    data.erase(0, data.find(delimiter) + delimiter.length());
    items.push_back(data.substr(0, data.find(delimiter)));
    data.erase(0, data.find(delimiter) + delimiter.length());
    categories.push_back(data.substr(0, data.find(delimiter)));
    data.erase(0, data.find(delimiter) + delimiter.length());
    quantities.push_back(stoi(data.substr(0, data.find(delimiter))));
    data.erase(0, data.find(delimiter) + delimiter.length());
    prices.push_back(stof(data.substr(0, data.find(delimiter))));
    data.erase(0, data.find(delimiter) + delimiter.length());
    descriptions.push_back(data.substr(0, data.find(delimiter)));
    data.erase(0, data.find(delimiter) + delimiter.length());
    attribute1.push_back(data.substr(0, data.find(delimiter)));
    data.erase(0, data.find(delimiter) + delimiter.length());
    attribute2.push_back(data.substr(0, data.find(delimiter)));

    i++;
    numberItems++;
  }
}

// prints the items of the inventory
void inventory::printItems()
{
  for(int i = 0; i < items.size(); i++)
  {
    cout << i+1 << ". " << items[i] << endl;
    cout << "Category: " << categories[i] << endl;
    cout << "Price: " << prices[i] << endl;
    cout << "Inventory: " << quantities[i] << endl;
    cout << "Description: " << descriptions[i] << endl;

    // prints attributes according to category
    if(categories[i] == "Household Items")
    {
      cout << "Room: " << attribute1[i] << endl;
      cout << "Luxury Item: " << attribute2[i] << endl;
    }

    else if(categories[i] == "Books")
    {
      cout << "ISBN: " << attribute1[i] << endl;
      cout << "Author: " << attribute2[i] << endl;
    }

    else if(categories[i] == "Toys")
    {
      cout << "Age range: " << attribute1[i] << endl;
      cout << "Action figure: " << attribute2[i] << endl;
    }

    else if(categories[i] == "Small Electronics")
    {
      cout << "Brand: " << attribute1[i] << endl;
      cout << "Category: " << attribute2[i] << endl;
    }

    else
    {
      cout << "Gender: " << attribute1[i] << endl;
      cout << "Section: " << attribute2[i] << endl;
    }

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

int inventory::getNumberItems()
{
  return numberItems;
}

void inventory::updateInventory(string item)
{
  // opens inventory file
  ifstream inv;
  inv.open("inventory.txt");

  // opens temporary file
  ofstream temp;
  temp.open("temp.txt");

  // variables to use
  string data, line;
  string item_tok, id_tok;
  string category, price, description, attributeA, attributeB;
  int quantity;

  while(getline(inv, line))
  {
    data = line;

    // delimiter to split string
    string delimiter = "<+";

    // gets the information from the file
    id_tok = data.substr(0, data.find(delimiter));
    data.erase(0, data.find(delimiter) + delimiter.length());
    item_tok = data.substr(0, data.find(delimiter));

    if(item_tok == item)
    {
      // gets the rest of the data to alter
      data.erase(0, data.find(delimiter) + delimiter.length());
      category = data.substr(0, data.find(delimiter));
      data.erase(0, data.find(delimiter) + delimiter.length());
      quantity = stoi(data.substr(0, data.find(delimiter)));
      data.erase(0, data.find(delimiter) + delimiter.length());
      price = data.substr(0, data.find(delimiter));
      data.erase(0, data.find(delimiter) + delimiter.length());
      description = data.substr(0, data.find(delimiter));
      data.erase(0, data.find(delimiter) + delimiter.length());
      attributeA = data.substr(0, data.find(delimiter));
      data.erase(0, data.find(delimiter) + delimiter.length());
      attributeB = data.substr(0, data.find(delimiter));

      quantity--;
      temp << id_tok << "<+" << item_tok << "<+" << category << "<+" << quantity << "<+" << price << "<+" << description << "<+" << attributeA << "<+" << attributeB << endl;

      // updates the vector
      int ID = stoi(id_tok) - 1;
      quantities[ID] = quantity;
    }

    else
      temp << line << endl;
  }

  // renames and allocates files correctly
  remove("inventory.txt");
  rename("temp.txt", "inventory.txt");
}
