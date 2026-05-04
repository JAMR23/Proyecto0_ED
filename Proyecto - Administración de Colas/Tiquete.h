//autor: Indigo Sánchez
//fecha: 2026-05-04
//descripción: 

#pragma once
#include <string>
#include <ctime>

using std::string;

class Tiquete {
public:
	string codigo;			//ej: C1
	int prioridad;			//PT = PU * 10 + PS	
	time_t horaSolicitud;	//solicita tiquete
	time_t horaAtencion;	//tiquete atendido

	Tiquete(string codigo, int prioridad) {
		this->codigo = codigo;
		this->prioridad = prioridad;
		this->horaSolicitud = time(nullptr);
		this->horaAtencion = 0;
	}
	//sin el operador definido no compila
	bool operator<(const Tiquete& other) {
		return this->prioridad < other.prioridad;	//con menor numero, mayor prioridad
	}

	double tiempoEspera() {
		return difftime(horaAtencion, horaSolicitud); //retorna los segundos de espera
	}

	//imprime con formato el tiquete
	friend ostream& operator<<(ostream& os, const Tiquete& t) {
		os << "Código: " << t.codigo
			<< "-- Prioridad: " << t.prioridad
			<< "-- Hora: " << ctime(&t.horaSolicitud);
		return os;
	}

};

