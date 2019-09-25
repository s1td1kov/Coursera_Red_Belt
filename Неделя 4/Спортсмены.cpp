#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <deque>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int main() {
    
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    list<int> iterators;
    vector<list<int>::iterator> sportsmen(100000, iterators.end());
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int sportsmanNum, sportsmanBefore;
        cin >> sportsmanNum >> sportsmanBefore;
        sportsmen[sportsmanNum] = iterators.insert(sportsmen[sportsmanBefore], sportsmanNum);
    }
    for (const auto& now : iterators) {
        cout << now << " ";
    }
    cout << endl;
    return 0;
}
