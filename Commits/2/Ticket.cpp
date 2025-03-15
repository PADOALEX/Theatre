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