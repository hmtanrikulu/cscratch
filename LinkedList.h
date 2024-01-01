#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

template <typename T>
class LinkedList {
	Node<T>* head;
public:
	int length;
	void insert(T x) {
		Node<T>* newElement = new Node<T>(x);
		if (this->head == nullptr) {
			this->head = newElement;
			this->length += 1;
		}
		else {
			Node<T>* tmp = this->head;
			while (tmp->next != nullptr) {
				tmp = tmp->next;
			}
			tmp->next = newElement;
			this->length += 1;
		}
	}
	void del(int x) {
		if (x < 0 || x >= this->length) throw std::runtime_error("Index out of range");

		Node<T>* iterator = nullptr;
		if (x == 0) {
			iterator = head;
			head = head->next;
		}
		else {
			Node<T>* prev = head;
			iterator = head->next;
			for (int i = 1; i < x; ++i) {
				prev = iterator;
				iterator = iterator->next;
			}
			prev->next = iterator->next;
		}

		delete iterator;
		iterator = nullptr;
		this->length -= 1;
	}


	T& operator[](int x) {
		if (x < 0 || x >= this->length) {
			throw std::runtime_error("Index out of Boundary");
		}

		Node<T>* iterator = this->head; // error "Unhandled Exception" occurs here
		for (int i = 0; i < x; ++i) {
			iterator = iterator->next;
		}

		return iterator->data; // Assuming Node has a 'data' member of type T
	}


	LinkedList() {
		this->head = nullptr;
		this->length = 0;
	}
};


#endif