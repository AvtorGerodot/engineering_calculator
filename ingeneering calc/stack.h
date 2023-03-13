#pragma once
//#include <string>
#include <stdio.h>


//для универсальности работы как со строками, так и с численными типами данных, информацию передаём по указателю
template <typename T>
struct Node {
	T* data;
	Node<T>* next;
	~Node() {
		delete data;
	}
};

template <typename T>
class myStack {
	Node<T>* top;
public:
	myStack() {
		this->top = 0;
	}
	~myStack() {
		while (this->top) {
			Node<T>* temp = top;
			this->top = this->top->next;
			delete temp;
		}
		this->top = 0;
	}
	void push(T* data) {
		Node<T>* n = new Node<T>;
		n->data = data;
		n->next = this->top;
		this->top = n;
	}
	bool pop(T* data) {
		bool have_elements = this->top;
		if (have_elements) {
			Node<T>* temp = this->top;
			data = this->top->data;
			this->top = this->top->next;
			delete temp;
		}
		return have_elements;
	}
	T* peek() {
		return this->top->data;
	}
	bool isEmpty() {
		return !this->top;
	}
	void print() {
		Node<T>* temp = this->top;
		while (temp) {
			//std::cout << temp->data << std::endl;
			printf("%s\n", temp->data);
			temp = temp->next;
		}
	}
};