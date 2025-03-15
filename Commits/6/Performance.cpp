#include "Performance.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

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