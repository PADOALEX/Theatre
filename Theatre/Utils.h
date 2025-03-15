#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <limits>

// Forward declarations
class Performance;
class Ticket;

// Date and time validation functions
bool validateDate(const char* date);
bool validateTime(const char* time);
bool isDateAfterToday(const char* date);

// File operations
void loadPerformances(Performance*& head);
void savePerformances(Performance* head);
void loadTickets(Ticket*& head, Performance* perfList);
void saveTickets(Ticket* head);
void reloadPerformancesFromFile(Performance*& head);
void clearPerformanceHistory(Performance*& head);

// Menu and search operations
int menu();
Performance* findPerformanceByTitle(Performance* head, const char* title);
void displayPerformances(Performance* head);
void displayUpcomingPerformances(Performance* head);
void displayPerformancesByActor(Performance* head, const char* actorName, const char* actorSurname);
void searchPerformancesByDate(Performance* head, const char* searchDate);
void searchPerformancesByTitle(Performance* head, const char* searchTitle);
void sellTicket(Ticket*& ticketHead, Performance* perfHead, int& ticketCounter);

