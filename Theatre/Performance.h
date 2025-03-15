#pragma once
#include <fstream>  // For std::ifstream and std::ofstream

struct Actor {
    char name[50];
    char surname[50];
};

class Performance {
private:
    char title[100];
    char date[11];  // Format: DD-MM-YYYY
    char time[6];   // Format: HH:MM
    int duration;   // In minutes
    int intermissions;
    int actorCount;
    Actor actors[10];
    int availableSeats;
    char description[256];
    float ratingsSum;
    int ratingsCount;
    Performance* next;

public:
    Performance();

    // Input and display methods
    void inputPerformance();
    void displayPerformance();

    // Utility methods
    bool overlapsWith(Performance* other);
    bool actorConflict(Performance* other);
    bool hasActor(const char* actorName, const char* actorSurname);
    bool isUpcoming();
    bool matchesDate(const char* searchDate);
    bool matchesTitle(const char* searchTitle);
    bool isValidDate();

    // Check for actors with matching initials
    bool hasActorWithInitials(char firstInitial, char lastInitial) const;
    bool actorInitialsConflict(Performance* other);

    // Getters
    const char* getTitle() const;
    const char* getDate() const;
    const char* getTime() const;
    int getAvailableSeats() const;

    // Modifiers
    void decreaseAvailableSeats();
    void ratePerformance(int rating);

    // Calculations
    float getAverageRating() const;

    // File I/O methods
    void saveToFile(std::ofstream& file);
    void loadFromFile(std::ifstream& file);

    // Next pointer for linked list
    Performance* getNext() const;
    void setNext(Performance* nextPerformance);

private:
    int parseTimeToMinutes(const char* timeStr) const;
};