#ifndef SS_BUBBLE_SORT_HPP
#define SS_BUBBLE_SORT_HPP

#include <cstddef>
#include <utility>

template<typename T>
void bubble_sort(T *array, std::size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t i = 0; i < len; i++) {
		for (std::size_t j = 1; j < len; j++) {
			if (array[j-1] > array[j]) std::swap(array[j-1], array[j]);
		}
	}
}

#endif
