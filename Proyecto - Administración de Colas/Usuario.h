// Autor: Jose Marin
// Fecha: 2026-05-12
// Descripción: Define la estructura de cada tipo de usuario creado.
#pragma once

#include <string>

using std::string;

class Usuario {
private:
	string nombre;			//Nombre del tipo de usuario
	int prioridad;			//Prioridad del usuario en la cola
	int tiquetesEmitidos;	//Tiquetes que han solicitado usuarios de ese tipo

public:
	//Constructor
	Usuario(int prioridad, string nombre) {
		this->prioridad = prioridad;
		this->nombre = nombre;
		tiquetesEmitidos = 0;
	}
	~Usuario() {}

	//Reinicia la estadistica de tiqeutes
	void reiniciarTiquetes() {
		tiquetesEmitidos = 0;
	}
	//Aumenta el contador de tiquetes emitidos y devielvee la prioridad del tipo para colocarlo en la cola
	int emitirTiquete() {
		tiquetesEmitidos++;
		return getPrioridad();
	}

	//Getters
	string getNombre() {
		return nombre;
	}
	int getPrioridad() {
		return prioridad;
	}
	int getTiquetesEmitidos() {
		return tiquetesEmitidos;
	}
};

