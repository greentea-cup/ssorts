#include <random>
#include "util.hpp"

void array10i_str(char *buffer, std::size_t buffer_size, int data[10]) {
	GTEST_SNPRINTF_(
		buffer, buffer_size, "%d %d %d %d %d %d %d %d %d %d",
		data[0], data[1], data[2], data[3], data[4],
		data[5], data[6], data[7], data[8], data[9]
	);
}

void arrayi_fill(int data[100], std::size_t len, int maxv) {
	for (std::size_t i = 0; i < len; i++) {
		data[i] = rand() % maxv;
	}
}

files lots_fopen(char const *prefix, bool four_tmps) {
	files result = {0};
	char name[256];
	sprintf(name, "tmp/%s_in.txt", prefix);
	result.fin = fopen(name, "w");
	sprintf(name, "tmp/%s", prefix);
	result.f = fopen(name, "w+b");
	sprintf(name, "tmp/%s_tmp1", prefix);
	result.tmp1 = fopen(name, "w+b");
	sprintf(name, "tmp/%s_tmp2", prefix);
	result.tmp2 = fopen(name, "w+b");
	if (four_tmps) {
		sprintf(name, "tmp/%s_tmp3", prefix);
		result.tmp3 = fopen(name, "w+b");
		sprintf(name, "tmp/%s_tmp4", prefix);
		result.tmp4 = fopen(name, "w+b");
	}
	sprintf(name, "tmp/%s_out.txt", prefix);
	result.fout = fopen(name, "w");
	return result;
}

void lots_fclose(files ff) {
	if (ff.f != nullptr) fclose(ff.f);
	if (ff.fin != nullptr) fclose(ff.fin);
	if (ff.fout != nullptr) fclose(ff.fout);
	if (ff.tmp1 != nullptr) fclose(ff.tmp1);
	if (ff.tmp2 != nullptr) fclose(ff.tmp2);
	if (ff.tmp3 != nullptr) fclose(ff.tmp3);
	if (ff.tmp4 != nullptr) fclose(ff.tmp4);
}

void arrayi_print(std::FILE *to, int const *array, std::size_t len) {
	for (std::size_t i = 0; i < len; i++) fprintf(to, "%d ", array[i]);
}

