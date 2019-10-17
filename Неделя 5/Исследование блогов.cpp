#include "test_runner.h"
#include "profile.h"
 
#include <map>
#include <string>
#include <future>
 
using namespace std;
 
struct Stats {
  map<string, int> word_frequences;
 
  void operator += (const Stats& other) {
      map<string, int> other_map = other.word_frequences;
      for (auto now : other_map) {
          word_frequences[now.first] += other_map[now.first];
      }
  }
};
 
    
Stats Explore(const vector<string>& vector_words,
                const set<string>& key_words) {
    Stats result;
    map<string, int> new_map;
    for (auto now : vector_words) {
        ++new_map[now];
    }
    for (auto now : key_words) {
        if (new_map[now] != 0) {
            result.word_frequences[now] = new_map[now];
        }
    }
    return result;
}
 
 
vector<string> GetVector(istream& input) {
    vector<string> result;
    for (string line; getline(input, line); ) {
        istringstream ss(line);
        string s;
        while (ss >> s) {
            result.push_back(s);
        }
    }
    return result;
}
   
vector<vector<string>> Pag(const vector<string>& lines, size_t page_size) {
    vector<vector<string>> pages;
    auto begin = lines.begin();
    for (size_t left = distance(begin, lines.end()); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      auto current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});
 
      left -= current_page_size;
      begin = current_page_end;
    }
    return pages;
}

vector<vector<string>> PagOnThreads(const vector<string>& lines, size_t threads) {
    size_t page_size = lines.size() % threads == 0 ? lines.size() / threads : lines.size() / threads + 1;
    vector<vector<string>> pages;
       auto begin = lines.begin();
       for (size_t left = distance(begin, lines.end()); left > 0; ) {
         size_t current_page_size = min(page_size, left);
         auto current_page_end = next(begin, current_page_size);
         pages.push_back({begin, current_page_end});
    
         left -= current_page_size;
         begin = current_page_end;
       }
    return pages;
}


 
Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats result;
    vector<string> lines = GetVector(input);
    vector<future<Stats>> futures;
    vector<vector<string>> Pags = PagOnThreads(lines, 4);
    for (size_t i = 0; i < 4; ++i) {
        vector<string> temp_v = Pags[i];
        futures.push_back(async(Explore, ref(temp_v), ref(key_words)));
    }
    for (auto& now : futures) {
        result += now.get();
    }
    return result;
}
 
void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
 
    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
 
    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}
 
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
