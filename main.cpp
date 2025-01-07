#include <ssorts/external_natural_merge_sort.hpp>
#include "test/util.hpp"

int main(void) {
	files ff = lots_fopen("run", false);
	std::size_t const len = 10;
	int data[len] = {5, 1, 3, 4, 0, 9, 8, 7, 6, 2};
	array_to_file(ff.f, data, len);
	arrayi_print(ff.fin, data, len);
	// merge_1pass_sort_default<int>(ff.f, ff.tmp1, ff.tmp2, ff.tmp3, ff.tmp4, len);
	merge_natural_sort_default<int>(ff.f, ff.tmp1, ff.tmp2, len);
	array_from_file(ff.f, data, len);
	arrayi_print(ff.fout, data, len);
	lots_fclose(ff);
	for (std::size_t i = 0; i < len; i++) printf("%d ", data[i]);
	printf("\n");
	return 0;
}
