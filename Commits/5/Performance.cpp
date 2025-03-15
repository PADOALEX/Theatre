#include "Performance.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

void Performance::inputPerformance() {
    cin.ignore();
    cout << "Enter title: ";
    cin.getline(title, sizeof(title));

    bool validDate = false;
    while (!validDate) {
        cout << "Enter date (DD-MM-YYYY): ";
        cin.getline(date, sizeof(date));
        if (validateDate(date) && isDateAfterToday(date)) {
            validDate = true;
        }
        else {
            cout << "Invalid date format or date is in the past. Please use DD-MM-YYYY and ensure the date is today or in the future.\n";
        }
    }

    bool validTime = false;
    while (!validTime) {
        cout << "Enter time (HH:MM): ";
        cin.getline(time, sizeof(time));
        if (validateTime(time)) {
            validTime = true;
        }
        else {
            cout << "Invalid time format. Please use HH:MM (24-hour format).\n";
        }
    }

    cout << "Enter duration (minutes): ";
    cin >> duration;
    while (duration <= 0) {
        cout << "Duration must be positive. Enter duration (minutes): ";
        cin >> duration;
    }

    cout << "Enter number of intermissions: ";
    cin >> intermissions;
    while (intermissions < 0) {
        cout << "Intermissions cannot be negative. Enter number of intermissions: ";
        cin >> intermissions;
    }

    cout << "Enter number of actors (max 10): ";
    cin >> actorCount;
    while (actorCount <= 0 || actorCount > 10) {
        cout << "Number of actors must be between 1 and 10. Enter number of actors: ";
        cin >> actorCount;
    }

    cin.ignore();
    for (int i = 0; i < actorCount; i++) {
        cout << "Enter first name of actor " << i + 1 << ": ";
        cin.getline(actors[i].name, sizeof(actors[i].name));

        cout << "Enter surname of actor " << i + 1 << ": ";
        cin.getline(actors[i].surname, sizeof(actors[i].surname));

        // Check for duplicate actors
        for (int j = 0; j < i; j++) {
            if (strcmp(actors[i].name, actors[j].name) == 0 &&
                strcmp(actors[i].surname, actors[j].surname) == 0) {
                cout << "This actor is already in the performance. Please enter a different actor.\n";
                i--; // Decrement i to repeat this iteration
                break;
            }
        }
    }

    cout << "Enter number of available seats: ";
    cin >> availableSeats;
    while (availableSeats <= 0) {
        cout << "Available seats must be positive. Enter number of available seats: ";
        cin >> availableSeats;
    }

    cin.ignore();
    cout << "Enter description: ";
    cin.getline(description, sizeof(description));
}

void Performance::displayPerformance() {
    cout << "Title: " << title << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << time << endl;
    cout << "Duration: " << duration << " minutes" << endl;
    cout << "Intermissions: " << intermissions << endl;

    cout << "Actors: ";
    for (int i = 0; i < actorCount; i++) {
        cout << actors[i].name << " " << actors[i].surname;
        if (i < actorCount - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "Available Seats: " << availableSeats << endl;
    cout << "Description: " << description << endl;
    cout << "Average Rating: " << getAverageRating() << endl;
}


