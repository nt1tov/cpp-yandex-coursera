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
    T* Allocate(){
        if(free_pool.empty()){
            T* ptr = new T;
            alloc_set.insert(ptr);
            return ptr;
        }
        return AllocExisted();
    }
    T* TryAllocate(){
        if(free_pool.empty()){
            return nullptr;
        }
        return AllocExisted();
    }

    void Deallocate(T* object){
        if(alloc_set.find(object) == alloc_set.end()){
            throw invalid_argument("object is not allocated");
        }
        alloc_set.erase(object);
        free_pool.push(object);
    }

    ~ObjectPool(){
        for(auto alloc_ptr: alloc_set){
            delete alloc_ptr;
        }
        while(!free_pool.empty()){
            auto free_ptr = free_pool.front();
            free_pool.pop();
            delete free_ptr;
        }
    }

private:
    T* AllocExisted(){
        T* ptr = free_pool.front();
        free_pool.pop();
        alloc_set.insert(ptr);
        return ptr;
    }
    set<T*> alloc_set;
    queue<T*> free_pool;
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

// int main() {
//     TestRunner tr;
//     RUN_TEST(tr, TestObjectPool);
//     return 0;
// }
