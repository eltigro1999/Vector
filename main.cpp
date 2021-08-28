#include <iostream>
#include "vector.h"
//#include <vector>
#include <string>

template <typename T>
typename vector<T>::iterator begin(const vector<T>& v) {
	return v.begin();
}

template <typename T>
typename vector<T>::iterator end(const vector<T>& v) {
	return v.end();
}
template<typename T>
void show_all_elements(const T& v) {
	std::cout<<"Here"<<v.cap()<<" "<<v.sz()<<std::endl;
	for(const auto& element:v) {
		std::cout<<element<<" ";
	}
	std::cout<<std::endl;
}

int main() {
	vector<int> v(10,100);
	for(const auto& element : v) {
		std::cout<<element<<" ";
	}
}
