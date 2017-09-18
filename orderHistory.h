// Software Architecture
// Assignment 3
//
// Order History class
// Author: Joseph Sommer

#include <string>
#include <vector>

using namespace std;

#ifndef ORDER_HISTORY
#define ORDER_HISTORY

class orderHistory
{
    private:
        string _username;
        vector<string> _items;
        int _numberOfItems;
        float _total;
        string _paymentInfo;
        string _email;
        string _shippingAddress;
        string _billingAddress;
        string _phone;

    public:
        orderHistory(string username, string paymentInfo, string email, string shippingAddr, string billingAddr, string phone);
        void addToHistory(vector<string> items, int numberOfItems, float total);
        string viewHistory();
};
#endif