
#include "QuickSort.h"
#include <algorithm>
#include <vector>

// Select a pivot using median-of-three.
// This helps with already sorted and reversed data.
int medianOfThree(std::vector<Title>& titles,
                  int left, int right,
                  Comparator& cmp) {

    int mid = left + (right - left) / 2;

    if (cmp(titles[mid], titles[left])) {
        std::swap(titles[mid], titles[left]);
    }

    if (cmp(titles[right], titles[left])) {
        std::swap(titles[right], titles[left]);
    }

    if (cmp(titles[right], titles[mid])) {
        std::swap(titles[right], titles[mid]);
    }

    return mid;
}

// Recursive Quick Sort helper function.
void quickSortHelper(std::vector<Title>& titles,
                     int left, int right,
                     Comparator& cmp) {

    while (left < right) {

        // Choose pivot using median-of-three.
        int pivotIndex = medianOfThree(titles, left, right, cmp);
        Title pivot = titles[pivotIndex];

        // Three-way partitioning:
        // left section: before pivot
        // middle section: equal to pivot
        // right section: after pivot
        int lt = left;
        int i = left;
        int gt = right;

        while (i <= gt) {

            if (cmp(titles[i], pivot)) {
                std::swap(titles[lt], titles[i]);
                lt++;
                i++;
            }
            else if (cmp(pivot, titles[i])) {
                std::swap(titles[i], titles[gt]);
                gt--;
            }
            else {
                i++;
            }
        }

        // Sort the smaller partition first
        // to reduce recursion depth.
        if (lt - left < right - gt) {
            quickSortHelper(titles, left, lt - 1, cmp);
            left = gt + 1;
        }
        else {
            quickSortHelper(titles, gt + 1, right, cmp);
            right = lt - 1;
        }
    }
}

// Main Quick Sort function.
void quickSort(std::vector<Title>& titles,
               Comparator& cmp) {

    // No sorting needed for 0 or 1 titles.
    if (titles.size() < 2) {
        return;
    }

    quickSortHelper(titles, 0,
                    static_cast<int>(titles.size()) - 1,
                    cmp);
}
