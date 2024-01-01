#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node {
public:
	T data;
	Node<T>* next;
	void setData(T x) {
		this->data = x;
	}
	T& getData() {
		return this->data;
	}
	Node(T x) : data(x), next(nullptr) {}
	Node() : data(T()), next(nullptr) {}
};

#endif



