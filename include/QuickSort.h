#pragma once

#include <vector>
#include "Title.h"
#include "Comparator.h"

// Sort titles using Quick Sort.
// All comparisons go through Comparator.
void quickSort(std::vector<Title>& titles, Comparator& cmp);
