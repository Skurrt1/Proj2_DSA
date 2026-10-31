// Owner: Matthew
#include "DataLoader.h"

std::vector<Title> loadTitles(const std::string& basicsPath,
                              const std::string& ratingsPath) {
    // TODO: read ratings into a map, then read basics and join on tconst
    (void)basicsPath; (void)ratingsPath;
    return {};
}

std::vector<Title> applyFilters(const std::vector<Title>& all, const Filters& f) {
    // TODO: keep only titles that match the filters
    (void)f;
    return all;
}
