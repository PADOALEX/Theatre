#include "Utils.h"
#include "Performance.h"
#include "Ticket.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <ctime>

using namespace std;

// Convert month number to month name
const char* getMonthName(int month) {
    static const char* monthNames[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    if (month >= 1 && month <= 12)
        return monthNames[month - 1];
    return "Unknown";
}

bool validateDate(const char* date) {
    if (strlen(date) != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }

    int day, month, year;
    sscanf_s(date, "%2d-%2d-%4d", &day, &month, &year);

    cout << "Debug: Parsed date " << date << " as day=" << day
        << ", month=" << month << " (" << getMonthName(month) << ")"
        << ", year=" << year << "\n";

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // Adjust for leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1]) return false;

    return true;
}

bool validateTime(const char* time) {
    if (strlen(time) != 5) return false;
    if (time[2] != ':') return false;

    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (time[i] < '0' || time[i] > '9') return false;
    }

    int hour, minute;
    sscanf_s(time, "%2d:%2d", &hour, &minute);

    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;

    return true;
}

bool isDateAfterToday(const char* date) {
    time_t now = time(0);
    struct tm today;
    localtime_s(&today, &now);

    int day, month, year;
    sscanf_s(date, "%2d-%2d-%4d", &day, &month, &year);

    int currentYear = today.tm_year + 1900;
    int currentMonth = today.tm_mon + 1;
    int currentDay = today.tm_mday;

    if (year > currentYear) return true;
    if (year < currentYear) return false;

    if (month > currentMonth) return true;
    if (month < currentMonth) return false;

    return day >= currentDay;
}

void loadPerformances(Performance*& head) {
    ifstream file("performances.txt");
    if (!file) {
        cout << "No previous performance data found.\n";
        return;
    }

    cout << "Debug: File opened successfully\n";

    head = nullptr;
    Performance* temp = nullptr;
    int performanceCount = 0;

    while (!file.eof()) {
        Performance* newPerf = new Performance();
        cout << "Debug: Loading performance #" << performanceCount + 1 << "\n";
        newPerf->loadFromFile(file);

        if (strlen(newPerf->getTitle()) == 0) {
            cout << "Debug: Empty title detected, stopping load\n";
            delete newPerf;
            break;
        }

        cout << "Debug: Loaded performance: " << newPerf->getTitle() << "\n";

        performanceCount++;
        newPerf->setNext(nullptr);

        if (!head) {
            head = newPerf;
            temp = head;
        }
        else {
            temp->setNext(newPerf);
            temp = temp->getNext();
        }
    }

    file.close();

    if (performanceCount > 0) {
        cout << "Successfully loaded " << performanceCount << " performances from file.\n";
    }
}

void savePerformances(Performance* head) {
    ofstream file("performances.txt");
    if (!file) {
        cout << "Error: Could not save performances data.\n";
        cout << "Make sure you have write permissions for this directory.\n";
        return;
    }

    Performance* temp = head;
    while (temp) {
        temp->saveToFile(file);
        temp = temp->getNext();
    }

    file.flush(); // Ensure data is written to disk
    file.close();
    cout << "Performance data saved successfully.\n";
}

void loadTickets(Ticket*& head, Performance* perfList) {
    ifstream file("tickets.txt");
    if (!file) {
        cout << "No previous ticket data found.\n";
        return;
    }

    head = nullptr;
    Ticket* temp = nullptr;

    while (!file.eof()) {
        Ticket* newTicket = new Ticket();
        newTicket->loadFromFile(file, perfList);

        if (newTicket->getId() == 0) {
            delete newTicket;
            break;
        }

        newTicket->setNext(nullptr);

        if (!head) {
            head = newTicket;
            temp = head;
        }
        else {
            temp->setNext(newTicket);
            temp = temp->getNext();
        }
    }

    file.close();
}

void saveTickets(Ticket* head) {
    ofstream file("tickets.txt");
    if (!file) {
        cout << "Error: Could not save ticket data.\n";
        return;
    }

    Ticket* temp = head;
    while (temp) {
        temp->saveToFile(file);
        temp = temp->getNext();
    }

    file.close();
}

void clearPerformanceHistory(Performance*& head) {
    char confirmation;
    cout << "WARNING: This will delete all performance records. Are you sure? (Y/N): ";
    cin >> confirmation;

    if (toupper(confirmation) != 'Y') {
        cout << "Operation cancelled.\n";
        return;
    }

    // Delete all performances from memory
    while (head) {
        Performance* temp = head;
        head = head->getNext();
        delete temp;
    }

    // Clear the file by opening it with trunc mode
    ofstream file("performances.txt", ios::trunc);
    if (!file) {
        cout << "Error: Could not clear performance file.\n";
        return;
    }
    file.close();

    cout << "All performance records have been deleted.\n";
}

