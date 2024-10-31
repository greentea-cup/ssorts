#ifndef SS_BINARY_INSERTION_SORT_HPP
#define SS_BINARY_INSERTION_SORT_HPP

#include <cstddef>
#include <utility>

template<typename T>
void binary_insertion_sort(T *array, std::size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t i = 1; i < len; i++) {
		if (array[i - 1] < array[i]) continue;
		// перемещать пока все элементы предыдущие не отсортируются
		// for (std::size_t j = i, k = i;
		// 	k > 0 && array[j] < array[k - 1]; k--, j = k)
		// 	std::swap(array[j], array[k - 1]);
		// найти место, в которое нужно поместить элемент
		// затем сдвинуть все элементы и вставить текущий в нужное место
		std::size_t l = 0, r = i - 1, m;
		while (l < r) {
			m = l + (r - l) / 2;
			if (array[m] > array[i]) r = m;
			else l = m + 1;
		}
		std::size_t pos = r;
		for (std::size_t j = i; j > pos; j--) {
			std::swap(array[j], array[j-1]);
		}
	}
}

#endif
