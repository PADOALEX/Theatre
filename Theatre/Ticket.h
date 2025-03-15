#pragma once
#include <iostream>
#include <fstream>
#include <string>

// Forward declaration to avoid circular dependencies
class Performance;

class Ticket {
private:
    int id;
    char buyerName[100];
    int seatNumber;
    Performance* performance;
    Ticket* next;

public:
    Ticket();
    void generateTicket(int ticketId, Performance* perf);
    void inputBuyerInfo();
    void displayTicket();
    void saveToFile(std::ofstream& file);
    void loadFromFile(std::ifstream& file, Performance* perfList);

    // Getter for 'id' to access the private member
    int getId() const { return id; }

    // Methods to manage the next pointer
    Ticket* getNext() const;
    void setNext(Ticket* nextTicket);
};
