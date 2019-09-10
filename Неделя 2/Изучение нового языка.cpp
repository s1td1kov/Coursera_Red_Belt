#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
private:
    set<string> dict;
    
public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            if (dict.count(word) == 0) {
                ++newWords;
                dict.insert(word);
            }
        }
        return newWords;
    }
    
    vector<string> KnownWords() {
        return {dict.begin(), dict.end()};
    }
};
