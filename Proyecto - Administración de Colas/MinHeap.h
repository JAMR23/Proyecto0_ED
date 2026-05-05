#pragma once

#include <stdexcept>
#include <iostream>
#define DEFAULT_MAX 1024

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class MinHeap {
private:
    E* elements;
    int max;
    int size;

    int leftChild(int pos) {
        return 2 * pos + 1;
    }
    int rightChild(int pos) {
        return 2 * pos + 2;
    }
    int parent(int pos) {
        return (pos - 1) / 2;
    }
    void swap(int pos1, int pos2) {
        E temp = elements[pos1];
        elements[pos1] = elements[pos2];
        elements[pos2] = temp;
    }
    void siftUp(int pos) {
        while (pos > 0 and elements[pos] < elements[parent(pos)]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }
    bool isLeaf(int pos) {
        return leftChild(pos) >= size;
    }
    int minChild(int pos) {
        if (rightChild(pos) < size && elements[rightChild(pos)] < elements[leftChild(pos)])
            return rightChild(pos);
        return leftChild(pos);
    }
    void siftDown(int pos) {
        while (!isLeaf(pos) && elements[pos] >= elements[minChild(pos)]) {
            int mChild = minChild(pos);
            swap(pos, mChild);
            pos = mChild;
        }
    }

public:
    MinHeap(int max = 1024) {
        elements = new E[max];
        this->max = max;
        size = 0;
    }
    ~MinHeap() {
        delete[] elements;
    }
    void insert(E element) {
        if (size == max)
            throw runtime_error("ERROR: Heap is full.");
        elements[size] = element;
        siftUp(size);
        size++;
    }
    void first() {
        if (size == 0)
            throw runtime_error("ERROR: Heap is empty.");
        return elements[0];
    }

    E removeFirst() {
        return remove(0);
    }
    E remove(int pos) {
        if (size == 0)
            throw runtime_error("ERROR: Heap is empty.");
        if (pos < 0 || pos >= size)
            throw runtime_error("ERROR: Invalid index.");
        swap(pos, size - 1);
        size--;
        siftDown(pos);
        return elements[size];
    }
    void clear() {
        size = 0;
    }
    int getSize() {
        return size;
    }
    int isEmpty() {
        return size == 0;
    }
    void print() {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << elements[i];
            if (i != size - 1)
                cout << ", ";
        }
        cout << " ]" << endl;
    }
};