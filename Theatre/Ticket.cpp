#include "Ticket.h"
#include "Performance.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

Ticket* Ticket::getNext() const {
    return next;
}

void Ticket::setNext(Ticket* nextTicket) {
    next = nextTicket;
}

Ticket::Ticket() {
    id = 0;
    strcpy_s(buyerName, "");
    seatNumber = 0;
    performance = nullptr;
    next = nullptr;
}

void Ticket::generateTicket(int ticketId, Performance* perf) {
    id = ticketId;
    performance = perf;
    seatNumber = perf->getAvailableSeats();
    perf->decreaseAvailableSeats();
}

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

void Ticket::saveToFile(ofstream& file) {
    if (!file.is_open() || performance == nullptr) return;

    file << id << endl;
    file << buyerName << endl;
    file << seatNumber << endl;
    file << performance->getTitle() << endl;
    file << "---" << endl;
}

void Ticket::loadFromFile(ifstream& file, Performance* perfList) {
    if (!file.is_open() || file.eof()) {
        id = 0;
        return;
    }

    char perfTitle[100];
    file >> id;
    if (file.eof()) {
        id = 0;
        return;
    }
    file.ignore();
    file.getline(buyerName, 100);
    file >> seatNumber;
    file.ignore();
    file.getline(perfTitle, 100);

    performance = nullptr;
    Performance* temp = perfList;
    while (temp) {
        if (strcmp(temp->getTitle(), perfTitle) == 0) {
            performance = temp;
            break;
        }
        temp = temp->getNext();
    }

    string separator;
    std::getline(file, separator);
}

