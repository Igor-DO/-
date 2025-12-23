#pragma once
#include"Token.h"
#include<iostream>
#include<fstream>
template<typename T>
class Deque {
	unsigned int LENGHT = 16, SIZE = 0, front_pos = LENGHT / 2 - 1, back_pos = LENGHT / 2;
	T* Array;
	void increas() {
		LENGHT *= 2;
		T* Temp_Array;
		Temp_Array = new T[LENGHT];
		for (int i = 0; i < SIZE; ++i) {
			Temp_Array[LENGHT / 2 - SIZE / 2 + i] = Array[i + front_pos + 1];
		}
		front_pos = LENGHT / 2 - SIZE / 2 - 1;
		back_pos = LENGHT / 2 - SIZE / 2 + SIZE;
		delete[]Array;
		Array = Temp_Array;
	}
public:
	Deque() :front_pos(LENGHT / 2 - 1), back_pos(LENGHT / 2) {
		Array = new T[LENGHT];
	}
	Deque(const Deque& other) : front_pos(other.front_pos), back_pos(other.back_pos), LENGHT(other.LENGHT), SIZE(other.SIZE) {
		Array = new T[LENGHT];
		for (int i = 0; i < SIZE; ++i) {
			Array[i + front_pos] = other.Array[i + front_pos];
		}
	}
	template<bool F>
	class Iterator {
		using DequePtr = std::conditional_t<F, const T*, T*>;
		DequePtr ptr;
	public:
		T& operator*() const {
			return *ptr;
		}
		Iterator(T* ptra)
			:ptr(ptra) {}
		Iterator& operator++() {
			++ptr;
			return *this;
		}
		Iterator& operator--() {
			--ptr;
			return *this;
		}
		Iterator operator++(int) {
			Iterator Temp = *this;
			++Temp.ptr;
			return Temp;
		}
		Iterator operator--(int) {
			Iterator Temp = *this;
			--Temp.ptr;
			return Temp;
		}
		Iterator& operator+=(const size_t n) {
			ptr += n;
			return *this;
		}
		Iterator& operator-=(const size_t n) {
			ptr -= n;
			return *this;
		}
		Iterator operator+(const size_t n) const {
			Iterator Temp(ptr + n);
			return Temp;
		}
		Iterator operator-(const size_t n) const {
			Iterator Temp(ptr - n);
			return Temp;
		}
		int operator-(const Iterator other) {
			return (ptr - other.ptr);
		}
		bool operator==(const Iterator other) {
			return ptr == other.ptr;
		}
		bool operator!=(const Iterator other) {
			return ptr != other.ptr;
		}
		bool operator>(const Iterator other) {
			return ptr > other.ptr;
		}
		bool operator<(const Iterator other) {
			return ptr < other.ptr;
		}
	};
	using iterator = Iterator<false>;
	using const_iterator = Iterator<true>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	T& operator[](size_t n) {
		return Array[front_pos + n + 1];
	}
	const T& operator[](size_t n) const {
		return Array[front_pos + n + 1];
	}
	void resize(const int len) {
		for (int i = 0; i < len; ++i) {
			if (back_pos >= LENGHT - 1) {
				increas();
			}
			++back_pos;
			++SIZE;
		}
	}
	void push_back(const T& element) {
		if (back_pos >= LENGHT - 1) {
			increas();
		}
		Array[back_pos] = element;
		++back_pos;

		++SIZE;
	}
	void push_front(const T& element) {
		if (front_pos < 0) {
			increas();
		}

		Array[front_pos] = element;
		--front_pos;
		++SIZE;
	}
	void pop_back() {
		if (back_pos < 0)return;
		--back_pos;
		--SIZE;
		if (back_pos == front_pos) {
			front_pos = LENGHT / 2 - 1;
			back_pos = LENGHT / 2;
		}
	}
	void pop_front() {
		if (front_pos == LENGHT)return;
		++front_pos;
		--SIZE;
		if (back_pos == front_pos) {
			front_pos = LENGHT / 2 - 1;
			back_pos = LENGHT / 2;
		}
	}
	T& back() {
		return Array[back_pos - 1];
	}
	T& front() {
		return Array[front_pos + 1];
	}
	const T& back() const {
		return Array[back_pos];
	}
	const T& front() const {
		return Array[front_pos];
	}
	const unsigned int size() const {
		return SIZE;
	}
	const bool empty() const {
		return (SIZE == 0);
	}
	iterator begin() {
		iterator A(Array + front_pos + 2);
		return A;
	}
	iterator begin() const {

		iterator A(Array + front_pos + 2);
		return A;
	}
	iterator end() {
		iterator A(Array + back_pos);
		return A;
	}
	iterator end() const {
		iterator A(Array + back_pos);
		return A;
	}
	reverse_iterator rbegin() {
		reverse_iterator A(Array + front_pos + 2);
		return A;
	}
	reverse_iterator rbegin() const {
		reverse_iterator A(Array + front_pos + 2);
		return A;
	}
	reverse_iterator rend() {
		reverse_iterator A(Array + back_pos);
		return A;
	}
	reverse_iterator rend() const {
		reverse_iterator A(Array + back_pos);
		return A;
	}
	const_iterator cbegin() const {
		const_iterator A(Array + front_pos + 2);
		return A;
	}
	const_iterator cend() const {
		const_iterator A(Array + back_pos);
		return A;
	}
	const_reverse_iterator crbegin() const {
		const_reverse_iterator A(Array + front_pos + 2);
		return T;
	}
	const_reverse_iterator crend() const {
		const_reverse_iterator A(Array + back_pos);
		return A;
	}
};
class HashTable {
	Deque<Deque<Token>>Table;
	int SIZE = 31, count = 0;
	size_t Hash_func(const std::string s);
	int enlarge(int n);
public:
	HashTable() ;
	void resize();
	void insert(const Token& tok);
	void print();
	~HashTable() = default;
};