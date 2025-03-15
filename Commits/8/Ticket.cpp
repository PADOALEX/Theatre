#include "Ticket.h"
#include "Performance.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void Ticket::inputBuyerInfo() {
    cout << "Enter buyer's name: ";
    cin.getline(buyerName, 100);
    while (strlen(buyerName) == 0) {
        cout << "Buyer name cannot be empty. Enter buyer's name: ";
        cin.getline(buyerName, 100);
    }
}

void Ticket::displayTicket() {
    cout << "Ticket ID: " << id << endl;
    cout << "Buyer: " << buyerName << endl;
    if (performance != nullptr) {
        cout << "Performance: " << performance->getTitle() << endl;
        cout << "Date: " << performance->getDate() << endl;
        cout << "Time: " << performance->getTime() << endl;
    }
    cout << "Seat Number: " << seatNumber << endl;
}