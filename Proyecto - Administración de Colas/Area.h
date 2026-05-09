// Autor: Indigo Sánchez, Jessica Vargas
// Fecha: 2026-05-04
// Descripción: Administra un área con ventanillas y una cola de prioridad de tiquetes.

#pragma once
#include <string>
#include "HeapPriorityQueue.h"
#include "Tiquete.h"
#include "Ventanilla.h"

using std::string;
using std::to_string;

class Area {
private:
	string codigo;				//Código único del área C, S o E
	string descripcion;			//nombre del área
	int cantidadVentanillas;	//Ventanillas en esta área
	Ventanilla** ventanillas;	//Array dinámico de punteros a ventanillas
	HeapPriorityQueue<Tiquete*> cola;	//cola de prioridad de tiquetes

public:
	//Crea el área y sus ventanillas
	Area(string codigo, string descripcion, int cantidadVentanillas) : cola(1024) {
		this->codigo = codigo;
		this->descripcion = descripcion;
		this->cantidadVentanillas = cantidadVentanillas;

		//Hace las ventanillas con código: el código de área y el consecutivo
		ventanillas = new Ventanilla* [cantidadVentanillas];
		for (int i = 0; i < cantidadVentanillas; i++) {
			string nombreVentanilla = codigo + to_string(i + 1);
			ventanillas[i] = new Ventanilla(nombreVentanilla);
		}
	}

	//Libera memoria de ventanillas
	~Area() {
		for (int i = 0; i < cantidadVentanillas; i++) 
			delete ventanillas[i];
		delete[] ventanillas;
	}

	//Agrega un tiquete a la cola de prioridad del área
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

	//Contador de tiquetes dispensados
	int tiquetesDispensados = 0;

};

