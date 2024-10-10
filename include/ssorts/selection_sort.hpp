#ifndef SS_SELECTION_SORT_HPP
#define SS_SELECTION_SORT_HPP

#include <cstddef>
#include <utility>

template<typename T>
void selection_sort(T *array, std::size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t i = 0; i < len; i++) {
		std::size_t minj = i;
		for (std::size_t j = i; j < len; j++) {
			if (array[j] < array[minj]) minj = j;
		}
		if (minj != i) std::swap(array[i], array[minj]);
	}
}

#endif
