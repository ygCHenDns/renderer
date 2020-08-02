#pragma once
#ifndef BASIC_LOGIC_STRUCT_H
#define BASIC_LOGIC_STRUCT_H
#include <iostream>
#include <string>
#include <assert.h>
namespace BasicLogicStruct {
	template <class T> class Array {
	private:
		const int basic_size = 32;
		int hold_size = basic_size;
		int size = 0;
		T *data = new T[this->hold_size];
	public:
		Array() {};
		Array(const BasicLogicStruct::Array<T>& array_t) {
			for (int i = 0; i < array_t.size; i++) {
				this->append(array_t.data[i]);
			}
		};
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
		int get_hold_size() {
			return this->hold_size;
		}
		void set(size_t& n, T& set_data) {
			if (n >= this->hold_size) {
				this->resize(n);
			}
			if(n > this->size) {
				this->size = n;
			}
			this->data[n] = set_data;
		}
		void slice(size_t start_pos=0, size_t end_pos=-1) {

			if (end_pos == -1) {
				end_pos = this->size;
			}

			assert(start_pos <= end_pos);

			int new_size = end_pos - start_pos;

			int need_expand_muti = (new_size / basic_size) + 1;
			this->hold_size = this->basic_size * need_expand_muti;
			T* new_data = new T[this->hold_size];
			for (int i = 0; i < this->size; i++) {
				new_data[i] = this->data[start_pos + i];
			}
			delete[] this->data;
			this->data = new_data;
		}
		friend std::ostream& operator<<(std::ostream&, Array<T>& array) {
			std::cout << "DATA:{";
			for (int i = 0; i < array.size; i++) {
				std::cout << array.data[i] << ", ";
			}
			std::cout << "}" << std::endl;
			std::cout << "SIZE:" << array.size << std::endl;
			return std::cout;
		};
		Array<T>& operator =(BasicLogicStruct::Array<T>& array_t) {
			return this->copy(array_t);
		};
		Array<T>& copy(BasicLogicStruct::Array<T>& array_t) {
			this->hold_size = array_t.get_hold_size();
			T* new_data = new T[this->hold_size];
			delete[] this->data;
			this->data = new_data;
			for (int i = 0; i < array_t.get_size(); i++) {
				this->append(array_t.get_data()[i]);
			}
			return *this;
		}

	};
	void splitStr(const std::string oriStr, const std::string seperator, Array<std::string>&);
	void convert_str_array(Array<int>& int_array, Array<std::string>& str_array);
	void convert_str_array(Array<float>& int_array, Array<std::string>& str_array);

}

#endif