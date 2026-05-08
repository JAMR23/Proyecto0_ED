/*
* @file Interfaz.cpp
* @author Jose Marin
* @date 2026-05-08
* @brief Programa principal, muestra la interfaz del sistema e interactúa con el usuario.
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "Pair.h"
#include "HeapPriorityQueue.h"
#include "Servicio.h"
#include "Area.h"
#include "Ventanilla.h"
#include "Tiquete.h"
#include "LinkedList.h"

using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::string;
using std::getline;
using std::to_string;
using std::exception;
using std::runtime_error;


int main()
{
    cout << "Fuera de servivio...\n";
    return 0;
}

int main1() {
    //Inicializar y definir las listas y variables.
    LinkedList<Pair<int, string>>* usuarios = new LinkedList<Pair<int, string>>();
    LinkedList<Servicio>* servicios = new LinkedList<Servicio>();
    LinkedList<Area>* areas = new LinkedList<Area>();
    int consec = 100;
    bool c = true;
    while (c) {
        for (int i = 0; i < 50; ++i) {
            cout << endl;
        }
        cout << ".*:''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':*." << endl;
        cout << ": :    _____     __                      __                     : :" << endl;
        cout << ": :   / __(_)__ / /____ __ _  ___ _  ___/ /__                   : :" << endl;
        cout << ": :  _\\ \\/ (_-</ __/ -_)  ' \\/ _ `/ / _  / -_)                  : :" << endl;
        cout << ": : /___/_/___/\\__/\\__/_/_/_/\\_,_/  \\_,_/\\__/                   : :" << endl;
        cout << ": :    ___     __      _      _     __               _  __      : :" << endl;
        cout << ": :   / _ |___/ /_ _  (_)__  (_)__ / /________ _____(_)/_/ ___  : :" << endl;
        cout << ": :  / __ / _  /  ' \\/ / _ \\/ (_-</ __/ __/ _ `/ __/ / _ \\/ _ \\ : :" << endl;
        cout << ": : /_/ |_\\_,_/_/_/_/_/_//_/_/___/\\__/_/  \\_,_/\\__/_/\\___/_//_/ : :" << endl;
        cout << ": :      __      _____     __                                   : :" << endl;
        cout << ": :  ___/ /__   / ___/__  / /__ ____                            : :" << endl;
        cout << ": : / _  / -_) / /__/ _ \\/ / _ `(_-<                            : :" << endl;
        cout << ": : \\_,_/\\__/  \\___/\\___/_/\\_,_/___/                            : :" << endl;
        cout << ": :                                                             : :" << endl;
        cout << "'*:.............................................................:*'" << endl;
    }

    cout << "Menú Principal: " << endl
        << "1. Ver estado de las colas." << endl
        << "2. Generar tiquete." << endl
        << "3. Atender tiquete." << endl
        << "4. Administración." << endl
        << "5. Ver estadisticas del sistema." << endl
        << "6. Salir." << endl;
    string opt;
    getline(cin, opt);

    try {
        switch (stoi(opt)) {
        case 1:
                
            areas->goToStart();
            HeapPriorityQueue<Tiquete*>* q = areas->getElement().getCola();
            for (int i = 0; i < areas->getSize(); i++) {
                cout << "Area " << areas->getElement().getCodigo() << ": " << areas->getElement().getDescripcion() << endl;
                cout << "Cantidad de ventanillas: " << areas->getElement().getCantidadVentanillas() << endl;
                //Imprimir codigos de tiquetes presentes en cada cola
                q->print();
                //Las ventanillas muestran el numero del ultimo tiquete atendido
                for (int j = 0; j < areas->getElement().getCantidadVentanillas(); j++) {
                    Ventanilla* vent = areas->getElement().getVentanilla(j);
                    cout << "Ventanilla " << vent->getNombre() << ": " << endl
                        << "Ultimo tiquete: " << vent->getTiqueteActual() << endl;
                }
                areas->next();
            }
            cout << "Presione Enter para volver al menú principal...";
            cin.ignore(1000, '\n');
            cin.get();
            cin.ignore(1000, '\n');
            break;
        case 2:
            do {
                cout << "1. Seleccionar tipo de usuario y servicio." << endl
                    << "2. Regresar." << endl;
                getline(cin, opt);
                if (opt == "1") {
                    //Mostrar lista de tipos de usuario, selecciona uno
                    usuarios->goToStart();
                    cout << "Elija un tipo de usuario:" << endl;
                    for (int i = 0; i < usuarios->getSize(); i++) {
                        cout << i + 1 << ". " << usuarios->getElement().value;
                    }
                    getline(cin, opt);
                    usuarios->goToPos(stoi(opt) - 1);
                    int pu = usuarios->getElement().key;
                    //Mostrar lista de servicios (orden en el que se configuró) selecciona uno
                    servicios->goToStart();
                    cout << "Elija un servicio:" << endl;
                    for (int i = 0; i < servicios->getSize(); i++) {
                        cout << i + 1 << ". " << servicios->getElement().getDescripcion();
                    }
                    getline(cin, opt);
                    servicios->goToPos(stoi(opt) - 1);
                    int ps = servicios->getElement().agregar();
                    //Generar, agregar a la lista y mostrar datos del tiquete
                    Tiquete* t = new Tiquete(servicios->getElement().getCodArea() + to_string(consec), pu * 10 + ps);
                    consec++;
                    string cod = servicios->getElement().getCodArea();
                    areas->goToStart();
                    for (int i = 0; i < areas->getSize(); i++) {
                        if (areas->getElement().getCodigo() == cod)
                            areas->getElement().agregarTiquete(t);
                    }
                    cout << "Tiquete " << t << " agregado." << endl 
                        << "Presione enter para volver al menú principal...";
                    cin.ignore(1000, '\n');
                    cin.get();
                    cin.ignore(1000, '\n');
                }
                else if (opt == "2")
                    ; //no hace nada lol (para que no imprima error si es 2)
                else
                    cout << "ERROR: Opción no valida.";
            } while (opt != "2");
            break;
        case 3:
            //Solicita area y numero de ventanilla
            //if (lista de esa ventanilla->isEmpty())
            //cout << "No hay usuarios en espera.";
            //else, elimina el tiquete de esa cola y lo asigna como tiquete atendido en la ventanilla
            //actualizar datos necesarios para las estadisticas
            cout << "Tiquete atendido." << endl << "Presione enter para volver al menú principal...";
            cin.ignore(1000, '\n');
            cin.get();
            cin.ignore(1000, '\n');
            break;
        case 4:
            do {
                cout << "1. Tipos de usuario." << endl
                    << "2. Areas." << endl
                    << "3. Servicios disponibles." << endl
                    << "4. Limpiar colas y estadísticas." << endl
                    << "5. Regresar." << endl;
                getline(cin, opt);
                switch (stoi(opt)) {
                case 1:
                    do {
                        cout << "1. Agregar." << endl
                            << "2. Eliminar." << endl
                            << "3. Regresar." << endl;
                        getline(cin, opt);
                        if (opt == "1") {
                            ; //agregar tipo de usuario nuevo
                        }
                        else if (opt == "2") {
                            ; // eliminar un tipo de usuario y los tiquetes que lo tuvieran en cada cola de las areas
                        }
                        else if (opt == "3")
                            ;
                        else
                            cout << "ERROR: Opción no valida.";
                    } while (opt != "3");
                    break;
                case 2:
                    do {
                        cout << "1. Agregar." << endl
                            << "2. Modificar cantidad de ventanillas." << endl
                            << "3. Eliminar." << endl
                            << "4. Regresar." << endl;
                        getline(cin, opt);
                        if (opt == "1") {
                            ; //agregar area nueva
                        }
                        else if (opt == "2") {
                            ; //pedir al usuario un area, mostrar su cant de ventanillas y pedir un numero
                            //crear automaticamente la lista de ventanillas con sus codigos
                        }
                        else if (opt == "3")
                            ; // eliminar el area elimina tambien servicios y ventanillas con todos los tiquetes que tengan en cola
                            // debe solicitar confiramación mostrando la lista de servicios que se eliminarían.
                        else if (opt == "4")
                            ;
                        else
                            cout << "ERROR: Opción no valida.";
                    } while (opt != "4");
                    break;
                case 3:
                    do {
                        cout << "1. Agregar." << endl
                            << "2. Eliminar." << endl
                            << "3. Reordenar." << endl
                            << "4. Regresar." << endl;
                        getline(cin, opt);
                        if (opt == "1") {
                            ; //agregar servicio nuevo
                        }
                        else if (opt == "2") {
                            ; //mostrar servicios disponibles y pedir uno para eliminarlo
                            // PREGUNTAR AL PROFE   Eliminar TODOS los tiquetes??
                        }
                        else if (opt == "3")
                            ; //pedir numero de servicio y nueva posición donde se insertará en la lista.
                        else if (opt == "4")
                            ;
                        else
                            cout << "ERROR: Opción no valida.";
                    } while (opt != "4");
                    break;
                case 4:
                    // Clear todas las colas y reiniciar las estadisticas (no reinicia usuarios, servicios ni areas)
                    break;
                case 5:
                    break;
                default:
                    cout << "ERROR: Opción no valida.";
                }
            } while (opt != "5");
            break;
        case 5:
            //imprimir estadisticas del sistema (explicadas antes del menu)
            break;
        case 6:
            cout << "Cerrando el programa... ";
            c = false;
            cout << "Adios.";
            break;
        }
    }
    //Faltan catch especificos
    catch (const exception& e) {
        cout << "ERROR: " << e.what() << endl;
    }

    return 0;
};