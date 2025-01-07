#ifndef UTILS_HPP
#define UTILS_HPP

#include <gtest/gtest.h>

void array10i_str(char *buffer, std::size_t buffer_size, int data[10]);

void arrayi_fill(int data[100], std::size_t len, int maxv);

template<typename T>
::testing::AssertionResult array_is_sorted(T const *array, std::size_t len) {
	for (std::size_t i = 1; i < len; i++) {
		if (array[i-1] > array[i])
			return ::testing::AssertionFailure() << "array[" << i-1 << "] > array[" << i << "]";
	}
	return ::testing::AssertionSuccess();
}

struct files {
	std::FILE *fin, *fout, *f, *tmp1, *tmp2, *tmp3, *tmp4;
};

files lots_fopen(char const *prefix, bool four_tmps);

void lots_fclose(files ff);

void arrayi_print(std::FILE *to, int const *array, std::size_t len);

template<typename T>
void array_to_file(std::FILE *to, T const *array, std::size_t len) {
	fseek(to, 0, SEEK_SET);
	fwrite(array, sizeof(T), len, to);
}

template<typename T>
void array_from_file(std::FILE *from, T *array, std::size_t len) {
	fseek(from, 0, SEEK_SET);
	fread(array, sizeof(T), len, from);
}
#endif
