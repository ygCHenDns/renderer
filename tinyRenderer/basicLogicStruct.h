#pragma once
#ifndef BASIC_LOGIC_STRUCT_H
#define BASIC_LOGIC_STRUCT_H
#include <iostream>
#include <string>
namespace BasicLogicStruct {
	template <class T> class Array {
	private:
		const int basic_size = 32;
		int hold_size = basic_size;
		int size = 0;
		T *data = new T[this->hold_size];
	public:
		Array() {};
		~Array() { 
			delete[] this->data; 
		};
		void append(T append_data) {
			if (this->size >= this->hold_size) {
				this->auto_resize();
			}
			this->data[this->size] = append_data;
			this->size++;
		};
		T get(int n) {
			return this[n];
		};
		void auto_resize() {
			this->do_resize(this->hold_size + this->basic_size);
		};
		void resize(int& new_size) {
			int need_expand_muti = 1;
			int sub_size;
			if ((sub_size = (new_size - this->hold_size)) > 0) {
				int need_expand_muti = (sub_size / basic_size) + 1;
			}
			this->do_resize(this->hold_size + need_expand_muti * this->basic_size);
		};

		void do_resize(int new_size) {
			this->hold_size = new_size;
			T* new_data = new T[this->hold_size];
			for (int i = 0; i < this->hold_size; i++) {
				new_data[i] = this->data[i];
			}
			delete[] this->data;
			this->data = new_data;
		}

		T operator[](size_t n) {
			return this->data[n];
		};
		int get_size() {
			return this->size;
		};
		T* get_data() {
			return this->data;
		};
		void set(size_t& n, T& set_data) {
			if (n >= this->hold_size) {
				this->resize(n);
			}
			if(n > this->size) {
				this->size = n;
			}
			this->data[n] = set_data;
		}
		friend std::ostream& operator<<(std::ostream&, Array<T>& array) {
			std::cout << *array.get_data() << std::endl;
			std::cout << "DATA:{";
			for (int i = 0; i < array.size; i++) {
				std::cout << array.data[i] << ", ";
			}
			std::cout << "}" << std::endl;
			std::cout << "SIZE:" << array.size << std::endl;
			return std::cout;
		};
	};
	Array<std::string> splitStr(const std::string oriStr, const std::string seperator);
}

#endif