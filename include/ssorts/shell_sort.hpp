#ifndef SS_SHELL_SORT_HPP
#define SS_SHELL_SORT_HPP

#include <cstddef>
#include <utility>

// wikipedia.org/wiki/Shellsort#Gap_sequences Skean, Ehrenborg, Jaromczyk, 2023
// f(k) = floor(4.0816 * pow(8.5714, k / 2.2449)) unitl f(k) <= SIZE_MAX
static size_t constexpr gaps[] = {7918234608705825792, 3040861179278158848, 1167790191701860608, 448469644431056512, 172227017665743424, 66140810158214120, 25400235268981328, 9754521454701038, 3746055412581965, 1438607851682117, 552472487184852, 212167512320558, 81479266983357, 31290704573633, 12016654407487, 4614788484841, 1772229776913, 680594222789, 261370451015, 100374805392, 38547209596, 14803389773, 5684986049, 2183220659, 838428169, 321983850, 123652334, 47486542, 18236386, 7003368, 2689522, 1032864, 396653, 152328, 58498, 22465, 8627, 3313, 1272, 488, 187, 72, 27, 10, 4, 1};
static size_t constexpr gaps_len = sizeof(gaps) / sizeof(*gaps);

template<typename T>
void shell_sort(T *array, std::size_t len) {
	if (array == nullptr || len < 2) return;
	size_t gap_index = 0;
	for (; gaps[gap_index] >= len; gap_index++);
	for (size_t gap = gaps[gap_index]; gap > 0 && gap_index++ < gaps_len; gap = gaps[gap_index]) {
		for (size_t i = gap; i < len; i++) {
			T tmp = array[i];
			size_t j = i;
			for (; j >= gap && array[j - gap] > tmp; j-= gap) {
				array[j] = array[j - gap];
			}
			array[j] = tmp;
		}
	}
}

#endif
