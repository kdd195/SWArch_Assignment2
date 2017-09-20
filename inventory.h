// Software Architecture
// Assignment 3
//
// Inventory class
// Author: Samuel Coley

#include <string>
#include <vector>

using namespace std;

#ifndef INVENTORY_H
#define INVENTORY_H

class inventory
{
  private:
    vector<string> items;
    vector<string> descriptions;
    vector<string> categories;
    vector<string> attribute1;
    vector<string> attribute2;
    vector<float> prices;
    vector<int> quantities;
    int numberItems;

  public:
    inventory(string filename);
  	void printItems();
    string getItem(int ID);
    float getPrice(int ID);
    void updateInventory(string item);
    int getNumberItems();
};

#endif
