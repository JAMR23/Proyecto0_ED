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
    int contador; // 

public:
    //Constructor
    Servicio(string descripcion, int prioridad, string codArea) {
        this->descripcion = descripcion;
        this->codArea = codArea;
        this->prioridad = prioridad;
     
    }
    ~Servicio() {};
    // getters
    //se maneja diferente
    string getDescripcion() const { 
        return descripcion; 
    }
    int agregar() { 
        return prioridad; 
    }
    string getCodArea() {
        return codArea;
    }
    // Para imprimir
    friend ostream& operator<<(ostream& os, const Servicio& s) {
        os << s.descripcion
            << " Prioridad: " << s.prioridad
            << " Area: " << s.codArea;
        return os;
    }
};