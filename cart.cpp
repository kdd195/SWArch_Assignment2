// Software Architecture
// Assignment 3
//
// Inventory class
// Author: Thomas Marandi

#include "cart.h"
#include <iostream>
#include <fstream>
#include <string>

// constructor
cart::cart(string filename, string username)
{
  // opening the file
  ifstream cart;
  cart.open(filename);

  int i = 0;
  string data, user;

  // initializes quantity
  quantity = 0;

  // gets lines from the file
  while(getline(cart, data))
  {
    // delimiter to split string
    string delimiter = "<+";

    // gets the username from the file
    user = data.substr(0, data.find(delimiter));

    // only adds to arrays if the username matches
    // so that's their cart item
    if(user == username)
    {
      // starts adding to the arrays
      data.erase(0, data.find(delimiter) + delimiter.length());
      items[i] = data.substr(0, data.find(delimiter));
      data.erase(0, data.find(delimiter) + delimiter.length());
      prices[i] = stof(data.substr(0, data.find(delimiter)));

      i++;
      quantity++;
    }

  }
}

void cart::addToCart(string username, string item, float price)
{
  // opening a file to write to
  ofstream cart;
  cart.open("cart.txt", ios::app);

  // writes to the file
  cart << username << "<+" << item << "<+" << price << "\n";

  // gets the index
  // to add items to the arrays
  int index = quantity;

  // adds to arrays
  items[index] = item;
  prices[index] = price;
  quantity++;
}

void cart::printCart()
{
  // initializes incrementor
  int j = 0;

  // prints the cart
  for(int i = 0; i < quantity; i++)
  {
    cout << i+1 << ": " << items[i] << endl;
    cout << "Price: $" << prices[i] << endl;
    cout << endl;

    j++;
    total += prices[i];
  }

  cout << "Quantity: " << j << endl;
  cout << "Total price: $" << total << endl;
  cout << endl;
}

int cart::getQuantity()
{
  return quantity;
}

string cart::getItem(int ID)
{
  return items[ID];
}

float cart::getTotal()
{
  return total;
}
