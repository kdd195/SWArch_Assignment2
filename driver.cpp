// Software Architecture
// Assignment 3
//
// Implementing design from Assignment 2
// Main driver function

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "inventory.h"
#include "cart.h"
#include "orderHistory.h"

using namespace std;

int main(int argc, char *argv[])
{
	// if the correct number of arguments not provided
	// just exit from the program
	if(argc < 3)
	{
		cout << "Correct number of arguments not provided" << endl;
		exit(1);
	}

	// gets the two arguments from the commandline
	string username = argv[1];
	string password = argv[2];

	// gets temporary buffer to get lines from the file
	string data;

	// declare vector to hold data needed later to initialize orderHistory
	vector<string> userData;

	// variable to set flag for successful login
	// 1 is logged in
	// 0 is not logged in
	int flag = 0;

	// files to read user data
	ifstream userfile;
	userfile.open("users.txt");

	// gets lines from the file
	while(getline(userfile, data))
	{
		// effectively splits string from file
		// gets the first and second item for comparison to login
		string delimiter = "<+";
		string usertoken = data.substr(0, data.find(delimiter));

		// erases user token from data
		// makes it possible to get next item
		data.erase(0, data.find(delimiter) + delimiter.length());
		string passtoken = data.substr(0, data.find(delimiter));

		// if there's a successful combination
		if(usertoken == username && passtoken == password)
		{
			// updates flag information
			flag = 1;

			// gets the rest of the user information
			data.erase(0, data.find(delimiter) + delimiter.length());
			string name = data.substr(0, data.find(delimiter));
			data.erase(0, data.find(delimiter) + delimiter.length());
			string email = data.substr(0, data.find(delimiter));
			data.erase(0, data.find(delimiter) + delimiter.length());
			string shipping = data.substr(0, data.find(delimiter));
			data.erase(0, data.find(delimiter) + delimiter.length());
			string billing = data.substr(0, data.find(delimiter));
			data.erase(0, data.find(delimiter) + delimiter.length());
			string payment = data.substr(0, data.find(delimiter));
			data.erase(0, data.find(delimiter) + delimiter.length());
			string phone = data.substr(0, data.find(delimiter));

			// cout << name << " " << email << endl;
			// cout << shipping << endl;
			// cout << billing << endl;
			// cout << payment << endl;
			// cout << phone << endl;

			// strings of email, billing address, shipping address,
			// payment information, and phone number now exist
			userData.push_back(name);
			userData.push_back(payment);
			userData.push_back(email);
			userData.push_back(shipping);
			userData.push_back(billing);
			userData.push_back(phone);
		}
	}

	// exits program is flag is 0
	// AKA not logged
	if(flag == 0)
	{
		cout << "Username/password combination does not exist." << endl;
		exit(1);
	}

	// displays a menu to the user
	cout << "You're now logged in!" << endl;
	cout << "1. View inventory items" << endl;
	cout << "2. View your cart" << endl;
	cout << "3. View your order history" << endl;
	cout << "4. Logout" << endl;
	cout << "Please pick an option from the list (1-4): ";

	// declares the variable
	// that menu option is stored in
	int option;

	// gets input from the command line
	cin >> option;
	cout << endl;

	// initialize order history
	orderHistory history(userData[0], userData[1], userData[2], userData[3], userData[4], userData[5]);
	history.viewHistory();

	// creates an instance of the inventory class
	inventory items("inventory.txt");

	// initializes cart class
	string file = "cart.txt";
	cart userCart(file, username);

	while(1)
	{
		// the user chose to go back
		if(option == 0)
		{
			// displays a menu to the user
			cout << endl;
			cout << "You've gone back!" << endl;
			cout << "1. View inventory items" << endl;
			cout << "2. View your cart" << endl;
			cout << "3. View your order history" << endl;
			cout << "4. Logout" << endl;
			cout << "Please pick an option from the list (1-4): ";

			cin >> option;
			cout << endl;
		}

		// handles printing the inventory
		// also the place where adding to cart happens, etc
		else if(option == 1)
		{
			int prompt;

			// starts a menu
			cout << "0. Go Back" << endl;
			cout << endl;

			items.printItems();

			while(1)
			{
				// prints prompt to user
				cout << "Please enter 0 to return to the main menu" << endl;
				cout << "Or enter the number of item you'd like to add to your cart: ";

				// gets in the prompt number
				cin >> prompt;
				cout << endl;

				// the user chose to go back
				if(prompt == 0)
				{
					option = 0;
					break;
				}

				// stores variables to use in add to cart
				else if(prompt > 0 && prompt < items.getNumberItems()+1)
				{
					cout << "Successfully added item to the cart!" << endl;
					string item = items.getItem(prompt);
					float price = items.getPrice(prompt);

					// adds item to the cart
					userCart.addToCart(username, item, price);
				}

				else
				{
					cout << "Sorry, your entry was not a valid entry. Please try again." << endl;
				}
			}
		}

		// handles viewing the cart
		// also the place checking out would commence
		else if(option == 2)
		{
			// initializes variable for menu
			int prompt;

			// Begins the menu for the user to select from
			cout << "0. Go Back" << endl;

			// prints the cart to view
			userCart.printCart();

			while(1)
			{
				cout << "Enter 0 to go back" << endl;
				cout << "Or enter the number of the item you'd like to remove from the cart" << endl;
				cout << "Or enter -1 to checkout: ";

				cin >> prompt;

				if(prompt == 0)
				{
					option = 0;
					break;
				}

				else if(prompt > 0 && prompt < (userCart.getQuantity() + 1))
				{
					// this is where remove from cart will go
					userCart.removeFromCart(username, prompt);
				}

				else if(prompt == -1)
				{
					// gets the size
					// initializes the array
					// switched from array to vector to be more C++ compliant - JS
					int size = userCart.getQuantity();
					vector<string> cartItems;

					// adds items to the array
					for(int i = 0; i < size; i++)
					{
						cartItems.push_back(userCart.getItem(i));

						// updates inventory for that item
						items.updateInventory(userCart.getItem(i));
					}

					float total = userCart.getTotal();
					// this is where you'd add items to the order history
					history.addToHistory(cartItems, size, total);
					cout << "Order placed and logged in history" << endl;
					cout << endl;

					// this is where check out will go
					userCart.checkout(username);

					// goes back to main menu
					option = 0;
					break;
				}

				else
				{
					cout << "Sorry, your entry was not a valid entry. Please try again." << endl;
				}
			}
		}

		// handles viewing the order history
		// provides a back functionality
		else if(option == 3)
		{
			cout << history.viewHistory() << endl;
			while(1){
				int prompt;
				cout << "Enter 0 to go back" << endl;
				cin >> prompt;

				if(prompt == 0)
				{
					option = 0;
					break;
				}
			}

		}

		// handles logging out
		// basically just breaking from the while loop
		else if(option == 4)
		{
			cout << "Logged out" << endl;
			exit(1);
		}

		// else the option isn't valid
		// handles error checking
		else
		{
			// gets new input
			cout << "Sorry, your entry was not a valid option. Try again: ";
			cin >> option;

			cout << endl;
		}
	}

	return 0;
}
