#pragma once
#include <string>
#include <vector>

struct Title {
    std::string id;     // tconst
    std::string type;   // titleType
    std::string name;   // primaryTitle
    
    int year = -1;      // startYear (-1 if "\N")
    int runtime = -1;   // runtimeMinutes
    double rating = 0.0;// averageRating
    int votes = 0;      // numVotes

    std::vector<std::string> genres;
};