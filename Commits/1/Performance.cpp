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