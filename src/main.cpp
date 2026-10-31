#include "DataLoader.h"
#include <iostream>

using namespace std;

int main() {
    vector<Title> titles = loadTitles("data/title.basics.tsv", "data/title.ratings.tsv");
    cout << "Loaded " << titles.size() << " titles from IMDb\n";

    // check: print the first 3 titles
    for (int i = 0; i < 3 && i < (int)titles.size(); i++) {
        cout << titles[i].id << " | " << titles[i].name << " | "
             << titles[i].year << " | " << titles[i].rating
             << " | " << titles[i].votes << "\n";
    }

    // test filters: documentary movies with at least 10,000 votes
    Filters f;
    f.type = "movie";
    f.genre = "Documentary";
    f.minVotes = 10000;
    vector<Title> docs = applyFilters(titles, f);
    cout << "Documentary movies with 10k+ votes: " << docs.size() << "\n";
}