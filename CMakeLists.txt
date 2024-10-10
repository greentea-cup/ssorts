cmake_minimum_required(VERSION 3.5.0)

project(stankin_greentea_sorts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SS_BUILD_TESTS "Build tests for sorts" OFF)

if (SS_BUILD_TESTS OR BUILD_TESTS)
	enable_testing()
	find_package(GTest MODULE REQUIRED)
	file(GLOB_RECURSE SSORTS_TESTS "test/*.cpp")
	add_executable(ssorts_tests ${SSORTS_TESTS})
	if (MSVC)
		target_compile_options(ssorts_tests PRIVATE /utf-8)
		target_compile_definitions(ssorts_tests PRIVATE _CRT_SECURE_NO_WARNINGS)
	endif()
	target_include_directories(ssorts_tests PRIVATE "include")
	target_link_libraries(ssorts_tests PRIVATE gtest)
	add_test(NAME ssorts_tests_all COMMAND ssorts_tests)
endif()
