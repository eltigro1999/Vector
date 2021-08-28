#pragma once
#include <memory>
#include <stdexcept>

template <typename T>
class vector{
	T* arr=nullptr;
	size_t size;
	size_t capacity;
	public:
	class iterator {
		private:
			T* ptr=nullptr;
		public:
			iterator(const iterator& it) {
				ptr=it.ptr;
			}
			iterator(T* ptr):ptr(ptr){}
			~iterator(){}
			iterator& operator+=(const int& n) {
				ptr+=n;
				return *(this);
			}
			iterator& operator-=(const int& n) {
				ptr-=n;
				return *(this);
			}
			iterator& operator+(const int& n) {
				iterator it=*this;
				return it+=n;
			}
			iterator& operator-(const int& n) {
				iterator it=*this;
				return it-=n;
			}
			iterator& operator++() {
				return *this+=1;
			}
			iterator& operator++(int) {
				iterator it=*this;
				*this+=1;
				return it;
			}
			iterator& operator--() {
				return *this-=1;
			}
			iterator& operator--(int) {
				iterator it=*this;
				*this-=1;
				return it;
			}
			T& operator*() {
				return *ptr;
			}
			T& operator->() {
				return ptr;
			}
			iterator& operator=(const iterator& it) {
				ptr=it.ptr;
				return *this;
			}

			bool operator<(const iterator& it) {
				return ptr<it.ptr;
			}
			bool operator>(const iterator& it) {
				return this>it;
			}
			bool operator!=(const iterator& it) {
				return !(ptr==it.ptr);
			}
			bool operator==(const iterator& it) {
				return ptr==it.ptr;
			}
	};
	
	vector() : size(0),capacity(0) {}
	
	vector(size_t n, const T& value=T()) : size(n), capacity(n){
		arr=new T[n*sizeof(T)];
		std::fill(arr, arr+n, value);
	}
	vector(const vector<T>& v):size(v.size), capacity(v.capacity) {
	}//finish copy constructor
	vector(std::initializer_list<T> init): size(init.size()), capacity(size) {
		arr=new T[size];
		int i=0;
		for (const T& element:init) {
			arr[i]=element;
			i++;
		}
	}
	void reserve(size_t n) {
		if (n<size) {
			return;
		}
		T* new_arr=reinterpret_cast<T*>(::operator new(n*sizeof(T)));
		try {
			std::uninitialized_copy(arr, arr+size, new_arr);
		} catch (...) {
			delete[] reinterpret_cast<int8_t*>(new_arr);
			throw;
		}
		for (size_t i=0;i<size;++i) {
			(arr+i)->~T();
		}
		operator delete(reinterpret_cast<int8_t*>(arr));
		arr=new_arr;
		capacity=n;
	}
	
	void push_back(const T& value) {
		if(size+1>capacity){
			reserve(size*2);
		}
		new(arr+size)T(value);
		size++;
	}
	
	void pop_back() {
		if(size!=0) {
			(arr+size-1)->~T();
			size-=1;
		}

	}
	void shrink_to_fit() {
		reserve(size);
		capacity=size;
	}
	void resize(const size_t& n, const T& value=T()){
		if (n<=size) {
			for (size_t i=n; i<size; ++i) {
				(arr+i)->~T();
			}
		} else {
			if (n>capacity) {
		       		reserve(n*2);
			}
			for(size_t i=size; i<n; ++i) {
				new(arr+i)T(value);
			}
		}
		size=n;
	}
	
	const T& at(const int& index) const {
		if(index<0 || index>=static_cast<int>(size)) {
			throw std::out_of_range("Out of range");
		}
		return arr[index];
	}

	T& at(const int& index) {
		if(index<0 || index>=static_cast<int>(size)) {
			throw std::out_of_range("Out of range");
		}
		return arr[index];
	}

	bool empty(){
		return !size;
	}

	const T& operator[](const int& index) const {
		return arr[index];
	}
	
	T& operator[](const int& index) {
		return arr[index];
	}

	int sz() const {
		return size;
	}

	int cap() const {
		return capacity;
	}

	iterator begin() const {
		return iterator(arr);
	}
	iterator end() const {
		return iterator(arr+size);
	}
	~vector() {
		for(size_t i=0;i<size;++i) {
			(arr+i)->~T();
		}
		::operator delete(arr);
		
	}
};
