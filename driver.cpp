// Software Architecture
// Assignment 3
//
// Implementing design from Assignment 2
// Main driver function

#include <iostream>
#include <fstream>
#include <string>

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

	while(1)
	{
		// handles printing the inventory
		// also the place where adding to cart happens, etc
		if(option == 1)
		{
			cout << "Inventory" << endl;
		}

		// handles viewing the cart
		// also the place checking out would commence
		else if(option == 2)
		{
			cout << "Viewing cart" << endl;
		}

		// handles viewing the order history
		// provides a back functionality
		else if(option == 3)
		{
			cout << "Order history" << endl;
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
		}
	}

	return 0;
}
