#ifndef SS_SHAKER_SORT_HPP
#define SS_SHAKER_SORT_HPP

#include <cstddef>
#include <utility>

template<typename T>
void shaker_sort(T *array, std::size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t l = 0, r = len; l < r;) {
		bool changed = false;
        for (size_t i = l; i < r-1; i++) {
            // printf("[%zu;%zu) %zu %zu\n", l, r, i, i+1);
			if (array[i+1] < array[i]) {
				std::swap(array[i+1], array[i]);
				changed = true;
			}
        }
        r--;
		if (!changed) break;
		changed = false;
        for (size_t i = r-1; i > l; i--) {
            // printf("[%zu;%zu) %zu %zu\n", l, r, i, i-1);
			if (array[i] < array[i-1]) {
				std::swap(array[i-1], array[i]);
				changed = true;
			}
        }
        l++;
		if (!changed) break;
	}
}

#endif
