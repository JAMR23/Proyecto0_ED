// Autor: Mauricio Avilés, Jose Marín
// Fecha: 12/05/2026
// Descripcion: Cola de prioridad implementada sobre un MinHeap. Almacena cada elemento
//              junto a su prioridad en un Pair<int, E>. 

#pragma once
#include <iostream>
#include "PriorityQueue.h"
#include "Pair.h"
#include "MinHeap.h"


template <typename E>
class HeapPriorityQueue : public PriorityQueue<E> {
private:
	MinHeap<Pair<int, E>>* pairs;


public:
	HeapPriorityQueue(int max = 1024) {
		pairs = new MinHeap<Pair<int, E>>(max);
	}
	~HeapPriorityQueue() {
		delete pairs;
	}
	void insert(E element, int priority) {
		Pair<int, E> p(priority, element);
		pairs->insert(p);
	}
	E removeMin() {
		Pair<int, E> p = pairs->removeFirst();
		return p.value;
	}
	E min() {
		Pair<int, E> p = pairs->first();
		return p.value;
	}
	void clear() {
		pairs->clear();
	}
	bool isEmpty() {
		return pairs->isEmpty();
	}
	int getSize() {
		return pairs->getSize();
	}
	void print() {
		pairs->print();
	}
};
