#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        map<string, int> other_map = other.word_frequences;
        for (auto now : other_map) {
            word_frequences[now.first] += other_map[now.first];
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats stats;
    istringstream ss(line);
    string s;
    map<string, int> dict;
    while (ss >> s) {
        ++dict[s];
    }
    map<string, int> stat_words;
    for (auto& now : key_words) {
        stat_words[now] = dict[now];
    }
    stats.word_frequences = stat_words;
    for (auto now : key_words) {
        if (stats.word_frequences[now] == 0) {
            stats.word_frequences.erase(now);
        }
    }
    return stats;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}


vector<set<string>> Pag(const set<string>& key_words, size_t page_size) {
    vector<set<string>> pages;
    auto begin = key_words.begin();
    for (size_t left = distance(begin, key_words.end()); left > 0; ) {
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
    vector<future<Stats>> futures;
    for (auto page : Pag(key_words, 2000)) {
        futures.push_back(async([&page, &input]() {
            return ExploreKeyWordsSingleThread(page, input);}));
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
//    vector<set<string>> se = Pag({"a", "b", "c"}, 200);
//    cout << se.size();
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
    
//    for (string line; getline(input, line); ) {
//        result += ExploreLine(key_words, line);
//    }
//    for (auto now : result.word_frequences) {
//        if (now.second == 0) {
//            result.word_frequences.erase(now.first);
//        }
//    }
//    return result;
