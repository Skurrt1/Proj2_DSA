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
}