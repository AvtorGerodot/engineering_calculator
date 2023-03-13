#pragma once
//#include <string>
#include <stdio.h>

template <typename T>
ref struct Node {
	T data;
	Node<T>^ next;
};

template <typename T>
ref class myStack {
	Node<T>^ top;
public:
	myStack() {
		this->top = nullptr;
	}
	~myStack() {
		while (this->top) {
			Node<T>^ temp = top;
			this->top = this->top->next;
			//delete temp;
		}
	}
	void push(T data) {
		Node<T>^ n = gcnew Node<T>;
		n->data = data;
		n->next = this->top;
		this->top = n;
	}
	Node<T>^ pop(T& data) {
		Node<T>^ have_elements = this->top;
		if (have_elements != nullptr) {
			Node<T>^ temp = this->top;
			data = this->top->data;
			this->top = this->top->next;
			delete temp;
		}
		return have_elements;
	}
	T peek() {
		return this->top->data;
	}
	bool isEmpty() {
		return !this->top;
	}
	void print() {
		Node<T>^ temp = this->top;
		while (temp) {
			//std::cout << temp->data << std::endl;
			printf("%s\n", temp->data);
			temp = temp->next;
		}
	}
};