#pragma once
#include "Title.h"
#include <string>
#include <vector>

std::vector<Title> loadTitles(const std::string& basicsPath, const std::string& ratingsPath);

// Filters from the "Set Filters" menu. Empty string / 0 means "no filter".
struct Filters {
    std::string type;    // e.g. "movie", "tvSeries"
    std::string genre;   // e.g. "Documentary"
    int minVotes = 0;
};

// Returns only the titles that match every filter that's set.
std::vector<Title> applyFilters(const std::vector<Title>& all, const Filters& f);