int menu() {
    cout << "\n===============================\n";
    cout << "THEATER MANAGEMENT SYSTEM\n";
    cout << "===============================\n";
    cout << "1. Add Performance\n";
    cout << "2. Display All Performances\n";
    cout << "3. Display Upcoming Performances\n";
    cout << "4. Display Performances by Actor\n";
    cout << "5. Search Performances by Date\n";
    cout << "6. Search Performances by Title\n";
    cout << "7. Sell Ticket\n";
    cout << "8. Reload Performances from File\n";
    cout << "9. Clear Performance History\n";
    cout << "0. Exit\n";
    cout << "===============================\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    // Input validation for menu choice
    while (cin.fail() || choice < 0 || choice > 9) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter a number between 0 and 9: ";
        cin >> choice;
    }

    return choice;
}

void reloadPerformancesFromFile(Performance*& head) {
    // Clean up existing performances
    while (head) {
        Performance* temp = head;
        head = head->getNext();
        delete temp;
    }

    // Reload from file
    loadPerformances(head);
    cout << "Performances reloaded from file.\n";
}

Performance* findPerformanceByTitle(Performance* head, const char* title) {
    Performance* temp = head;
    while (temp) {
        if (strcmp(temp->getTitle(), title) == 0)
            return temp;
        temp = temp->getNext();
    }
    return nullptr;
}

void displayPerformances(Performance* head) {
    if (!head) {
        cout << "No performances available.\n";
        return;
    }

    cout << "\n=== ALL PERFORMANCES ===\n";
    Performance* temp = head;
    while (temp) {
        temp->displayPerformance();
        cout << "-----------------------\n";
        temp = temp->getNext();
    }
}

void displayUpcomingPerformances(Performance* head) {
    if (!head) {
        cout << "No performances available.\n";
        return;
    }

    cout << "\n=== UPCOMING PERFORMANCES ===\n";
    Performance* temp = head;
    bool found = false;
    while (temp) {
        if (temp->isUpcoming()) {
            temp->displayPerformance();
            cout << "-----------------------\n";
            found = true;
        }
        temp = temp->getNext();
    }

    if (!found)
        cout << "No upcoming performances found.\n";
}

void displayPerformancesByActor(Performance* head, const char* actorName, const char* actorSurname) {
    if (!head) {
        cout << "No performances available.\n";
        return;
    }

    cout << "\n=== PERFORMANCES WITH " << actorName << " " << actorSurname << " ===\n";
    Performance* temp = head;
    bool found = false;
    while (temp) {
        if (temp->hasActor(actorName, actorSurname)) {
            temp->displayPerformance();
            cout << "-----------------------\n";
            found = true;
        }
        temp = temp->getNext();
    }

    if (!found) {
        cout << "No performances found for actor " << actorName << " " << actorSurname << ".\n";
    }
}

void searchPerformancesByDate(Performance* head, const char* searchDate) {
    if (!head) {
        cout << "No performances available.\n";
        return;
    }

    cout << "\n=== PERFORMANCES ON " << searchDate << " ===\n";
    Performance* temp = head;
    bool found = false;
    while (temp) {
        if (temp->matchesDate(searchDate)) {
            temp->displayPerformance();
            cout << "-----------------------\n";
            found = true;
        }
        temp = temp->getNext();
    }

    if (!found)
        cout << "No performances found on " << searchDate << ".\n";
}

void searchPerformancesByTitle(Performance* head, const char* searchTitle) {
    if (!head) {
        cout << "No performances available.\n";
        return;
    }

    cout << "\n=== PERFORMANCES WITH TITLE CONTAINING \"" << searchTitle << "\" ===\n";
    Performance* temp = head;
    bool found = false;
    while (temp) {
        if (temp->matchesTitle(searchTitle)) {
            temp->displayPerformance();
            cout << "-----------------------\n";
            found = true;
        }
        temp = temp->getNext();
    }

    if (!found)
        cout << "No performances found with title containing \"" << searchTitle << "\".\n";
}

void sellTicket(Ticket*& ticketHead, Performance* perfHead, int& ticketCounter) {
    if (!perfHead) {
        cout << "No performances available.\n";
        return;
    }

    cout << "\n=== SELL TICKET ===\n";
    displayUpcomingPerformances(perfHead);

    char title[100];
    cin.ignore();
    cout << "Enter performance title: ";
    cin.getline(title, 100);

    Performance* perf = findPerformanceByTitle(perfHead, title);
    if (!perf) {
        cout << "Performance not found.\n";
        return;
    }

    if (!perf->isUpcoming()) {
        cout << "Cannot sell tickets for past performances.\n";
        return;
    }

    if (perf->getAvailableSeats() <= 0) {
        cout << "No available seats for this performance.\n";
        return;
    }

    Ticket* newTicket = new Ticket();
    newTicket->generateTicket(ticketCounter++, perf);
    newTicket->inputBuyerInfo();

    newTicket->setNext(ticketHead);
    ticketHead = newTicket;

    perf->decreaseAvailableSeats();

    cout << "\nTicket sold successfully.\n";
    cout << "=== TICKET INFORMATION ===\n";
    newTicket->displayTicket();
}