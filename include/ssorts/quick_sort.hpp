#ifndef SS_QUICK_SORT_HPP
#define SS_QUICK_SORT_HPP

#include <cstddef>
#include <utility>

template<typename T>
std::size_t partition(T *array, std::size_t start, std::size_t end) {
	T pivot = array[start];
	std::size_t i = start-1;
	std::size_t j = end+1;
	while (1) {
		do i++; while (array[i] < pivot);
		do j--; while (array[j] > pivot);
		if (i < j) std::swap(array[i], array[j]);
		else return j;
	}
}

template<typename T>
void quicksort0(T *array, std::size_t start, std::size_t end) {
	if (start >= end) return;
	size_t p = partition(array, start, end);
	quicksort0(array, start, p);
	quicksort0(array, p+1, end);
}

template<typename T>
void quick_sort(T *array, std::size_t len) {
	if (array == nullptr || len < 2) return;
	quicksort0(array, 0, len-1);
}

#endif
