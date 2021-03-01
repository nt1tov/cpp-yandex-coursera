#pragma once

#include <cstdlib>

using namespace std;
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
	SimpleVector() {}
	explicit SimpleVector(size_t size):
		size_(size),
		capacity_(size)
	{
		data_ptr_ = new T[capacity_];
	}
	~SimpleVector(){
		delete[] data_ptr_;
	}

	T& operator[](size_t index){
		return data_ptr_[index];
	}

	T* begin(){
		return data_ptr_;
	}
	T* end(){
		return data_ptr_ + size_;
	}

	size_t Size() const{
		return size_;
	}
	size_t Capacity() const{
		return capacity_;
	}
	void PushBack(const T& value){
		if(size_ == 0){
			ReAllocate(1);
		}
		else if((size_ + 1) >= capacity_){
			ReAllocate(capacity_ * 2);
		}
		data_ptr_[size_] = value;
		++size_;
	}

private:
	void ReAllocate(const size_t& count){
		T* new_alloc_ptr = new T[count];
		if(data_ptr_ !=  nullptr){
			for(auto i = 0; i < size_; ++i){
				new_alloc_ptr[i] = data_ptr_[i];
			}
			delete[] data_ptr_;
		}
		capacity_ = count;
		data_ptr_ = new_alloc_ptr;
	}
	T* data_ptr_ = nullptr;
	size_t capacity_ = 0u;
	size_t size_ =  0u;

};
