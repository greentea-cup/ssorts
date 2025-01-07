#ifndef SS_OPTIMIZED_BUBBLE_SORT_HPP
#define SS_OPTIMIZED_BUBBLE_SORT_HPP

#include <cstddef>
#include <utility>

template<typename T>
void optimized_bubble_sort(T *array, std::size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t i = 0; i < len-1; i++) {
		bool changed = false;
		for (std::size_t j = 0; j < len-i-1; j++) {
			if (array[j] > array[j+1]) changed = true, std::swap(array[j], array[j+1]);
		}
		if (!changed) break;
	}
}

#endif
