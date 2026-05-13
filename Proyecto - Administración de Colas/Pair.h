// Autor: Mauricio Avilés
// Fecha: 12/05/2026
// Descripcion: Estructura generica que agrupa un par (key, value) de tipos distintos.
//				Agrupa un elemento y su prioridad en una sola unidad.


#pragma once

#include <iostream>

using std::ostream;

template <typename K, typename V>
class Pair {
public:
	K key;
	V value;

	Pair() {}
	Pair(K key) {
		this->key = key;
	}
	Pair(K key, V value) {
		this->key = key;
		this->value = value;
	}
	bool operator==(const Pair<K, V>& other) {
		return key == other.key;
	}
	bool operator!=(const Pair<K, V>& other) {
		return key != other.key;
	}
	bool operator<(const Pair<K, V>& other) {
		return key < other.key;
	}
	bool operator<=(const Pair<K, V>& other) {
		return key <= other.key;
	}
	bool operator>(const Pair<K, V>& other) {
		return key > other.key;
	}
	bool operator>=(const Pair<K, V>& other) {
		return key >= other.key;
	}
	friend ostream& operator <<(ostream& os, const Pair<K, V>& p) { 
		os << "(" << p.key << ", " << p.value << ")";
		return os;
	}
};
