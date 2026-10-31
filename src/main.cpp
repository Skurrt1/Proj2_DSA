#include "Title.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Quick test
// Split "tt0000001\t5.7\t2238" into {"tt0000001", "5.7", "2238"}
std::vector<std::string> splitTabs(const std::string& line) {
    std::vector<std::string> parts;
    std::string field;
    std::istringstream ss(line);
    while (std::getline(ss, field, '\t')) parts.push_back(field);
    return parts;
}

struct Rating {
    double avg;
    int votes;
};

// IMDb uses "\N" for missing values. Return -1 in that case.
int toIntOrMissing(const std::string& s) {
    if (s == "\\N") return -1;
    return std::stoi(s);
}

// Split "Drama,Comedy" into {"Drama", "Comedy"}
std::vector<std::string> splitGenres(const std::string& s) {
    std::vector<std::string> genres;
    if (s == "\\N") return genres;
    std::string g;
    std::istringstream ss(s);
    while (std::getline(ss, g, ',')) genres.push_back(g);
    return genres;
}

int main() {
    std::ifstream file("data/title.ratings.tsv");
    if (!file) { std::cout << "Could not open file\n"; return 1; }

    std::unordered_map<std::string, Rating> ratings;
    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        auto parts = splitTabs(line);
        if (parts.size() < 3) continue;          // skip broken lines
        ratings[parts[0]] = { std::stod(parts[1]), std::stoi(parts[2]) };
    }

    std::cout << "Ratings loaded: " << ratings.size() << "\n";

    // ---- Read basics and join with ratings ----
    std::ifstream basics("data/title.basics.tsv");
    if (!basics) { std::cout << "Could not open basics file\n"; return 1; }

    std::vector<Title> titles;
    titles.reserve(ratings.size());
    std::getline(basics, line); // skip header

    // Columns: 0 tconst, 1 titleType, 2 primaryTitle, 3 originalTitle,
    // 4 isAdult, 5 startYear, 6 endYear, 7 runtimeMinutes, 8 genres

    while (std::getline(basics, line)) {
        auto parts = splitTabs(line);
        if (parts.size() < 9) continue;

        auto it = ratings.find(parts[0]);
        if (it == ratings.end()) continue;   // no rating -> skip (this is the join)

        Title t;
        t.id      = parts[0];
        t.type    = parts[1];
        t.name    = parts[2];
        t.year    = toIntOrMissing(parts[5]);
        t.runtime = toIntOrMissing(parts[7]);
        t.genres  = splitGenres(parts[8]);
        t.rating  = it->second.avg;
        t.votes   = it->second.votes;
        titles.push_back(t);
    }

    std::cout << "Titles after join: " << titles.size() << "\n";

    // Spot check: print the first 3 titles
    for (int i = 0; i < 3 && i < (int)titles.size(); i++) {
        std::cout << titles[i].id << " | " << titles[i].name << " | "
                  << titles[i].year << " | " << titles[i].rating
                  << " | " << titles[i].votes << "\n";
    }
}
