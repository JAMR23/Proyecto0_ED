// Autor: Indigo Sánchez
// Fecha: 2026-05-04
// Descripción: Representa el tiquete generado para un cliente cuando 
//				solicitan un servicio, con prioridad, hora de solicitud y atención.

#pragma once
#include <string>
#include <ctime>

using std::string;

class Tiquete {
public:
	string codigo;			//ej: C100
	int prioridad;			//PT = PU * 10 + PS	
	time_t horaSolicitud;	//solicita tiquete
	time_t horaAtencion;	//tiquete atendido

	//Guarda la hora actual, 0 = no atendido
	Tiquete(string codigo, int prioridad) {
		this->codigo = codigo;
		this->prioridad = prioridad;
		this->horaSolicitud = time(nullptr);
		this->horaAtencion = 0;
	}
	// Necesario para ordenar en la cola de prioridad, orden ascendente
	bool operator<(const Tiquete& other) {
		return this->prioridad < other.prioridad;	//con menor numero, mayor prioridad
	}

	// Calcula el timepo de espera del cliente
	double tiempoEspera() {
		return difftime(horaAtencion, horaSolicitud); //retorna los segundos de espera
	}

	//Usa el operador << para imprimir el tiquete
	friend ostream& operator<<(ostream& os, const Tiquete& t) {
		char buffer[26];
		ctime_s(buffer, sizeof(buffer), &t.horaSolicitud);
		buffer[strcspn(buffer, "\n")] = 0;
		os << "( Código: " << t.codigo
			<< " -- Prioridad: " << t.prioridad
			<< " -- Hora: " << buffer << " )";
		return os;
	}

};

