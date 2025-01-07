#ifndef SS_MERGE_NATURAL_SORT_HPP
#define SS_MERGE_NATURAL_SORT_HPP

#include <cstddef>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include "util.hpp"

// f. tmp1, tmp2 - files opened in binary write-extended mode
void merge_natural_sort(
	std::FILE *f, std::FILE *tmp1, std::FILE *tmp2,
	std::size_t len, std::size_t elsize,
	comparator_t comparator
) {
	if (f == nullptr || tmp1 == nullptr || tmp2 == nullptr || len < 2 || elsize == 0 || comparator == nullptr) return;
	std::size_t len1, len2;
	void *el = malloc(2 * elsize);
	while(1) {
		// spread
		void *el1 = el, *el2 = (char *)el + elsize;
		fseek(f, 0, SEEK_SET);
		fseek(tmp1, 0, SEEK_SET);
		fseek(tmp2, 0, SEEK_SET);
		bool switch_out = false;
		len1 = len2 = 0;
		fread(el2, elsize, 1, f);
		fwrite(el2, elsize, 1, tmp1);
		len1++;
		for (std::size_t i = 1; i < len; i++) {
			fread(el1, elsize, 1, f);
			int cmp = comparator(el1, el2);
			if (cmp == -1) switch_out = !switch_out;
			if (switch_out) {
				fwrite(el1, elsize, 1, tmp2);
				len2++;
			}
			else {
				fwrite(el1, elsize, 1, tmp1);
				len1++;
			}
			std::swap(el1, el2); // put current to prev (without copy)
		}
		if (len1 == 0 || len2 == 0) break;
		{
			fseek(f, 0, SEEK_SET);
			fseek(tmp1, 0, SEEK_SET);
			fseek(tmp2, 0, SEEK_SET);
			printf("f: ");
			for (std::size_t i = 0; i < len; i++) {
				fread(el1, elsize, 1, f);
				printf("%d ", *(int const *)el1);
			}
			printf("\ntmp1: ");
			for (std::size_t i = 0; i < len1; i++) {
				fread(el1, elsize, 1, tmp1);
				printf("%d ", *(int const *)el1);
			}
			printf("\ntmp2: ");
			for (std::size_t i = 0; i < len2; i++) {
				fread(el1, elsize, 1, tmp2);
				printf("%d ", *(int const *)el1);
			}
			printf("\n");
		}
		fseek(f, 0, SEEK_SET);
		fseek(tmp1, 0, SEEK_SET);
		fseek(tmp2, 0, SEEK_SET);
		std::size_t i = 0, j = 0;
		// merge
		fread(el1, elsize, 1, tmp1);
		fread(el2, elsize, 1, tmp2);
		while (i < len1 && j < len2) {
			int cmp = comparator(el1, el2);
			if (cmp == 1) { // el1 > el2
				fwrite(el2, elsize, 1, f);
				j++;
				fread(el2, elsize, 1, tmp2);
			}
			else { // el1 <= el2
				fwrite(el1, elsize, 1, f);
				i++;
				fread(el1, elsize, 1, tmp1);
			}
		}
		// copy rest
		while (i < len1) {
			fwrite(el1, elsize, 1, f);
			i++;
			fread(el1, elsize, 1, tmp1);
		}
		while (j < len2) {
			fwrite(el2, elsize, 1, f);
			j++;
			fread(el2, elsize, 1, tmp2);
		}
	}
	free(el);
}

template<typename T>
void merge_natural_sort_default(std::FILE *f, std::FILE *tmp1, std::FILE *tmp2, std::size_t len) {
	merge_natural_sort(f, tmp1, tmp2, len, sizeof(T), default_comparator<T>);
}

#endif
