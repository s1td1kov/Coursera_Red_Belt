#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor() {}
    
    auto Move(size_t tokens) {
        auto it = kursor;
        for (size_t i = 0; i < tokens; ++i) {
            if (it == text.end()) {
                break;
            }
            
            ++it;
        }
        return it;
    }
    
    void Left() {
        if (kursor != text.begin()) {
            --kursor;
        }
    }
    void Right() {
        if (kursor != text.end()) {
            ++kursor;
        }
    }
    void Insert(char token) {
        text.insert(kursor, token);
    }
    
    void Cut(size_t tokens = 1) {
        bufer.clear();
        list<char>::iterator it = Move(tokens);
        bufer.splice(bufer.begin(), text, kursor, it);
        kursor = it;
    }
    
    void Copy(size_t tokens = 1) {
        auto it = kursor;
        bufer.clear();
        for (size_t i = 0; i < tokens; ++i) {
            if (it != text.end()) {
                bufer.insert(bufer.end(), *it);
                ++it;
            }
        }
    }
    
    void Paste() {
        text.insert(kursor, bufer.begin(), bufer.end());
    }
    
    string GetText() const {
        string total = "";
        for (auto now : text) {
            total += now;
        }
        return total;
    }
    
private:
    list<char> text;
    list<char>::iterator kursor = text.begin();
    list<char> bufer;
    
};



void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
