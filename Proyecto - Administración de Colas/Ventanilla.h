// Autor: Indigo Sánchez
// Fecha: 2026-05-04
// Descripción: Representa la ventanilla de atención dentro de un área que atiende tiquetes. Guarda el tiquete actual y los atendidos.

#pragma once

#include <String>
#include "Tiquete.h"

using std::string;

class Ventanilla {
private:
	string nombre;			//Código: area y consecutivo
	Tiquete* tiqueteActual;	//Tiquete que se está atendiendo, null si ninguno
	int tiquetesAtendidos;	//Contador de los tiquetes atendidos

public:

	Ventanilla(string nombre) {
		this->nombre = nombre;
		this->tiqueteActual = nullptr;
		this->tiquetesAtendidos = 0;
	}
	//Asigna el tiquete que se está atendiendo a esta ventanilla
	void atenderTiquete(Tiquete* tiquete) {
		this->tiqueteActual = tiquete;
		tiquetesAtendidos++;
	}

	//Termina la atención del tiquete actual
	void liberaVentanilla() {
		tiqueteActual = nullptr;
	}
	
	//Nombre de la ventanilla
	string getNombre() {
		return nombre;
	}

	Tiquete* getTiqueteActual() {
		return tiqueteActual;
	}

	int getTiquetesAtendidos() {
		return tiquetesAtendidos;
	}

};

