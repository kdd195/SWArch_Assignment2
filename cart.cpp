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
      items.push_back(data.substr(0, data.find(delimiter)));
      data.erase(0, data.find(delimiter) + delimiter.length());
      prices.push_back(stof(data.substr(0, data.find(delimiter))));

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

  // adds to vectors
  items.push_back(item);
  prices.push_back(price);
  quantity++;
}

void cart::printCart()
{
  // initializes incrementor
  int j = 0;
  total = 0;

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

void cart::removeFromCart(string username, int ID)
{
  // gets index
  ID--;

  // gets item from vector
  string item = items[ID];

  // removes affected items from the vectors
  // alters quantity accordingly
  quantity--;
  items.erase(items.begin()+ID);
  prices.erase(prices.begin()+ID);

  // declares variables to be used
  string line, data, user_tok, item_tok;
  int count = 0;

  // opens cart file
  ifstream cart;
  cart.open("cart.txt");

  // opens temporary file
  ofstream temp;
  temp.open("temp.txt");

  while(getline(cart, line))
  {
    data = line;

    // delimiter to split string
    string delimiter = "<+";

    // gets the username from the file
    user_tok = data.substr(0, data.find(delimiter));
    data.erase(0, data.find(delimiter) + delimiter.length());
    item_tok = data.substr(0, data.find(delimiter));

    // writes to temp file
    if(user_tok != username || item_tok != item || count > 0)
      temp << line << endl;

    // checks for one instance of item and username
    if(user_tok == username && item_tok == item)
      count++;
  }

  // renames and allocates files correctly
  remove("cart.txt");
  rename("temp.txt", "cart.txt");
}

void cart::checkout(string username)
{
  // removes affected items from the vectors
  // alters quantity accordingly
  quantity = 0;
  items.clear();
  prices.clear();

  // declares variables to be used
  string line, data, user_tok;

  // opens cart file
  ifstream cart;
  cart.open("cart.txt");

  // opens temporary file
  ofstream temp;
  temp.open("temp.txt");

  while(getline(cart, line))
  {
    data = line;

    // delimiter to split string
    string delimiter = "<+";

    // gets the username from the file
    user_tok = data.substr(0, data.find(delimiter));

    // writes to temp file
    if(user_tok != username)
      temp << line << endl;
  }

  // renames and allocates files correctly
  remove("cart.txt");
  rename("temp.txt", "cart.txt");
}
