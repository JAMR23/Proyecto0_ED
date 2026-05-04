//autor: Indigo Sánchez
//fecha: 2026-05-04
//descripción: 

#pragma once

#include <String>
#include "Tiquete.h"

using std::string;

class Ventanilla {
private:
	string nombre;			//Código: area y consecutivo
	Tiquete* tiqueteActual;	//Tiquete que se está atendiendo, null si ninguno
	int tiquetesAtendidos;

public:
	Ventanilla(string nombre) {
		this->nombre = nombre;
		this->tiqueteActual = nullptr;
		this->tiquetesAtendidos = 0;
	}
	//Asigna el tiquete que se está atendiendo
	void atenderTiquete(Tiquete* tiquete) {
		this->tiqueteActual = tiquete;
		tiquetesAtendidos++;
	}

	void liberaVentanilla() {
		tiqueteActual = nullptr;
	}

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

