#include "MergeSort.h"
#include <vector>

// merges two sorted halves of vector
void merge(std::vector<Title>& titles, int left, int mid, int right, Comparator& cmp) {
    std::vector<Title> temp;

    int i = left;
    int j = mid + 1;

    //compare elements and add smaller ranked element first
    while (i <= mid && j <= right) {

        if (cmp(titles[i], titles[j])) {
            temp.push_back(titles[i]);
            i++;
        }
        else {
            temp.push_back(titles[j]);
            j++;
        }
    }

    // remaining emelents from left half
    while (i <= mid) {
        temp.push_back(titles[i]);
        i++;   
    }
    // remaining elements from right half
    while (j <= right) {
        temp.push_back(titles[j]);
        j++;
    }

    // put merged section back into original vector
    for (int i = 0; i < static_cast<int>(temp.size()); i++) {
        titles[left + i] = temp[i];
    }
}

void mergeSortHelper(std::vector<Title>& titles, int left, int right, Comparator& cmp) {
    // base case
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    // sort left
    mergeSortHelper(titles, left, mid, cmp);

    // sort right
    mergeSortHelper(titles, mid + 1, right, cmp);

    // merge sorted halves
    merge(titles, left, mid, right, cmp);
}

void mergeSort(std::vector<Title>& titles, Comparator& cmp) {
    if (titles.size() < 2) {
        return;
    }

    mergeSortHelper(titles, 0, static_cast<int>(titles.size()) - 1, cmp);
}