#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (deallocated.size() != 0) {
            auto uk = deallocated.front();
            allocated.insert(uk);
            deallocated.pop();
            return uk;
        }
        T* tptr = new T;
        allocated.insert(tptr);
        return tptr;
    }
    T* TryAllocate() {
        if (deallocated.size() == 0) {
            return nullptr;
        }
        auto uk = deallocated.front();
        deallocated.pop();
        allocated.insert(uk);
        return uk;
    }
    
    void Deallocate(T* object) {
        if (allocated.count(object)) {
            deallocated.push(object);
            allocated.erase(object);
        }
        else {
            throw invalid_argument("invalid argument");
        }
        
    }
    
    ~ObjectPool() {
        for (auto now : allocated) {
            delete now;
        }
        
        allocated.erase(allocated.begin(), allocated.end());
        
        while (!deallocated.empty()) {
            delete deallocated.front();
            deallocated.pop();
        }
    }
    
    
private:
    set<T*> allocated;
    queue<T*> deallocated;
};

void TestObjectPool() {
    ObjectPool<string> pool;
    
    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();
    
    *p1 = "first";
    *p2 = "second";
    *p3 = "third";
    
    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");
    
    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");
    
    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
     return 0;
}
