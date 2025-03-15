#include "Performance.h"
#include "Ticket.h"
#include "Utils.h"

using namespace std;

int main() {
    Performance* perfHead = nullptr;
    Ticket* ticketHead = nullptr;
    int ticketCounter = 1;

    loadPerformances(perfHead);
    loadTickets(ticketHead, perfHead);

    int choice;
    do {
        choice = menu();
        switch (choice) {
        case 1: {
            Performance* newPerf = new Performance();
            newPerf->inputPerformance();

            if (newPerf->getAvailableSeats() <= 0) {
                cout << "Error: Number of available seats must be greater than 0.\n";
                delete newPerf;
                break;
            }

            if (!validateDate(newPerf->getDate())) {
                cout << "Error: Invalid date format. Use YYYY-MM-DD.\n";
                delete newPerf;
                break;
            }

            if (!validateTime(newPerf->getTime())) {
                cout << "Error: Invalid time format. Use HH:MM.\n";
                delete newPerf;
                break;
            }

            if (!isDateAfterToday(newPerf->getDate())) {
                cout << "Error: Performance date must be today or in the future.\n";
                delete newPerf;
                break;
            }

            Performance* temp = perfHead;
            bool conflict = false;
            while (temp != nullptr) {
                if (newPerf->overlapsWith(temp)) {
                    cout << "Error: Overlapping performances.\n";
                    conflict = true;
                    break;
                }
                if (newPerf->actorConflict(temp)) {
                    cout << "Error: Actor conflict on the same day.\n";
                    conflict = true;
                    break;
                }
                if (newPerf->actorInitialsConflict(temp)) {
                    cout << "Error: Actor with identical initials already has a performance on this day.\n";
                    conflict = true;
                    break;
                }
                temp = temp->getNext();
            }
            if (conflict) {
                delete newPerf;
                break;
            }

            newPerf->setNext(perfHead);
            perfHead = newPerf;
            cout << "Performance added successfully.\n";
            savePerformances(perfHead); // Save immediately after adding
            break;
        }
        case 2:
            displayPerformances(perfHead);
            break;
        case 3:
            displayUpcomingPerformances(perfHead);
            break;
        case 4: {
            char actorName[50];
            char actorSurname[50];
            cin.ignore();
            cout << "Enter actor's first name: ";
            cin.getline(actorName, 50);
            cout << "Enter actor's surname: ";
            cin.getline(actorSurname, 50);
            displayPerformancesByActor(perfHead, actorName, actorSurname);
            break;
        }
        case 5: {
            char searchDate[11];
            cin.ignore();
            cout << "Enter date to search (YYYY-MM-DD): ";
            cin.getline(searchDate, 11);
            if (!validateDate(searchDate)) {
                cout << "Error: Invalid date format. Use YYYY-MM-DD.\n";
                break;
            }
            searchPerformancesByDate(perfHead, searchDate);
            break;
        }
        case 6: {
            char searchTitle[100];
            cin.ignore();
            cout << "Enter title to search: ";
            cin.getline(searchTitle, 100);
            searchPerformancesByTitle(perfHead, searchTitle);
            break;
        }
        case 7:
            sellTicket(ticketHead, perfHead, ticketCounter);
            break;
        case 8:
            reloadPerformancesFromFile(perfHead);
            break;
        case 9:
            clearPerformanceHistory(perfHead);
            break;
        case 0:
            savePerformances(perfHead);
            saveTickets(ticketHead);
            cout << "Data saved. Exiting.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    // Clean up memory
    while (perfHead) {
        Performance* temp = perfHead;
        perfHead = perfHead->getNext();
        delete temp;
    }
    while (ticketHead) {
        Ticket* temp = ticketHead;
        ticketHead = ticketHead->getNext();
        delete temp;
    }

    return 0;
}

