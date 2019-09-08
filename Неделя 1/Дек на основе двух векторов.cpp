#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

template <typename T>
class Deque {
private:
    vector<T> back;
    vector<T> front;
public:
    Deque() = default;
    
    bool Empty() const {
        return front.empty() && back.empty();
    }
    
    size_t Size() const {
        return front.size() + back.size();
    }
    
    T& operator[](const size_t& index) {
        return index < front.size() ? front[front.size() - index - 1] : back[index - front.size()];
    }
    
    const T& operator[](const size_t& index) const {
        return index < front.size() ? front[front.size() - index - 1] : back[index - front.size()];
    }
    
    T& At(size_t index) {
        if (index >= (front.size() + back.size())) {
            throw out_of_range("");
        } else {
            if (index < front.size()) {
                return front[front.size() - index - 1];
            } else {
                index -= front.size();
                return back[index];
            }
        }
    }
    
    const T& At(size_t index) const {
        if (index >= (front.size() + back.size())) {
            throw out_of_range("");
        } else {
            if (index < front.size()) {
                return front[front.size() - index - 1];
            } else {
                index -= front.size();
                return back[index];
            }
        }
    }
    
    T& Front() {
        return front.empty() ? back.front() : front.back();
    }
    
    const T& Front() const {
        return front.empty() ? back.front() : front.back();
    }
    
    T& Back() {
        return back.empty() ? front.front() : back.back();
    }
    
    const T& Back() const {
        return back.empty() ? front.front() : back.back();
    }
    
    void PushFront(const T& t) {
        front.push_back(t);
    }
    
    void PushBack(const T& t) {
        back.push_back(t);
    }
    
};

int main() {
    
}
