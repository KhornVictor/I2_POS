#include<iostream>
using namespace std;

#define GRAY    "\033[90m"
#define RESET   "\033[0m"

void pressEnterToContinue() {
    cout << GRAY << "Press Enter to continue..." << RESET;
    cin.ignore();
    cin.get();
}