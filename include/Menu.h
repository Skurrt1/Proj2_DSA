#pragma once
#include "DataLoader.h"
#include "Title.h"
#include <vector>

class Menu {
public:

    // Takes all loaded titles
    Menu(const std::vector<Title>& all);

    // Shows the main menu until the user picks Exit
    void run();

private:

    // 1) Rank titles
    void rankTitles();

    // 2) Set filters
    void setFilters();

    // 3) Benchmark merge sort vs quicksort
    void benchmark();

    // Reads a number between low and high from the user
    int readChoice(int low, int high);

    std::vector<Title> all_;        // every loaded title
    std::vector<Title> filtered_;   // titles after filters are applied
    Filters filters_;               // current filters
};