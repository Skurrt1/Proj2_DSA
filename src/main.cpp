#include "DataLoader.h"
#include "Menu.h"
#include <iostream>

using namespace std;

int main() {
    vector<Title> titles = loadTitles("data/title.basics.tsv", "data/title.ratings.tsv");

    Menu menu(titles);
    menu.run();

    return 0;
}