#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

template <typename T>
class Table {
public:
    typename vector<vector<T>>::iterator begin() {
        return table.begin();
    }
    
    typename vector<vector<T>>::iterator end() {
        return table.end();
    }
    
    Table(size_t n, size_t m) {
        table.resize(n);
        for (auto& v : table) {
            v.resize(m);
        }
    }
    
    vector<T>& operator[](size_t i) {
        return table[i];
    }
    
    const vector<T>& operator[](size_t i) const {
        return table[i];
    }
    
    void Resize(size_t n, size_t m) {
        table.resize(n);
        for (auto& v : table) {
            v.resize(m);
        }
    }
    
    pair<size_t, size_t> Size() const {
        return {table.size(), table[0].size()};
    }
private:
    vector<vector<T>> table;
};

/*void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
    
}*/
