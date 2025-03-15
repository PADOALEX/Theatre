#include "Performance.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

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



