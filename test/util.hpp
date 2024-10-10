#include <random>
#include <gtest/gtest.h>

static inline void array10i_str(char *buffer, std::size_t buffer_size, int data[10]) {
	GTEST_SNPRINTF_(
		buffer, buffer_size, "%d %d %d %d %d %d %d %d %d %d",
		data[0], data[1], data[2], data[3], data[4],
		data[5], data[6], data[7], data[8], data[9]
	);
}

static inline void arrayi_fill(int data[100], std::size_t len, int maxv) {
	for (std::size_t i = 0; i < len; i++) {
		data[i] = rand() % maxv;
	}
}

template<typename T>
bool array_is_sorted(T const *array, std::size_t len) {
	for (std::size_t i = 1; i < len; i++) {
		if (array[i-1] > array[i]) return false;
	}
	return true;
}

