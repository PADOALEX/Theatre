#include "Ticket.h"
#include "Performance.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

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