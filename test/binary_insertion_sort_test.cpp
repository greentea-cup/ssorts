#include "util.hpp"
#include "ssorts/binary_insertion_sort.hpp"

TEST(TestBinaryInsertionSort, TestOne_Sorted) {
	int data[1] {10};
	binary_insertion_sort(data, 1);
	ASSERT_EQ(data[0], 10);
}

TEST(TestBinaryInsertionSort, Test10_Sorted) {
	std::size_t const len = 10;
	int data[len] {5, 1, 3, 4, 0, 9, 8, 7, 6, 2};
	char str[len*2];
	binary_insertion_sort(data, len);
	array10i_str(str, len*2, data);
	ASSERT_STREQ(str, "0 1 2 3 4 5 6 7 8 9");
}

TEST(TestBinaryInsertionSort, Test100Random_Sorted) {
	std::size_t const len = 100;
	int data[len];
	arrayi_fill(data, len, 50);
	binary_insertion_sort(data, len);
	ASSERT_TRUE(array_is_sorted(data, len));
}

TEST(TestBinaryInsertionSort, Test1000Random_Sorted) {
	std::size_t const len = 1000;
	int data[len];
	arrayi_fill(data, len, 50);
	binary_insertion_sort(data, len);
	ASSERT_TRUE(array_is_sorted(data, len));
}