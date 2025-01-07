#ifndef SSORTS_UTIL_HPP
#define SSORTS_UTIL_HPP
// 1 = a > b; 0 = a == b; -1 = a < b
typedef int (*comparator_t)(void const *a, void const *b);

template<typename T>
int default_comparator(void const *a, void const *b) {
	T left = *static_cast<T const *>(a);
	T right = *static_cast<T const *>(b);
	return (left > right) - (left < right);
}
#endif
