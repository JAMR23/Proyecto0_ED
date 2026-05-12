// Autor: Jessica Vargas
// Fecha: 07/05/2026
// Descripcion: Un servicio disponible en el sistema de administracion de colas. 
 
#pragma once

#include <stdexcept>
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;
using std::ostream;
using std::runtime_error;

class Servicio {
private:
    string descripcion;
    int prioridad;
    string codArea;
    int tiquetesSolicitados; 

public:
    // Constructor: inicializa el servicio con su descripción, prioridad y código de área.
    Servicio(string descripcion, int prioridad, string codArea) {
        this->descripcion = descripcion;
        this->codArea = codArea;
        this->prioridad = prioridad;
        tiquetesSolicitados = 0;

    }
    ~Servicio() {};
    // getters
    // Retorna la descripción del servicio
    string getDescripcion() const {
        return descripcion;
    }
    // Registra un nuevo tiquete solicitado para este servicio y retorna su prioridad.
    int agregar() {
        tiquetesSolicitados++;
        return prioridad;
    }
    // Retorna el código del área donde se atiende este servicio
    string getCodArea() {
        return codArea;
    }
    // Reinicia el contador de tiquetes solicitados 
    void reiniciarTiquetes() {
        tiquetesSolicitados = 0;
    }
    // Retorna la cantidad de tiquetes solicitados
    int getTiquetesSol() {
        return tiquetesSolicitados;
    }
    // Para imprimir
    friend ostream& operator<<(ostream& os, const Servicio& s) {
        os << s.descripcion
            << " Prioridad: " << s.prioridad
            << " Area: " << s.codArea;
        return os;
    }
};