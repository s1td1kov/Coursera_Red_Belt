#pragma once

#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() {
        size_ = 0u;
        capacity_ = 0u;
        data = nullptr;
        end_ = nullptr;
    }
    explicit SimpleVector(size_t size) {
        data = new T[size];
        end_ = data + size;
        size_ = size;
        capacity_ = size;
    }
    ~SimpleVector() {
        delete[] data;
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    T* begin() {
        return data;
    }
    T* end() {
        return end_;
    }
    
    const T* begin() const {
        return data;
    }
    const T* end() const {
        return end_;
    }
    
    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity_;
    }
    
    void PushBack(T value) {
        if (size_ == 0u) {
            data = new T[++capacity_];
        } else if (Size() == Capacity()) {
            T* new_data = data;
            capacity_ *= 2;
            data = new T[capacity_];
            for (size_t i = 0; i < Size(); ++i) {
                data[i] = move(new_data[i]);
            }
            delete[] new_data;
        }
        data[size_++] = move(value);
        end_ = data + size_;
    }
    
private:
    T* data;
    T* end_;
    size_t size_ = 0u;
    size_t capacity_ = 0u;
};
