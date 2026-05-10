//descripcion
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
    int prioridad; // 
    string codArea;
    int tiquetesSolicitados; //agregado
    //Eliminado atributo contador, no se usaba

public:
    //Constructor
    Servicio(string descripcion, int prioridad, string codArea) {
        this->descripcion = descripcion;
        this->codArea = codArea;
        this->prioridad = prioridad;
        tiquetesSolicitados = 0;

    }
    ~Servicio() {};
    // getters
    //se maneja diferente
    string getDescripcion() const {
        return descripcion;
    }
    int agregar() {
        tiquetesSolicitados++;
        return prioridad;
    }
    string getCodArea() {
        return codArea;
    }
    void reiniciarTiquetes() {
        tiquetesSolicitados = 0;            //agregado
    }
    int getTiquetesSol() {
        return tiquetesSolicitados;         //agregado
    }
    // Para imprimir
    friend ostream& operator<<(ostream& os, const Servicio& s) {
        os << s.descripcion
            << " Prioridad: " << s.prioridad
            << " Area: " << s.codArea;
        return os;
    }
};