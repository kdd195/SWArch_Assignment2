// Software Architecture
// Assignment 3
//
// Order History class
// Author: Joseph Sommer

#include "orderHistory.h"
#include <fstream>

using namespace std;

orderHistory::orderHistory(string username, string paymentInfo, string email, string shippingAddr, string billingAddr, string phone){
    _username = username;
    _paymentInfo = paymentInfo;
    _email = email;
    _shippingAddress = shippingAddr;
    _billingAddress = billingAddr;
    _phone = phone;
}

void orderHistory::addToHistory(vector<string> items, int numberOfItems, float total){
    ofstream file;
    string output;
    file.open("orders.txt", ofstream::app);
    output = _username + "<+" + _paymentInfo + "<+" + _email + "<+" + _shippingAddress + "<+" + _billingAddress + "<+" + _phone + "<+";
    for(int x=0; x<items.size(); x++){
        output = output + items[x] + "|";
    }
    output = output + "<+" + to_string(numberOfItems) + "<+" + to_string(total) + "\n";
    file << output;
    file.close();
}

string orderHistory::viewHistory(){
	ifstream orderFile;
    string data;
    string output = "";
    orderFile.open("orders.txt");
    while(getline(orderFile, data))
    {
        // effectively splits string from file
        // gets the first and second item for comparison to login
        string delimiter = "<+";
        string usertoken = data.substr(0, data.find(delimiter));
        
        // if there's a successful combination
        if(usertoken == _username)
        {	
            // gets the rest of the user information
            data.erase(0, data.find(delimiter) + delimiter.length());
            string name = data.substr(0, data.find(delimiter));
            data.erase(0, data.find(delimiter) + delimiter.length());
            string paymentInfo = data.substr(0, data.find(delimiter));
            data.erase(0, data.find(delimiter) + delimiter.length());
            string email = data.substr(0, data.find(delimiter));
            data.erase(0, data.find(delimiter) + delimiter.length());
            string shippingAddr = data.substr(0, data.find(delimiter));
            data.erase(0, data.find(delimiter) + delimiter.length());
            string billingAddr = data.substr(0, data.find(delimiter));
            data.erase(0, data.find(delimiter) + delimiter.length());
            string phone = data.substr(0, data.find(delimiter));
            data.erase(0, data.find(delimiter) + delimiter.length());
            string items = data.substr(0, data.find(delimiter));
            data.erase(0, data.find(delimiter) + delimiter.length());
            string numberOfItems = data.substr(0, data.find(delimiter));
            data.erase(0, data.find(delimiter) + delimiter.length());
            string total = data.substr(0, data.find(delimiter));

            output = output + name + " " + paymentInfo + " " + email + " " + shippingAddr + " " + billingAddr + " " + 
                     phone + " " + items + " " + numberOfItems + " " + total + "\n";
        }
    }
    orderFile.close();
    return output;
}