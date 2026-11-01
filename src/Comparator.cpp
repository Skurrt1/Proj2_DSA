#include "Comparator.h"

using namespace std;

bool Comparator::operator()(const Title& a, const Title& b) const {
    // Count every comparison
    count_++;

    bool desc = (order_ == Order::Descending);

    //Comparing Test cases
    switch (key_) {
        case SortKey::Rating:
            if (desc) {
                return a.rating > b.rating;
            } else {
                return a.rating < b.rating;
            }

        case SortKey::Votes:
            if (desc) {
                return a.votes > b.votes;
            } else {
                return a.votes < b.votes;
            }

        case SortKey::Year:
            if (desc) {
                return a.year > b.year;
            } else {
                return a.year < b.year;
            }

        case SortKey::Title:
            if (desc) {
                return a.name > b.name;
            } else {
                return a.name < b.name;
            }
    }

    return false;
}