#include "DataLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Split "tt0000001\t5.7\t2238" into {"tt0000001", "5.7", "2238"}
vector<string> splitTabs(const string& line) {
    vector<string> parts;
    string field;
    istringstream ss(line);
    while (getline(ss, field, '\t')) parts.push_back(field);
    return parts;
}

struct Rating {
    double avg;
    int votes;
};

// IMDb uses "\N" for missing values. Return -1 in that case.
int toIntOrMissing(const string& s) {
    if (s == "\\N") return -1;
    return stoi(s);
}

// Split "Drama,Comedy" into {"Drama", "Comedy"}
vector<string> splitGenres(const string& s) {
    vector<string> genres;
    if (s == "\\N") return genres;
    string g;
    istringstream ss(s);
    while (getline(ss, g, ',')) genres.push_back(g);
    return genres;
}

vector<Title> loadTitles(const string& basicsPath, const string& ratingsPath) {
    vector<Title> titles;

    // ---- Read ratings into a map ----
    ifstream file(ratingsPath);
    if (!file) { cout << "Could not open " << ratingsPath << "\n"; return titles; }

    unordered_map<string, Rating> ratings;
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        auto parts = splitTabs(line);
        if (parts.size() < 3) continue;          // skip broken lines
        ratings[parts[0]] = { stod(parts[1]), stoi(parts[2]) };
    }

    // ---- Read basics and join with ratings ----
    ifstream basics(basicsPath);
    if (!basics) { cout << "Could not open " << basicsPath << "\n"; return titles; }

    titles.reserve(ratings.size());
    getline(basics, line); // skip header

    // Columns: 0 tconst, 1 titleType, 2 primaryTitle, 3 originalTitle,
    // 4 isAdult, 5 startYear, 6 endYear, 7 runtimeMinutes, 8 genres
    while (getline(basics, line)) {
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

    return titles;
}

vector<Title> applyFilters(const vector<Title>& all, const Filters& f) {
    vector<Title> result;
    for (const Title& t : all) {
        if (!f.type.empty() && t.type != f.type) continue;   // wrong type
        if (t.votes < f.minVotes) continue;                  // too few votes

        if (!f.genre.empty()) {                              // must have this genre
            bool hasGenre = false;
            for (const string& g : t.genres) {
                if (g == f.genre) { hasGenre = true; break; }
            }
            if (!hasGenre) continue;
        }
        result.push_back(t);
    }
    return result;
}