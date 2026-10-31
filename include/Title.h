#pragma once
#include <string>
#include <vector>

using namespace std;

struct Title {
    string id;     // tconst
    string type;   // titleType
    string name;   // primaryTitle
    
    int year = -1;      // startYear (-1 if "\N")
    int runtime = -1;   // runtimeMinutes
    double rating = 0.0;// averageRating
    int votes = 0;      // numVotes

    vector<string> genres;
};