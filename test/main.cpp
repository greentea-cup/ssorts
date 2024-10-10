#include <cstdio>
#include <ctime>
#include <gtest/gtest.h>
#include "util.hpp"

int main(int argc, char **argv) {
	srand(time(nullptr));
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

