#ifndef SS_INSERTION_SORT_HPP
#define SS_INSERTION_SORT_HPP

#include <cstddef>
#include <utility>

template<typename T>
void insertion_sort(T *array, std::size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t i = 1; i < len; i++) {
		if (array[i-1] < array[i]) continue;
		for (std::size_t j = i, k = i;
			k > 0 && array[j] < array[k-1]; k--, j = k) {
			std::swap(array[j], array[k-1]);
		}
	}
}

#endif
