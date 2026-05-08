//autor: Indigo Sánchez
//fecha: 2026-05-04
//descripción: 

#pragma once
#include <string>
#include "HeapPriorityQueue.h"
#include "Tiquete.h"
#include "Ventanilla.h"

using std::string;
using std::to_string;

class Area {
private:
	string codigo;			//el área C, S o E
	string descripcion;		//nombre del área
	int cantidadVentanillas;
	Ventanilla** ventanillas;	//array de punteros a ventanillas
	HeapPriorityQueue<Tiquete*> cola;	//cola de prioridad de tiquetes

public:
	Area(string codigo, string descripcion, int cantidadVentanillas) : cola(1024) {
		this->codigo = codigo;
		this->descripcion = descripcion;
		this->cantidadVentanillas = cantidadVentanillas;

		//Hace las ventanillas con código: el área y el consecutivo
		ventanillas = new Ventanilla* [cantidadVentanillas];
		for (int i = 0; i < cantidadVentanillas; i++) {
			string nombreVentanilla = codigo + to_string(i + 1);
			ventanillas[i] = new Ventanilla(nombreVentanilla);
		}
	}

	~Area() {
		for (int i = 0; i < cantidadVentanillas; i++) 
			delete ventanillas[i];
		delete[] ventanillas;
	}

	//Agrega el tiquete a la cola de prioridad del área
	void agregarTiquete(Tiquete* tiquete) {
		cola.insert(tiquete, tiquete->prioridad);		//Modificada para que solo necesite tiquete como parametro
	}

	//Extrae el tiquete con mayor prioridad (menor número)
	Tiquete* extraerTiquete() {
		return cola.removeMin();
	}

	//Revisa si la cola está vacía
	bool colaVacia() {
		return cola.isEmpty();
	}

	//Getters
	string getCodigo() {
		return codigo;
	}

	string getDescripcion() {
		return descripcion;
	}

	int getCantidadVentanillas() {
		return cantidadVentanillas;
	}

	Ventanilla* getVentanilla(int i) {
		return ventanillas[i];
	}

	int getCanTiquetes() {		//agregado
		return cola.getSize();
	}
	HeapPriorityQueue<Tiquete*>* getCola() {		//agregado
		return &cola;
	}

	int tiquetesDispensados = 0;

};

