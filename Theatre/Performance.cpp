#include "Performance.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

Performance::Performance() {
    strcpy_s(title, sizeof(title), "");
    strcpy_s(date, sizeof(date), "");
    strcpy_s(time, sizeof(time), "");
    duration = 0;
    intermissions = 0;
    actorCount = 0;
    availableSeats = 0;
    strcpy_s(description, sizeof(description), "");
    for (int i = 0; i < 10; i++) {
        strcpy_s(actors[i].name, sizeof(actors[i].name), "");
        strcpy_s(actors[i].surname, sizeof(actors[i].surname), "");
    }
    next = nullptr;
    ratingsSum = 0.0f;
    ratingsCount = 0;
}

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
	for (int i = 0; i < actorCount; i++) {   // Display actors
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

bool Performance::overlapsWith(Performance* other) {
    if (strcmp(date, other->date) != 0) {
        return false;
    }

    int start1 = parseTimeToMinutes(time);
    int end1 = start1 + duration;
    int start2 = parseTimeToMinutes(other->time);
    int end2 = start2 + other->duration;

    return (start1 < end2 && end1 > start2);
}

bool Performance::actorConflict(Performance* other) {
    if (strcmp(date, other->date) != 0) {
        return false;
    }

    for (int i = 0; i < actorCount; i++) {
        for (int j = 0; j < other->actorCount; j++) {
            if (strcmp(actors[i].name, other->actors[j].name) == 0 &&
                strcmp(actors[i].surname, other->actors[j].surname) == 0) {
                if (overlapsWith(other)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Performance::hasActor(const char* actorName, const char* actorSurname) {
    for (int i = 0; i < actorCount; i++) {
        if (strcmp(actors[i].name, actorName) == 0 &&
            strcmp(actors[i].surname, actorSurname) == 0) {
            return true;
        }
    }
    return false;
}

bool Performance::isUpcoming() {
    return isDateAfterToday(date);
}

bool Performance::matchesDate(const char* searchDate) {
    return (strcmp(date, searchDate) == 0);
}

bool Performance::matchesTitle(const char* searchTitle) {
    return (strstr(title, searchTitle) != nullptr);
}

bool Performance::isValidDate() {
    return validateDate(date);
}

bool Performance::hasActorWithInitials(char firstInitial, char lastInitial) const {
    for (int i = 0; i < actorCount; i++) {
        if (actors[i].name[0] == firstInitial && actors[i].surname[0] == lastInitial) {
            return true;
        }
    }
    return false;
}

bool Performance::actorInitialsConflict(Performance* other) {
    if (strcmp(date, other->date) != 0) {
        return false;
    }

    for (int i = 0; i < actorCount; i++) {
        char firstInitial = actors[i].name[0];
        char lastInitial = actors[i].surname[0];

        if (other->hasActorWithInitials(firstInitial, lastInitial)) {
            cout << "Debug: Actor with initials " << firstInitial << "." << lastInitial
                << ". has a conflict on " << date << "\n";
            return true;
        }
    }
    return false;
}

const char* Performance::getTitle() const {
    return title;
}

const char* Performance::getDate() const {
    return date;
}

const char* Performance::getTime() const {
    return time;
}

int Performance::getAvailableSeats() const {
    return availableSeats;
}

void Performance::decreaseAvailableSeats() {
    if (availableSeats > 0) {
        availableSeats--;
    }
}

void Performance::ratePerformance(int rating) {
    ratingsSum += static_cast<float>(rating);
    ratingsCount++;
}

float Performance::getAverageRating() const {
    if (ratingsCount == 0) {
        return 0.0f;
    }
    return ratingsSum / ratingsCount;
}

void Performance::saveToFile(std::ofstream& file) {
    if (!file.is_open()) {
        return;
    }

    file << title << endl;
    file << date << endl;
    file << time << endl;
    file << duration << endl;
    file << intermissions << endl;
    file << actorCount << endl;
    for (int i = 0; i < actorCount; i++) {
        file << actors[i].name << endl;
        file << actors[i].surname << endl;
    }
    file << availableSeats << endl;
    file << description << endl;
    file << ratingsSum << endl;
    file << ratingsCount << endl;
    file << "---" << endl;
}

void Performance::loadFromFile(std::ifstream& file) {
    if (!file.is_open() || file.eof()) {
        strcpy_s(title, sizeof(title), "");
        return;
    }

    file.getline(title, sizeof(title));
    if (file.eof() || strlen(title) == 0) {
        strcpy_s(title, sizeof(title), "");
        return;
    }
    file.getline(date, sizeof(date));
    file.getline(time, sizeof(time));
    file >> duration;
    file >> intermissions;
    file >> actorCount;
    file.ignore();
    for (int i = 0; i < actorCount; i++) {
        file.getline(actors[i].name, sizeof(actors[i].name));
        file.getline(actors[i].surname, sizeof(actors[i].surname));
    }
    file >> availableSeats;
    file.ignore();
    file.getline(description, sizeof(description));
    file >> ratingsSum;
    file >> ratingsCount;
    file.ignore();

    string separator;
    getline(file, separator);
}

Performance* Performance::getNext() const {
    return next;
}

void Performance::setNext(Performance* nextPerformance) {
    next = nextPerformance;
}

int Performance::parseTimeToMinutes(const char* timeStr) const {
    int hours = 0;
    int minutes = 0;
    if (sscanf_s(timeStr, "%d:%d", &hours, &minutes) != 2) {
        return -1; // Invalid time format
    }
    return hours * 60 + minutes;
}
