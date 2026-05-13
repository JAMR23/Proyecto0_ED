// Autor: Indigo Sánchez, Jessica Vargas, Jose Marin
// Fecha: 2026-05-04
// Descripción: Administra un área con ventanillas 
//				y una cola de prioridad de tiquetes.

#pragma once
#include <string>
#include "HeapPriorityQueue.h"
#include "Tiquete.h"
#include "Ventanilla.h"

using std::string;
using std::to_string;

class Area {
private:
	string codigo;						//Código único del área por ejemplo C, S o E
	string descripcion;					//Nombre del área
	int cantidadVentanillas;			//Ventanillas en esta área
	int tiquetesDispensados;			//Contador de tiquetes dispensados
	Ventanilla** ventanillas;			//Array dinámico de punteros a ventanillas
	HeapPriorityQueue<Tiquete*> cola;	//Cola de prioridad de tiquetes

public:
	//Crea el área y sus ventanillas
	Area(string codigo, string descripcion, int cantidadVentanillas) : cola(1024) {
		this->codigo = codigo;
		this->descripcion = descripcion;
		this->cantidadVentanillas = cantidadVentanillas;
		this->tiquetesDispensados = 0;

		//Hace las ventanillas con código: el código de área y el consecutivo
		ventanillas = new Ventanilla* [cantidadVentanillas];
		for (int i = 0; i < cantidadVentanillas; i++) {
			string nombreVentanilla = codigo + to_string(i + 1);
			ventanillas[i] = new Ventanilla(nombreVentanilla);
		}
	}

	//Libera memoria de ventanillas y la cola
	~Area() {
		delVentanillas();
		while (!colaVacia()) {
			Tiquete* t = cola.removeMin();
			delete t;
		}
	}

	//Agrega un tiquete a la cola de prioridad del área
	void agregarTiquete(Tiquete* tiquete) {
		cola.insert(tiquete, tiquete->prioridad);
	}

	//Extrae el tiquete con mayor prioridad (menor número)
	Tiquete* extraerTiquete() {
		Tiquete* t = cola.removeMin();
		tiquetesDispensados++;
		return t;
	}

	//Revisa si la cola está vacía
	bool colaVacia() {
		return cola.isEmpty();
	}

	//Libera memoria de ventanillas
	void delVentanillas() {
		for (int i = 0; i < cantidadVentanillas; i++)
			delete ventanillas[i];
		delete[] ventanillas;						
		cantidadVentanillas = 0;
	}
	//Asigna un nuevo arreglo de ventanillas
	void asignVentanillas(Ventanilla** v, int cVent) {
		ventanillas = v;
		cantidadVentanillas = cVent;				
	}
	//Limpia la cola
	void limpiarCola() {
		cola.clear();								
	}
	//Reinicia los tiquetes dispensados
	void reiniciarTiquetes() {
		tiquetesDispensados = 0;
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

	int getCanTiquetes() {							
		return cola.getSize();
	}
	HeapPriorityQueue<Tiquete*>* getCola() {		
		return &cola;
	}
	int getTiquetesDisp() {
		return tiquetesDispensados;					
	}
};

