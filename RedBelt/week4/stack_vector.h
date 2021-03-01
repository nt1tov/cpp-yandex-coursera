#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0){
    if(a_size > N){
      throw invalid_argument("");
    }
    size_ = a_size;
  }

  T& operator[](size_t index){
    return data[index];
  }
  const T& operator[](size_t index) const{
    return data.at(index);
  }

  typename array<T, N>::iterator begin(){
    return data.begin();
  }
  typename array<T, N>::iterator end(){
    if(Size() == 0){
      return data.begin();
    }
    return data.end();
  }
  typename array<T, N>::const_iterator begin() const{
    return data.cbegin();
  }
  typename array<T, N>::const_iterator end() const{
    if(Size() == 0){
      return data.cbegin();
    }
    return data.cend();
  }

  size_t Size() const{
    return size_;
  }
  size_t Capacity() const{
    return N;
  }

  void PushBack(const T& value){
    if(Size() == Capacity()){
      throw overflow_error("");
    }
    size_ += 1;
    data[size_-1] = value;
  }
  T PopBack(){
    if(Size() == 0u){
      throw underflow_error("");
    }
    size_ -= 1;
    return data[size_];
  }

private:
  array<T, N> data;
  size_t size_ = 0;
};

