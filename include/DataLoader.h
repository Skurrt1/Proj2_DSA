#pragma once
#include "Title.h"
#include <string>
#include <vector>

using namespace std;

vector<Title> loadTitles(const string& basicsPath, const string& ratingsPath);

// Filters from the "Set Filters" menu. Empty string / 0 means "no filter".
struct Filters {
    std::string type;    // example "movie", "tvSeries"
    std::string genre;   // example "Documentary"
    int minVotes = 0;
};

// Returns only the titles that match every filter that's set.
vector<Title> applyFilters(const vector<Title>& all, const Filters& f);