// Software Architecture
// Assignment 3
//
// Inventory class
// Author: Samuel Coley

#include <string>

using namespace std;

#ifndef INVENTORY_H
#define INVENTORY_H

class inventory
{
  private:
    string items[12];
    string descriptions[12];
    string categories[12];
    float prices[12];
    int quantities[12];

  public:
    inventory(string filename);
  	void printItems();
    string getItem(int ID);
    float getPrice(int ID);
    void updateInventory(int ID);
};

#endif
