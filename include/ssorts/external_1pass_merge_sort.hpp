#ifndef SS_MERGE_1PASS_SORT_HPP
#define SS_MERGE_1PASS_SORT_HPP

#include <cstddef>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include "util.hpp"

// f. tmp1, tmp2, tmp3, tmp4 - files opened in binary write-extended mode
void merge_1pass_sort(
	std::FILE *f, std::FILE *tmp1, std::FILE *tmp2, std::FILE *tmp3, std::FILE *tmp4,
	std::size_t len, std::size_t elsize,
	comparator_t comparator
) {
	if (!f || !tmp1 || !tmp2 || !tmp3 || !tmp4 || len < 2 || elsize == 0 || !comparator) return;
	fseek(f, 0, SEEK_SET);
	fseek(tmp1, 0, SEEK_SET);
	fseek(tmp2, 0, SEEK_SET);
	fseek(tmp3, 0, SEEK_SET);
	fseek(tmp4, 0, SEEK_SET);
	std::size_t len1, len2, len3, len4;
	len1 = len2 = len3 = len4 = 0;
	void *el1 = malloc(2 * elsize);
	void *el2 = (char *)el1 + elsize;
	
	// spread f to tmp1, tmp2
	for (std::size_t i = 0; i < len; i++) {
		fread(el1, elsize, 1, f);
		if (i % 2 == 0) {
			fwrite(el1, elsize, 1, tmp1);
			len1++;
		}
		else {
			fwrite(el1, elsize, 1, tmp2);
			len2++;
		}
	}

	for (std::size_t batch_size = 1; batch_size < len; batch_size *= 2) {
		fseek(tmp1, 0, SEEK_SET);
		fseek(tmp2, 0, SEEK_SET);
		fseek(tmp3, 0, SEEK_SET);
		fseek(tmp4, 0, SEEK_SET);
		
		fread(el1, elsize, 1, tmp1);
		fread(el2, elsize, 1, tmp2);
		std::size_t next_batch_size = batch_size * 2;
		std::FILE *out = tmp3;
		std::size_t *outlen = &len3;
		std::size_t i = 0, j = 0;
		while (i < len1 && j < len2) {
			int cmp = comparator(el1, el2);
			if (cmp == 1) { // el1 > el2
				fwrite(el2, elsize, 1, out);
				j++;
				++*outlen;
				fread(el2, elsize, 1, tmp2);
				if (j == len2 || (j % batch_size == 0 && i < len1)) {
					do {
						fwrite(el1, elsize, 1, out);
						++*outlen;
						i++;
						fread(el1, elsize, 1, tmp1);
					} while (i < len1 && i % batch_size != 0);
					out = out == tmp3 ? tmp4 : tmp3;
					outlen = outlen == &len3 ? &len4 : &len3;
				}
			}
			else { // el1 <= el2
				fwrite(el1, elsize, 1, out);
				i++;
				++*outlen;
				fread(el1, elsize, 1, tmp1);
				if (i == len1 || (i % batch_size == 0 && j < len2)) {
					do {
						fwrite(el2, elsize, 1, out);
						j++;
						++*outlen;
						fread(el2, elsize, 1, tmp2);
					} while(j < len2 && j % batch_size != 0);
					out = out == tmp3 ? tmp4 : tmp3;
					outlen = outlen == &len3 ? &len4 : &len3;
				}
			}
		}
		while (i < len1) {
			fwrite(el1, elsize, 1, out);
			i++;
			++*outlen;
			fread(el1, elsize, 1, tmp1);
		}
		std::swap(tmp1, tmp3);
		std::swap(tmp2, tmp4);
		len1 = len3;
		len2 = len4;
		len3 = len4 = 0;
	}
	fseek(f, 0, SEEK_SET);
	fseek(tmp1, 0, SEEK_SET);
	for (std::size_t i = 0; i < len1; i++) {
		fread(el1, elsize, 1, tmp1);
		fwrite(el1, elsize, 1, f);
	}
	free(el1); // el2 = el1
}

template<typename T>
void merge_1pass_sort_default(std::FILE *f, std::FILE *tmp1, std::FILE *tmp2, std::FILE *tmp3, std::FILE *tmp4, std::size_t len) {
	merge_1pass_sort(f, tmp1, tmp2, tmp3, tmp4, len, sizeof(T), default_comparator<T>);
}

#endif
