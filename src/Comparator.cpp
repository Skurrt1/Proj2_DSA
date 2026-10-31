#include "Comparator.h"

using namespace std;

bool Comparator::operator()(const Title& a, const Title& b) const {
    count_++;
    bool desc = (order_ == Order::Descending);

    switch (key_) {
        case SortKey::Rating: return desc ? a.rating > b.rating : a.rating < b.rating;
        case SortKey::Votes:  return desc ? a.votes  > b.votes  : a.votes  < b.votes;
        case SortKey::Year:   return desc ? a.year   > b.year   : a.year   < b.year;
        case SortKey::Title:  return desc ? a.name   > b.name   : a.name   < b.name;
    }
    return false;
}