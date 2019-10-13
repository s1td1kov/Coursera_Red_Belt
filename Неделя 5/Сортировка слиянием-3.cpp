#include "test_runner.h"

#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>
#include <numeric>
#include <utility>


using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    
    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
    
    auto range_length = range_end - range_begin;
    auto it1 = elements.begin() + range_length / 3;
    auto it2 = elements.begin() + 2 * range_length / 3;
    
    MergeSort(elements.begin(), it1);
    MergeSort(it1, it2);
    MergeSort(it2, elements.end());
    
    vector<typename RandomIt::value_type> interim_result;
    
    merge(make_move_iterator(elements.begin()), make_move_iterator(it1), make_move_iterator(it1), make_move_iterator(it2), back_inserter(interim_result));
    merge(make_move_iterator(interim_result.begin()), make_move_iterator(interim_result.end()), make_move_iterator(it2), make_move_iterator(elements.end()), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
