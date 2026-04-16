#include "ui.h"
#include "utils.h"
#include <iostream>

using namespace std;

// Display the program banner
void printBanner() {
    system("clear");
    cout << "\n";
    cout << BOLD << CYN;
    cout << "  +========================================================+\n";
    cout << "  |                                                        |\n";
    cout << "  |       C I N E C A C H E   D S A   S Y S T E M        |\n";
    cout << "  |                                                        |\n";
    cout << "  |   Consistent Hashing  +  LRU Cache  +  Sim-DB        |\n";
    cout << "  |                                                        |\n";
    cout << "  +========================================================+\n";
    cout << RST << "\n";
}

// Display the menu with options
void printMenu(bool databaseLoaded) {
    cout << BOLD << "  +-- MENU -------------------------------------------------+\n" << RST;
    cout << "  |  " << BOLD << CYN << "[1]" << RST << "  View LRU cache state of all nodes           |\n";
    cout << "  |  " << BOLD << CYN << "[2]" << RST << "  Lookup a movie (full flow + description)    |\n";
    cout << "  |  " << BOLD << CYN << "[3]" << RST << "  Consistent hash ring & routing table        |\n";
    cout << "  |  " << BOLD << CYN << "[4]" << RST << "  Load movie database  ";

    if (databaseLoaded) {
        cout << string(GRN) + "[loaded]" + RST;
    } else {
        cout << string(RED) + "[not loaded]" + RST;
    }

    cout << "               |\n";
    cout << "  |  " << BOLD << RED << "[5]" << RST << "  Remove a node (power saving)                |\n";
    cout << "  |  " << BOLD << RED << "[0]" << RST << "  Quit                                        |\n";
    cout << BOLD << "  +---------------------------------------------------------+\n" << RST;
    cout << "\n  " << BOLD << "> " << RST;
}
