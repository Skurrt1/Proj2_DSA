#include "Title.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Quick test
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

int main() {
    ifstream file("data/title.ratings.tsv");
    if (!file) { cout << "Could not open file\n"; return 1; }

    unordered_map<string, Rating> ratings;
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        auto parts = splitTabs(line);
        if (parts.size() < 3) continue;          // skip broken lines
        ratings[parts[0]] = { stod(parts[1]), stoi(parts[2]) };
    }

    cout << "Ratings loaded: " << ratings.size() << "\n";

    // ---- Read basics and join with ratings ----
    ifstream basics("data/title.basics.tsv");
    if (!basics) { cout << "Could not open basics file\n"; return 1; }

    vector<Title> titles;
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

    cout << "Titles after join: " << titles.size() << "\n";

    // check: print the first 3 titles
    for (int i = 0; i < 3 && i < (int)titles.size(); i++) {
        cout << titles[i].id << " | " << titles[i].name << " | "
             << titles[i].year << " | " << titles[i].rating
             << " | " << titles[i].votes << "\n";
    }
}