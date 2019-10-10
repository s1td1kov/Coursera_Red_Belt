#include "test_runner.h"

#include <vector>

using namespace std;


template <typename Token>
using Sentence = vector<Token>;

template <typename Token>

vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> sentences;
    Sentence<Token> sentence;
    // bool flag = true;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (!it->IsEndSentencePunctuation()) {
            sentence.push_back(move(*it));
        } else {
            if (next(it) != tokens.end() && next(it)->IsEndSentencePunctuation()) {
                sentence.push_back(move(*it));
            } else {
                sentence.push_back(move(*it));
                sentences.push_back(move(sentence));
                sentence.clear();
            }
        }
    }
    if (sentence.size()) {
        sentences.push_back(move(sentence));
    }
    return sentences;
}



struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );
    
    

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
