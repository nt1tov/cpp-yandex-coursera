#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
//#include "test_runner.h"

using namespace std;

template<typename T>
class Deque{
private:
    vector<T> front_data;
    vector<T> back_data;
    size_t front_size;
    size_t back_size;
public:
    Deque();
    bool Empty() const;
    size_t Size() const;

    T& operator[](const size_t& index);
    const T& operator[](const size_t& index) const;

    T& At(const size_t& index);
    const T& At(const size_t& index) const;

    T& Front();
    const T& Front() const;

    T& Back();
    const T& Back() const;

    void PushFront(const T& el);
    void PushBack(const T& el);
};

template<typename T>
Deque<T>::Deque(): front_size(0), back_size(0)
{
}

template<typename T>
bool Deque<T>::Empty() const{
    return Size() == 0;
}

template<typename T>
size_t Deque<T>::Size() const{
    return front_size + back_size;
}

template<typename T>
T& Deque<T>::At(const size_t& index){
    if(index >= Size() || index < 0){
        ostringstream os;
        os << "Index: " << index;
        throw out_of_range(os.str());
    }
    if(index > front_size-1){
        size_t deq_idx;
        deq_idx = index - front_size;
        return back_data[deq_idx];
    }

    return front_data[front_size - index - 1];
}

template<typename T>
const T& Deque<T>::At(const size_t& index) const{
    if(index >= Size() || index < 0){
        ostringstream os;
        os << "Index: " << index;
        throw out_of_range(os.str());
    }
    if(index > front_size-1){
        size_t deq_idx;
        deq_idx = index - front_size;
        return back_data[deq_idx];
    }
    return front_data[front_size - index - 1];
}

template<typename T>
T& Deque<T>::operator[](const size_t& index){
    if(front_size > 0){
        if(index > front_size-1){
            size_t deq_idx;
            deq_idx = index - front_size;
            return back_data[deq_idx];
        }
        return front_data[front_size - index - 1];
    }
    return back_data[index];
}

template<typename T>
const T& Deque<T>::operator[](const size_t& index) const{
    if(front_size > 0){
        if(index > front_size-1){
            size_t deq_idx;
            deq_idx = index - front_size;
            return back_data[deq_idx];
        }
        return front_data[front_size - index - 1];
    }
    return back_data[index];
}

template<typename T>
T& Deque<T>::Front(){
    if(front_size > 0)
        return front_data[front_size-1];
    return back_data[0];
}

template<typename T>
const T& Deque<T>::Front() const {
    if(front_size > 0)
        return front_data[front_size-1];
    return back_data[0];
}

template<typename T>
T& Deque<T>::Back(){
    if(back_size > 0)
        return back_data[back_size-1];
    return front_data[0];
}

template<typename T>
const T& Deque<T>::Back() const {
    if(back_size > 0)
        return back_data[back_size-1];
    return front_data[0];
}

template<typename T>
void Deque<T>::PushFront(const T& el){
    front_data.push_back(el);
    ++front_size;
}

template<typename T>
void Deque<T>::PushBack(const T& el){
    back_data.push_back(el);
    ++back_size;
}


// void TestDeque(){
//     Deque<int> deq;
//     ASSERT_EQUAL(deq.Size(), 0u);
//     ASSERT(deq.Empty());

//     deq.PushBack(3);
//     deq.PushBack(4);
//     ASSERT_EQUAL(deq.Size(), 2u);
//     ASSERT_EQUAL(deq.Front(), 3u);

//     Deque<int> deq1;
//     deq1.PushFront(2);
//     deq1.PushFront(1);
//     ASSERT_EQUAL(deq1.Size(), 2u);
//     ASSERT_EQUAL(deq1.Back(), 2u);

//     deq.PushFront(2);
//     deq.PushFront(1);
//     ASSERT_EQUAL(deq.Size(), 4u);

//     ASSERT_EQUAL(deq[0], 1u);
//     ASSERT_EQUAL(deq[1], 2u);
//     ASSERT_EQUAL(deq[2], 3u);
//     ASSERT_EQUAL(deq[3], 4u);

//     ASSERT_EQUAL(deq.Front(), 1u);
//     ASSERT_EQUAL(deq.Back(), 4u);


//     ASSERT_EQUAL(deq.At(0), 1u);
//     ASSERT_EQUAL(deq.At(1), 2u);
//     ASSERT_EQUAL(deq.At(2), 3u);
//     ASSERT_EQUAL(deq.At(3), 4u);

//     Deque<int> deq3;
//     deq3.PushFront(5);
//     deq3.PushFront(4);
//     deq3.PushFront(3);
//     deq3.PushFront(2);
//     deq3.PushFront(1);
//   //  deq3.Back()=1;
//     std::cout<<deq3[4]<<'\n';
// }



// int main() {
// 	TestRunner tr;
// 	RUN_TEST(tr, TestDeque);
// 	return 0;
// }






