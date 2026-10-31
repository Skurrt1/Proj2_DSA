#include "DataLoader.h"
#include "Comparator.h"
#include <iostream>

using namespace std;

int main() {

    //Data
    vector<Title> titles = loadTitles("data/title.basics.tsv", "data/title.ratings.tsv");
    cout << "Loaded " << titles.size() << " titles from IMDb\n";

    // check/test: print the first 3 titles
    for (int i = 0; i < 3 && i < (int)titles.size(); i++) {
        cout << titles[i].id << " | " << titles[i].name << " | "
             << titles[i].year << " | " << titles[i].rating
             << " | " << titles[i].votes << "\n";
    }

    // testings filter code: documentary movies with at least 10,000 votes
    Filters f;
    f.type = "movie";
    f.genre = "Documentary";
    f.minVotes = 10000;
    vector<Title> docs = applyFilters(titles, f);
    cout << "Documentary movies with 10k+ votes: " << docs.size() << "\n";

    // test comparator
    Comparator cmp(SortKey::Rating, Order::Descending);
    cout << "Carmencita (5.7) before Poor Pierrot (6.4)? "
         << cmp(titles[0], titles[2]) << "\n";    // expect 0 (false)
    cout << "Poor Pierrot (6.4) before Carmencita (5.7)? "
         << cmp(titles[2], titles[0]) << "\n";    // expect 1 (true)
    cout << "Comparisons counted: " << cmp.comparisons() << "\n";  // expect 2
}