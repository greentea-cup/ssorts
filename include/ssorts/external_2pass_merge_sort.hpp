#ifndef SS_MERGE_2PASS_SORT_HPP
#define SS_MERGE_2PASS_SORT_HPP

#include <cstddef>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include "util.hpp"

// f. tmp1, tmp2 - files opened in binary write-extended mode
void merge_2pass_sort(
	std::FILE *f, std::FILE *tmp1, std::FILE *tmp2,
	std::size_t len, std::size_t elsize,
	comparator_t comparator
) {
	if (f == nullptr || tmp1 == nullptr || tmp2 == nullptr || len < 2 || elsize == 0 || comparator == nullptr) return;
	std::size_t len1, len2;
	void *el1 = malloc(2 * elsize);
	void *el2 = (char *)el1 + elsize;
	for (std::size_t batch_size = 1; batch_size < len; batch_size *= 2) {
		fseek(f, 0, SEEK_SET);
		fseek(tmp1, 0, SEEK_SET);
		fseek(tmp2, 0, SEEK_SET);
		bool switch_out = false;
		len1 = len2 = 0;
		for (std::size_t i = 0, batch_counter = 0; i < len; i++, batch_counter++) {
			if (batch_counter == batch_size) {
				switch_out = !switch_out;
				batch_counter = 0;
			}
			fread(el1, elsize, 1, f);
			if (switch_out) {
				fwrite(el1, elsize, 1, tmp2);
				len2++;
			}
			else {
				fwrite(el1, elsize, 1, tmp1);
				len1++;
			}
		}
		fseek(f, 0, SEEK_SET);
		fseek(tmp1, 0, SEEK_SET);
		fseek(tmp2, 0, SEEK_SET);
		std::size_t next_batch_size = batch_size * 2;
		fread(el1, elsize, 1, tmp1);
		fread(el2, elsize, 1, tmp2);
		for (std::size_t i = 0, j = 0; i < len1 && j < len2;) {
			int cmp = comparator(el1, el2);
			if (cmp == 1) { // el1 > el2
				fwrite(el2, elsize, 1, f);
				j++;
				fread(el2, elsize, 1, tmp2);
				if (j == len2 || (j % batch_size == 0 && i < len1)) do {
					fwrite(el1, elsize, 1, f);
					i++;
					fread(el1, elsize, 1, tmp1);
				} while (i < len1 && i % batch_size != 0);
			}
			else { // el1 <= el2
				fwrite(el1, elsize, 1, f);
				i++;
				fread(el1, elsize, 1, tmp1);
				if (i == len1 || (i % batch_size == 0 && j < len2)) do {
					fwrite(el2, elsize, 1, f);
					j++;
					fread(el2, elsize, 1, tmp2);
				} while (j < len2 && j % batch_size != 0);
			}
		}
	}
	free(el1); // el2 = el1
}

template<typename T>
void merge_2pass_sort_default(std::FILE *f, std::FILE *tmp1, std::FILE *tmp2, std::size_t len) {
	merge_2pass_sort(f, tmp1, tmp2, len, sizeof(T), default_comparator<T>);
}

#endif
