#pragma once
#include <stdexcept>
#include <iostream>
#include "DNode.h"
#include "List.h"

using std::runtime_error;
using std::cout;
using std::endl;

template<typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;
	DNode<E>* tail;
	DNode<E>* current;
	int size;

public:
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
		size = 0;
	}
	void insert(E element) {
		current->next = current->next->previous = new DNode<E>(element, current->next, current);
		size++;
	}
	void append(E element) {
		tail->previous = tail->previous->next = new DNode<E>(element, tail, tail->previous);
		size++;
	}
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("ERROR: List is empty.");
		if (current == tail)
			throw runtime_error("ERROR: No current element.");
		current->next->element = element;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("ERROR: List is empty.");
		if (current == tail)
			throw runtime_error("ERROR: No current element.");
		return current->next->element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("ERROR: List is empty.");
		if (current == tail->previous)
			throw runtime_error("ERROR: No current element.");
		E res = current->next->element;
		current->next = current->next->next;
		delete current->next->previous;
		current->next->previous = current;
		size--;
		return res;
	}
	void clear() {
		current = head->next;
		DNode<E>* temp;
		while (current != tail) {
			temp = current;
			current = current->next;
			delete temp;
		}
		head->next = tail;
		current = tail->previous = head;
		size = 0;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail->previous;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("ERROR: Position out of bounds.");
		if (pos < size / 2) {
			current = head;
			for (int i = 0; i < pos; i++)
				current = current->next;
		}
		else {
			current = tail->previous;
			for (int i = size; i > pos; i--)
				current = current->previous;
		}
	}
	void next() {
		if (current != tail->previous)
			current = current->next;
	}
	void previous() {
		if (current != head)
			current = current->previous;
	}
	bool atStart() {
		return curernt == head;
	}
	bool atEnd() {
		return current == tail->previous;
	}
	int getPos() {
		int pos = 0;
		DNode<E>* temp = head;
		while (temp != current) {
			pos++;
			temp = temp->next;
		}
		return pos;
	}
	int getSize() {
		return size;
	}
	void print() {
		DNode<E>* temp = head->next;
		cout << "[ ";
		while (temp != tail) {
			cout << temp->element;
			if (temp == tail->previous)
				cout << " ";
			else:
			cout << ", ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};
