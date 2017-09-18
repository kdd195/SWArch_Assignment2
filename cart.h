// Software Architecture
// Assignment 3
//
// Inventory class
// Author: Thomas Marandi

#include <string>

using namespace std;

#ifndef CART_H
#define CART_H

class cart
{
  private:
    string items[100];
    float prices[100];
    int quantity;
    float total;

  public:
    cart(string filename, string username);
    void addToCart(string username, string item, float price);
    void removeFromCart(string username, int ID);
  	void printCart();
    void checkout(string username);
    int getQuantity();
    string getItem(int ID);
    float getTotal();
};

#endif
