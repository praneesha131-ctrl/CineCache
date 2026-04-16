#include "utils.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void pauseMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void printLine(const string& ch, int length) {
    for (int i = 0; i < length; i++) {
        cout << ch;
    }
    cout << "\n";
}

void printStep(int stepNumber, const string& message, const string& color) {
    pauseMs(120);
    cout << color << BOLD << "  [" << stepNumber << "] " << RST;
    cout << color << message << RST << "\n";
}

void printSuccess(const string& message) {
    pauseMs(80);
    cout << GRN << "  + " << RST << message << "\n";
}

void printError(const string& message) {
    pauseMs(80);
    cout << RED << "  x " << RST << message << "\n";
}

void printInfo(const string& message) {
    pauseMs(60);
    cout << BLU << "  . " << RST << message << "\n";
}
