#pragma once
#include "Title.h"

// Which field to sort by, and which direction.
enum class SortKey { Rating, Votes, Year, Title };
enum class Order { Descending, Ascending };

// Both merge sort and quicksort compare titles ONLY through this,
// so the comparison counts are fair.
class Comparator {
public:
    Comparator(SortKey key, Order order) : key_(key), order_(order) {}

    // Returns true if `a` should come BEFORE `b` in the ranking.
    // Every call adds 1 to the comparison count.
    bool operator()(const Title& a, const Title& b) const;

    long long comparisons() const { return count_; }
    void reset() { count_ = 0; }

private:
    SortKey key_;
    Order order_;
    mutable long long count_ = 0;   // mutable so operator() can stay const
};