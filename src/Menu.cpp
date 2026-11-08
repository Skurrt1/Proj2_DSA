#include "Menu.h"
#include "Comparator.h"
#include <algorithm>    
#include <functional>   
#include <iomanip>      
#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>
#include <vector>

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
    if (filtered_.empty()) {
        cout << "No titles match the current filters.\n";
        return;
    }

    // Ask sort key
    cout << "\nSort by: 1) Rating  2) Votes  3) Year  4) Title\n";
    int keyChoice = readChoice(1, 4);

    SortKey key;
    if (keyChoice == 1) {
        key = SortKey::Rating;
    } else if (keyChoice == 2) {
        key = SortKey::Votes;
    } else if (keyChoice == 3) {
        key = SortKey::Year;
    } else {
        key = SortKey::Title;
    }

    // Ask order
    cout << "Order: 1) Descending  2) Ascending\n";
    int orderChoice = readChoice(1, 2);

    Order order;
    if (orderChoice == 1) {
        order = Order::Descending;
    } else {
        order = Order::Ascending;
    }

    // Ask how many to show 
    cout << "Show top N (1-100)\n";
    int topN = readChoice(1, 100);

    // Sort a copy so filtered_ keeps its original order 
    vector<Title> sorted = filtered_;
    Comparator cmp(key, order);

    // TODO: replace with mergeSort(sorted, cmp) / quickSort(sorted, cmp) when ready
    stable_sort(sorted.begin(), sorted.end(), ref(cmp));

    // Print the table 
    cout << "\nTop " << topN << " (" << cmp.comparisons() << " comparisons)\n\n";

    cout << left
         << setw(5)  << "#"
         << setw(45) << "Title"
         << setw(12) << "Type"
         << setw(6)  << "Year"
         << right
         << setw(8)  << "Rating"
         << setw(12) << "Votes"
         << "\n";

    for (int i = 0; i < topN && i < (int)sorted.size(); i++) {
        const Title& t = sorted[i];

        // Cut long names so the columns line up
        string name = t.name;
        if (name.size() > 42) {
            name = name.substr(0, 39) + "...";
        }

        // Show "-" for a missing year instead of -1
        string year;
        if (t.year < 0) {
            year = "-";
        } else {
            year = to_string(t.year);
        }

        cout << left
             << setw(5)  << (i + 1)
             << setw(45) << name
             << setw(12) << t.type
             << setw(6)  << year
             << right
             << setw(8)  << fixed << setprecision(1) << t.rating
             << setw(12) << t.votes
             << "\n";
    }
}

void Menu::setFilters() {

    // TODO: ask type, genre, min votes
    // TODO: update filters_ and filtered_ = applyFilters(all_, filters_)
    cout << "Set filters - coming soon\n";
}


void Menu::benchmark() {

    if (filtered_.empty()) {
        cout << "No titles available to benchmark.\n";
        return;
    }

    // Benchmark using rating, highest first.
    SortKey key = SortKey::Rating;
    Order order = Order::Descending;

    Comparator ordering(key, order);

    // Different dataset sizes.
    vector<int> sizes = {100, 1000, 10000, 100000};

    cout << "\n========== SORT BENCHMARK ==========\n";
    cout << "Sorting by Rating (Descending)\n";

    for (int size : sizes) {

        if (size > (int)filtered_.size()) {
            continue;
        }

        // Copy the same number of titles.
        vector<Title> original(
            filtered_.begin(),
            filtered_.begin() + size
        );

        // Test three input orderings.
        for (int test = 0; test < 3; test++) {

            vector<Title> input = original;

            string testName;

            if (test == 0) {
                testName = "Random";

                mt19937 rng(42);
                shuffle(input.begin(), input.end(), rng);
            }
            else if (test == 1) {
                testName = "Sorted";

                ordering.reset();
                stable_sort(input.begin(), input.end(),
                            ref(ordering));
            }
            else {
                testName = "Reversed";

                ordering.reset();
                stable_sort(input.begin(), input.end(),
                            ref(ordering));

                reverse(input.begin(), input.end());
            }

            // Each algorithm gets an identical input.
            vector<Title> mergeData = input;
            vector<Title> quickData = input;

            Comparator mergeCmp(key, order);
            Comparator quickCmp(key, order);

            // -------- MERGE SORT --------

            auto mergeStart =
                chrono::steady_clock::now();

            mergeSort(mergeData, mergeCmp);

            auto mergeEnd =
                chrono::steady_clock::now();

            double mergeTime =
                chrono::duration<double, milli>(
                    mergeEnd - mergeStart
                ).count();

            // -------- QUICK SORT --------

            auto quickStart =
                chrono::steady_clock::now();

            quickSort(quickData, quickCmp);

            auto quickEnd =
                chrono::steady_clock::now();

            double quickTime =
                chrono::duration<double, milli>(
                    quickEnd - quickStart
                ).count();

            // -------- RESULTS --------

            cout << "\nSize: " << size
                 << " | Input: " << testName << "\n";

            cout << left
                 << setw(15) << "Algorithm"
                 << setw(18) << "Time (ms)"
                 << "Comparisons\n";

            cout << fixed << setprecision(3);

            cout << left
                 << setw(15) << "Merge Sort"
                 << setw(18) << mergeTime
                 << mergeCmp.comparisons()
                 << "\n";

            cout << left
                 << setw(15) << "Quick Sort"
                 << setw(18) << quickTime
                 << quickCmp.comparisons()
                 << "\n";
        }
    }

    cout << "\n========== END BENCHMARK ==========\n";
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