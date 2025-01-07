#include "util.hpp"
#include "ssorts/external_1pass_merge_sort.hpp"

TEST(TestExternal1PassMergeSort, TestComparators) {
	comparator_t c = default_comparator<int>;
	int a, b;
	a = 10, b = 10;
	ASSERT_EQ(c(&a, &b), 0) << "10 == 10 ?";
	a = 5, b = 10;
	ASSERT_EQ(c(&a, &b), -1) << "5 < 10 ?";
	a = 10, b = 5;
	ASSERT_EQ(c(&a, &b), 1) << "10 > 5 ?";
}

TEST(TestExternal1PassMergeSort, TestOne_Sorted) {
	std::size_t const len = 1;
	int data[len] {10};
	files ff = lots_fopen("merge1pass_1", true);
	arrayi_print(ff.fin, data, len);
	array_to_file(ff.f, data, len);
	merge_1pass_sort_default<int>(ff.f, ff.tmp1, ff.tmp2, ff.tmp3, ff.tmp4, len);
	array_from_file(ff.f, data, len);
	arrayi_print(ff.fout, data, len);
	lots_fclose(ff);
	ASSERT_EQ(data[0], 10);
}

TEST(TestExternal1PassMergeSort, Test10_Sorted) {
	std::size_t const len = 10;
	int data[len] {5, 1, 3, 4, 0, 9, 8, 7, 6, 2};
	char str[len*2];
	files ff = lots_fopen("merge1pass_10", true);
	arrayi_print(ff.fin, data, len);
	array_to_file(ff.f, data, len);
	merge_1pass_sort_default<int>(ff.f, ff.tmp1, ff.tmp2, ff.tmp3, ff.tmp4, len);
	array_from_file(ff.f, data, len);
	arrayi_print(ff.fout, data, len);
	lots_fclose(ff);
	array10i_str(str, len*2, data);
	ASSERT_STREQ(str, "0 1 2 3 4 5 6 7 8 9");
}

TEST(TestExternal1PassMergeSort, Test100Random_Sorted) {
	std::size_t const len = 100;
	int data[len];
	arrayi_fill(data, len, 50);
	files ff = lots_fopen("merge1pass_100", true);
	arrayi_print(ff.fin, data, len);
	array_to_file(ff.f, data, len);
	merge_1pass_sort_default<int>(ff.f, ff.tmp1, ff.tmp2, ff.tmp3, ff.tmp4, len);
	array_from_file(ff.f, data, len);
	arrayi_print(ff.fout, data, len);
	lots_fclose(ff);
	ASSERT_TRUE(array_is_sorted(data, len));
}

TEST(TestExternal1PassMergeSort, Test1000Random_Sorted) {
	std::size_t const len = 1000;
	int data[len];
	arrayi_fill(data, len, 50);
	files ff = lots_fopen("merge1pass_1000", true);
	arrayi_print(ff.fin, data, len);
	array_to_file(ff.f, data, len);
	merge_1pass_sort_default<int>(ff.f, ff.tmp1, ff.tmp2, ff.tmp3, ff.tmp4, len);
	array_from_file(ff.f, data, len);
	arrayi_print(ff.fout, data, len);
	lots_fclose(ff);
	ASSERT_TRUE(array_is_sorted(data, len));
}
