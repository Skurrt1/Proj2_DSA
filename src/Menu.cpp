#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(const vector<Title>& all) {
    
    all_ = all;
    filtered_ = all;   // no filters yet, so filtered = everything
}

void Menu::run() {
    while (true) {
        cout << "\n========================================================\n";
        cout << "Loaded " << all_.size() << " titles from IMDb\n";
        cout << "(" << filtered_.size() << " match current filters)\n\n";
        cout << "1) Rank titles\n";
        cout << "2) Set filters (type | genre | vote count)\n";
        cout << "3) Benchmark merge sort vs quicksort\n";
        cout << "4) Exit\n";

        int choice = readChoice(1, 4);

        if (choice == 1) {
            rankTitles();
        } else if (choice == 2) {
            setFilters();
        } else if (choice == 3) {
            benchmark();
        } else {
            cout << "Goodbye!\n";
            return;
        }
    }
}

void Menu::rankTitles() {

    // TODO: ask sort key (Rating/Votes/Year/Title)
    // TODO: ask order (Descending/Ascending)
    // TODO: ask top N
    // TODO: sort filtered_ and print the top N
    cout << "Rank titles - coming soon\n";
}

void Menu::setFilters() {

    // TODO: ask type, genre, min votes
    // TODO: update filters_ and filtered_ = applyFilters(all_, filters_)
    cout << "Set filters - coming soon\n";
}

void Menu::benchmark() {

    // TODO: run merge sort and quicksort on the same input
    // TODO: print time and comparison count for each
    cout << "Benchmark - coming soon\n";
}

int Menu::readChoice(int low, int high) {
    int choice;

    while (true) {
        cout << "Choice: ";

        if (cin >> choice) {
            if (choice >= low && choice <= high) {
                return choice;
            }
        } else {
            cin.clear();              // clear the error from non-number input
        }

        cin.ignore(10000, '\n');      // throw away the rest of the line
        cout << "Please enter a number from " << low << " to " << high << ".\n";
    }
}