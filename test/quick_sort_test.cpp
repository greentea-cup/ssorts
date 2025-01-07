#include "util.hpp"
#include "ssorts/quick_sort.hpp"

TEST(TestQuickSort, TestOne_Sorted) {
	int data[1] {10};
	quick_sort(data, 1);
	ASSERT_EQ(data[0], 10);
}

TEST(TestQuickSort, Test10_Sorted) {
	std::size_t const len = 10;
	int data[len] {5, 1, 3, 4, 0, 9, 8, 7, 6, 2};
	char str[len*2];
	quick_sort(data, len);
	array10i_str(str, len*2, data);
	ASSERT_STREQ(str, "0 1 2 3 4 5 6 7 8 9");
}

TEST(TestQuickSort, Test100Random_Sorted) {
	std::size_t const len = 100;
	int data[len];
	arrayi_fill(data, len, 50);
	quick_sort(data, len);
	ASSERT_TRUE(array_is_sorted(data, len));
}

TEST(TestQuickSort, Test1000Random_Sorted) {
	std::size_t const len = 1000;
	int data[len];
	arrayi_fill(data, len, 50);
	quick_sort(data, len);
	ASSERT_TRUE(array_is_sorted(data, len));
}