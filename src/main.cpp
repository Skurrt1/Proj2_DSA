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

    // Spot check: The Shawshank Redemption
    auto it = ratings.find("tt0111161");
    if (it != ratings.end())
        std::cout << "tt0111161 -> rating " << it->second.avg
                  << ", votes " << it->second.votes << "\n";
}