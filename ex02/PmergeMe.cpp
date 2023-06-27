#include "PmergeMe.hpp"

void insertionList(std::list<int>::iterator start, std::list<int>::iterator end) {
  std::list<int>::iterator ite;
  for (ite = start; ite != end; ++ite) {
    std::list<int>::iterator iteTemp = ite;
    ++iteTemp;
    int temp = *iteTemp;
    while (iteTemp != ite && *iteTemp > temp) {
      *iteTemp = *(--iteTemp);
    }
    *iteTemp = temp;
  }
}

void mergeList(std::list<int>::iterator start, std::list<int>::iterator mid,
               std::list<int>::iterator end) {
  std::list<int> firstList(start, mid);
  std::list<int> secondList(mid, end);

  std::list<int>::iterator iteFirst = firstList.begin();
  std::list<int>::iterator iteSecond = secondList.begin();
  std::list<int>::iterator ite = start;

  while (iteFirst != firstList.end() && iteSecond != secondList.end()) {
    if (*iteSecond > *iteFirst) {
      *ite = *iteFirst;
      ++iteFirst;
    } else {
      *ite = *iteSecond;
      ++iteSecond;
    }
    ++ite;
  }

  while (iteFirst != firstList.end()) {
    *ite = *iteFirst;
    ++iteFirst;
    ++ite;
  }

  while (iteSecond != secondList.end()) {
    *ite = *iteSecond;
    ++iteSecond;
    ++ite;
  }
}

void sortingList(std::list<int>& theList, std::list<int>::iterator start, std::list<int>::iterator end, int midList) {
  int size = std::distance(start, end);
  if (size > midList) {
    std::list<int>::iterator mid = start;
    std::advance(mid, size / 2);

    sortingList(theList, start, mid, midList);
    sortingList(theList, mid, end, midList);
    mergeList(start, mid, end);
  } else {
    insertionList(start, end);
  }
}

void mergeInsertionSort(std::list<int>& theList, int midList) {
  sortingList(theList, theList.begin(), theList.end(), midList);
}

clock_t sortingList(std::list<int>& theList) {
  int midList = 1;
  clock_t start = clock();
  mergeInsertionSort(theList, midList);
  clock_t end = clock();
  return end - start;
}

// ---------------------- DEQUE --------------------------------//
void insertionDeque(std::deque<int>& theDeque, size_t start, size_t end) {
  for (size_t i = start + 1; i <= end; ++i) {
    int temp = theDeque[i];
    size_t j = i - 1;
    while (j >= start && theDeque[j] > temp) {
      theDeque[j + 1] = theDeque[j];
      --j;
    }
    theDeque[j + 1] = temp;
  }
}

void mergeDeque(std::deque<int>& theDeque, size_t start, size_t mid, size_t end) {
  std::deque<int> firstDeque(theDeque.begin() + start, theDeque.begin() + mid + 1);
  std::deque<int> secondDeque(theDeque.begin() + mid + 1, theDeque.begin() + end + 1);

  size_t i = 0;
  size_t j = 0;
  size_t k = start;

  while (i < firstDeque.size() && j < secondDeque.size()) {
    if (firstDeque[i] <= secondDeque[j]) {
      theDeque[k] = firstDeque[i];
      ++i;
    } else {
      theDeque[k] = secondDeque[j];
      ++j;
    }
    ++k;
  }

  while (i < firstDeque.size()) {
    theDeque[k] = firstDeque[i];
    ++i;
    ++k;
  }

  while (j < secondDeque.size()) {
    theDeque[k] = secondDeque[j];
    ++j;
    ++k;
  }
}

void sortingDeque(std::deque<int>& theDeque, size_t start, size_t end, size_t midList) {
    size_t size = end - start + 1;
    if (size > midList) {
    size_t mid = start + (end - start) / 2;

    sortingDeque(theDeque, start, mid, midList);
    sortingDeque(theDeque, mid + 1, end, midList);
    mergeDeque(theDeque, start, mid, end);
    } else {
    insertionDeque(theDeque, start, end);
    }
}

clock_t sortingDeque(std::deque<int>& theDeque) {
    size_t midList = 1;
    clock_t start = clock();
    sortingDeque(theDeque, 0, theDeque.size() - 1, midList);
    clock_t end = clock();
    return end - start;
}