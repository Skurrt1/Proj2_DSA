#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream file("data/title.ratings.tsv");
    if (!file) {
        std::cout << "Could not open file\n";
        return 1;
    }
    std::string line;
    std::getline(file, line);              // skip the header row
    std::cout << "Header: " << line << "\n";

    long count = 0;
    while (std::getline(file, line)) count++;
    std::cout << "Rows: " << count << "\n";
}