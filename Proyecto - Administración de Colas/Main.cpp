/*
* @file Main.cpp
* @author Jose Marin
* @date 2026-05-12
* @brief Programa principal, muestra la interfaz del sistema e interactúa con el usuario.
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <clocale>
#include "Pair.h"
#include "HeapPriorityQueue.h"
#include "Usuario.h"
#include "Servicio.h"
#include "Area.h"
#include "Ventanilla.h"
#include "Tiquete.h"
#include "LinkedList.h"
#include <Windows.h>

using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::string;
using std::getline;
using std::to_string;
using std::exception;
using std::runtime_error;

int main() {
    setlocale(LC_ALL, "es_ES_UTF-8");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    //Inicializar y definir las listas y variables.
    LinkedList<Usuario*>* usuarios = new LinkedList<Usuario*>();
    LinkedList<Servicio*>* servicios = new LinkedList<Servicio*>();
    LinkedList<Area*>* areas = new LinkedList<Area*>();
    int consecutivo = 100;
    int tiempoTotalTiquetes = 0;
    int totalTiquetesAtendidos = 0;
    string x;
    bool c = true;
    while (c) {
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
                if (areas->getSize() == 0)
                    cout << "No hay areas definidas." << endl;
                else {
                    areas->goToStart();
                    for (int i = 0; i < areas->getSize(); i++) {
                        cout << "Area " << areas->getElement()->getCodigo() << ": " << areas->getElement()->getDescripcion() << endl;
                        cout << "Cantidad de ventanillas: " << areas->getElement()->getCantidadVentanillas() << endl;
                        //Imprimir codigos de tiquetes presentes en cada cola
                        areas->getElement()->getCola()->print();

                        //Las ventanillas muestran el numero del ultimo tiquete atendido
                        for (int j = 0; j < areas->getElement()->getCantidadVentanillas(); j++) {
                            Ventanilla* vent = areas->getElement()->getVentanilla(j);
                            cout << "Ventanilla " << vent->getNombre() << ": " << endl;
                            if (vent->getTiqueteActual() == nullptr)
                                cout << "No tiene un último tiquete registrado." << endl;
                            else
                                cout << "Ultimo tiquete: " << vent->getTiqueteActual()->codigo << endl;
                        }
                        areas->next();
                    }
                }
                cout << "Presione Enter para volver al menú principal...";
                cin.ignore(1000, '\n');
                for (int i = 0; i < 50; ++i) {
                    cout << endl;
                }
                break;
            case 2:
                if (usuarios->getSize() == 0 || servicios->getSize() == 0 || areas->getSize() == 0) {
                    cout << "No hay suficientes usuarios, servicios o areas definidos." << endl;
                    cout << "Presione Enter para volver al menú principal...";
                    cin.ignore(1000, '\n');
                    for (int i = 0; i < 50; ++i) {
                        cout << endl;
                    }
                }
                else {
                    do {
                        cout << "1. Seleccionar tipo de usuario y servicio." << endl
                            << "2. Regresar." << endl;
                        getline(cin, opt);
                        if (opt == "1") {
                            //Mostrar lista de tipos de usuario, selecciona uno
                            usuarios->goToStart();
                            cout << "Elija un tipo de usuario:" << endl;
                            for (int i = 0; i < usuarios->getSize(); i++) {
                                cout << i + 1 << ". " << usuarios->getElement()->getNombre() << endl;
                                usuarios->next();
                            }
                            getline(cin, x);
                            usuarios->goToPos(stoi(x) - 1);
                            int pu = usuarios->getElement()->emitirTiquete();
                            //Mostrar lista de servicios (orden en el que se configuró) selecciona uno
                            servicios->goToStart();
                            cout << "Elija un servicio:" << endl;
                            for (int i = 0; i < servicios->getSize(); i++) {
                                cout << i + 1 << ". " << servicios->getElement()->getDescripcion() << endl;
                                servicios->next();
                            }
                            getline(cin, x);
                            servicios->goToPos(stoi(x) - 1);
                            int ps = servicios->getElement()->agregar();
                            //Generar tiquete, agregarlo a la lista y mostrar sus datos.
                            Tiquete* t = new Tiquete(servicios->getElement()->getCodArea() + to_string(consecutivo), pu * 10 + ps);
                            consecutivo++;
                            string cod = servicios->getElement()->getCodArea();
                            areas->goToStart();
                            for (int i = 0; i < areas->getSize(); i++) {
                                if (areas->getElement()->getCodigo() == cod)
                                    areas->getElement()->agregarTiquete(t);
                            }
                            cout << "Tiquete " << t->codigo << " agregado." << endl;
                           
                        }
                        else if (opt == "2")
                            for (int i = 0; i < 50; ++i) {
                                cout << endl;
                            }
                        else
                            cout << "ERROR: Opción no valida.";
                    } while (opt != "2");
                }
                break;
            case 3:
                if (areas->getSize() == 0)
                    cout << "No hay areas definidas." << endl;
                else {
                    //Solicita area y numero de ventanilla
                    areas->goToStart();
                    cout << "Elija un area:" << endl;
                    for (int i = 0; i < areas->getSize(); i++) {
                        cout << i + 1 << ". " << areas->getElement()->getDescripcion() << endl;
                        areas->next();
                    }
                    getline(cin, x);
                    areas->goToPos(stoi(x) - 1);
                    //Revisar si la cola del area está vacía
                    if (areas->getElement()->colaVacia())
                        cout << "No hay ususarios en espera.";
                    //ventanilla
                    else {
                        cout << "Elija una ventanilla:" << endl;
                        for (int i = 0; i < areas->getElement()->getCantidadVentanillas(); i++) {
                            cout << i + 1 << ". " << areas->getElement()->getVentanilla(i)->getNombre() << endl;
                        }
                        getline(cin, x);
                        //elimina el tiquete de esa cola y lo asigna como tiquete atendido en la ventanilla
                        Tiquete* t = areas->getElement()->extraerTiquete();
                        areas->getElement()->getVentanilla(stoi(x) - 1)->atenderTiquete(t);
                        //actualizar datos necesarios para las estadisticas
                        t->horaAtencion = time(nullptr);
                        tiempoTotalTiquetes += t->tiempoEspera();
                        totalTiquetesAtendidos++;
                    }
                    cout << "Tiquete atendido." << endl;
                }
                cout << "Presione Enter para volver al menú principal...";
                cin.ignore(1000, '\n');
                for (int i = 0; i < 50; ++i) {
                    cout << endl;
                }
                break;
            case 4:
                do {
                    cout << "ADMINISTRACIÓN" << endl
                        << "1. Tipos de usuario." << endl
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
                                //agregar tipo de usuario nuevo
                                string nombre;
                                string prioridad;
                                cout << "Escriba el nombre del tipo de usuario: ";
                                getline(cin, nombre);
                                cout << "Escriba la prioridad: ";
                                getline(cin, prioridad);
                                Usuario* u = new Usuario(stoi(prioridad), nombre);
                                usuarios->goToStart();
                                if (usuarios->getSize() == 0) {
                                    usuarios->append(u);
                                }
                                else {
                                    bool insert = false;
                                    for (int i = 0; i < usuarios->getSize(); ++i) {
                                        if (u->getPrioridad() < usuarios->getElement()->getPrioridad()) {
                                            usuarios->insert(u);
                                            insert = true;
                                            break;
                                        }
                                        usuarios->next();
                                    }
                                    if (!insert) {
                                        usuarios->append(u);
                                    }
                                }
                                cout << "Usuario añadido." << endl << endl;
                            }
                            else if (opt == "2") {
                                if (usuarios->getSize() == 0)
                                    cout << "No hay ningún tipo de usuario definido." << endl << endl;
                                else {
                                    // eliminar un tipo de usuario y los tiquetes que lo tuvieran en cada cola de las areas
                                    usuarios->goToStart();
                                    cout << "Elija un tipo de usuario:" << endl;
                                    for (int i = 0; i < usuarios->getSize(); i++) {
                                        cout << i + 1 << ". " << usuarios->getElement()->getNombre() << endl;
                                        usuarios->next();
                                    }
                                    getline(cin, x);
                                    usuarios->goToPos(stoi(x) - 1);
                                    cout << "Usuario " << usuarios->remove()->getNombre()
                                        << " eliminado." << endl << endl;
                                }
                            }
                            else if (opt == "3")
                                cout << endl;
                            else
                                cout << "ERROR: Opción no valida." << endl;
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
                                string codigo;
                                string nombre;
                                string cVent;
                                cout << "Escriba el nombre: ";
                                getline(cin, nombre);
                                cout << "Escriba el codigo: ";
                                getline(cin, codigo);
                                cout << "Escriba la cantidad de ventanas: ";
                                getline(cin, cVent);
                                Area* a = new Area(codigo, nombre, stoi(cVent));
                                areas->append(a);
                                cout << "Area añadida." << endl << endl;

                            }
                            else if (opt == "2") {
                                if (areas->getSize() == 0)
                                    cout << "No hay areas definidas." << endl;
                                else {
                                    //pedir al usuario un area, mostrar su cant de ventanillas y pedir un numero
                                    areas->goToStart();
                                    cout << "Elija un area:" << endl;
                                    for (int i = 0; i < areas->getSize(); i++) {
                                        cout << i + 1 << ". " << areas->getElement()->getDescripcion() << endl;
                                        areas->next();
                                    }
                                    getline(cin, x);
                                    areas->goToPos(stoi(x) - 1);
                                    cout << "El area tiene " << areas->getElement()->getCantidadVentanillas() << " ventanillas." << endl;
                                    cout << "Escriba la nueva cantidad: ";
                                    getline(cin, x);
                                    //crear automaticamente la lista (array) de ventanillas con sus codigos
                                    Ventanilla** v = new Ventanilla * [stoi(x)];
                                    for (int i = 0; i < stoi(x); i++) {
                                        if (i < areas->getElement()->getCantidadVentanillas()) {
                                            v[i] = areas->getElement()->getVentanilla(i);
                                        }
                                    }
                                    //Borrar la lista de ventanillas del area, asignarle v y asignnar x a la cantVentanillas
                                    areas->getElement()->delVentanillas();
                                    areas->getElement()->asignVentanillas(v, stoi(x));
                                    cout << "Ventanillas modificadas." << endl << endl;
                                }
                                
                            }
                            else if (opt == "3") {
                                if (areas->getSize() == 0)
                                    cout << "No hay ningún area definida." << endl << endl;
                                else {
                                    // Elejir area a eliminar
                                    areas->goToStart();
                                    cout << "Elija un area:" << endl;
                                    for (int i = 0; i < areas->getSize(); i++) {
                                        cout << i + 1 << ". " << areas->getElement()->getDescripcion() << endl;
                                        areas->next();
                                    }
                                    getline(cin, x);
                                    areas->goToPos(stoi(x) - 1);
                                    // Solicitar confirmacion mostrando la lista de servicios que se eliminarán
                                    servicios->goToStart();
                                    cout << "¡ADVERTENCIA! Se eliminarán también los servicios de esta area: " << endl;
                                    for (int i = 0; i < servicios->getSize(); i++) {
                                        if (servicios->getElement()->getCodArea() == areas->getElement()->getCodigo()) {
                                            cout << servicios->getElement()->getDescripcion() << endl;
                                        }
                                    }
                                    cout << "Desea continuar?(s/n): ";
                                    getline(cin, x);
                                    // Si escribe s, eliminar todos los servicios y el area con su cola y ventanillas, si no, cancela.
                                    if (x == "s") {
                                        if (servicios->getSize() > 0) {
                                            servicios->goToStart();
                                            for (int i = 0; i < servicios->getSize(); i++) {
                                                if (servicios->getElement()->getCodArea() == areas->getElement()->getCodigo()) {
                                                    servicios->remove();
                                                }
                                            }
                                            cout << "Area " << areas->remove()->getDescripcion() << " eliminada." << endl << endl;
                                        }
                                        else {
                                            cout << "Area " << areas->remove()->getDescripcion() << " eliminada." << endl << endl;
                                        }
                                    }
                                    else
                                        cout << "Cancelando..." << endl << endl;
                                }
                                
                            }
                            else if (opt == "4")
                                cout << endl;
                            else
                                cout << "ERROR: Opción no valida." << endl;
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
                                //agregar servicio nuevo
                                if (areas->getSize() == 0)
                                    cout << "Debe haber al menos un area definida para asignar el servicio." << endl;
                                else {
                                    string codArea;
                                    string nombre;
                                    string prioridad;
                                    cout << "Escriba el nombre: ";
                                    getline(cin, nombre);
                                    cout << "Escriba la prioridad: ";
                                    getline(cin, prioridad);

                                    cout << "Areas disponibles:" << endl;
                                    areas->goToStart();
                                    for (int i = 0; i < areas->getSize(); i++)
                                        cout << "Codigo " << areas->getElement()->getCodigo() << ": " << areas->getElement()->getDescripcion() << endl;
                                    cout << "Escriba el codigo de area: ";
                                    getline(cin, codArea);

                                    Servicio* s = new Servicio(nombre, stoi(prioridad), codArea);
                                    servicios->append(s);
                                    cout << "Servicio añadido." << endl << endl;
                                }
                            }
                            else if (opt == "2") {
                                if (servicios->getSize() == 0)
                                    cout << "No hay ningún servicio definido." << endl << endl;
                                else {
                                    //mostrar servicios disponibles y pedir uno para eliminarlo
                                    servicios->goToStart();
                                    cout << "Elija un servicio a eliminar:" << endl;
                                    for (int i = 0; i < servicios->getSize(); i++) {
                                        cout << i + 1 << ". " << servicios->getElement()->getDescripcion();
                                        servicios->next();
                                    }
                                    getline(cin, x);
                                    servicios->goToPos(stoi(x) - 1);
                                    //eliminar tiquetes del area correspondiente al servicio
                                    for (int i = 0; i < areas->getSize(); i++) {
                                        if (areas->getElement()->getCodigo() == servicios->getElement()->getCodArea())
                                            areas->getElement()->limpiarCola();
                                    }
                                    cout << "Servicio " << servicios->remove()->getDescripcion() << " y tiquetes de su area, eliminados." << endl << endl;
                                }
                            }
                            else if (opt == "3") {
                                if (servicios->getSize() == 0)
                                    cout << "No hay ningún servicio definido." << endl << endl;
                                else {
                                    //pedir numero de servicio y nueva posición donde se insertará en la lista.
                                    servicios->goToStart();
                                    cout << "Elija un servicio a mover:" << endl;
                                    for (int i = 0; i < servicios->getSize(); i++) {
                                        cout << i + 1 << ". " << servicios->getElement()->getDescripcion();
                                        servicios->next();
                                    }
                                    getline(cin, x);
                                    servicios->goToPos(stoi(x) - 1);
                                    Servicio* temp = servicios->remove();
                                    cout << "Escriba la nueva posición del servicio en la lista (siendo 1 la primera posicion): ";
                                    getline(cin, x);
                                    servicios->goToPos(stoi(x) - 1);
                                    servicios->insert(temp);
                                    cout << "Orden de servicios actualizado." << endl << endl;
                                }
                            }
                            else if (opt == "4")
                                cout << endl;
                            else
                                cout << "ERROR: Opción no valida." << endl;
                        } while (opt != "4");
                        break;
                    case 4:
                        // Clear todas las colas y reiniciar las estadisticas (no reinicia usuarios, servicios ni areas)
                        consecutivo = 100;
                        totalTiquetesAtendidos = 0;
                        tiempoTotalTiquetes = 0;
                        areas->goToStart();
                        for (int i = 0; i < areas->getSize(); i++) {
                            areas->getElement()->limpiarCola();
                            areas->getElement()->reiniciarTiquetes();
                            for (int j = 0; j < areas->getElement()->getCantidadVentanillas(); j++) {
                                areas->getElement()->getVentanilla(j)->liberaVentanilla();
                            }
                        }
                        servicios->goToStart();
                        for (int i = 0; i < servicios->getSize(); i++) {
                            servicios->getElement()->reiniciarTiquetes();
                        }
                        usuarios->goToStart();
                        for (int i = 0; i < usuarios->getSize(); i++) {
                            usuarios->getElement()->reiniciarTiquetes();
                        }
                        cout << "Estadisticas del sistema reiniciadas." << endl << endl;
                        break;
                    case 5:
                        for (int i = 0; i < 50; ++i) {
                            cout << endl;
                        }
                        break;
                    default:
                        cout << "ERROR: Opción no valida." << endl;
                        break;
                    }
                } while (opt != "5");
                break;
            case 5:
                //imprimir estadisticas del sistema
                if (totalTiquetesAtendidos == 0)
                    cout << "No se ha atendido ningun tiquete." << endl;
                else {
                    cout << "Estadisticas del sistema:" << endl
                        << "Tiempo promedio de espera: " << tiempoTotalTiquetes / totalTiquetesAtendidos << " segundos." << endl;

                    if (areas->getSize() == 0)
                        cout << "No hay areas definidas." << endl;
                    else {
                        cout << "Tiquetes dispensados por area: " << endl;
                        areas->goToStart();
                        for (int i = 0; i < areas->getSize(); i++) {
                            cout << areas->getElement()->getDescripcion() << ": "
                                << areas->getElement()->getTiquetesDisp() << " tiquetes. " << endl;
                            areas->next();
                        }

                        cout << "Tiquetes atendidos por ventanilla: " << endl;
                        areas->goToStart();
                        for (int i = 0; i < areas->getSize(); i++) {
                            for (int j = 0; j < areas->getElement()->getCantidadVentanillas(); j++) {
                                cout << areas->getElement()->getVentanilla(j)->getNombre() << ": "
                                    << areas->getElement()->getVentanilla(j)->getTiquetesAtendidos() << " tiquetes. " << endl;
                            }
                            areas->next();
                        }
                    }
                    if (servicios->getSize() == 0)
                        cout << "No hay servicios definidas." << endl;
                    else {
                        servicios->goToStart();
                        cout << "Tiquetes solicitados por servicio: " << endl;
                        for (int i = 0; i < servicios->getSize(); i++) {
                            cout << servicios->getElement()->getDescripcion() << ": "
                                << servicios->getElement()->getTiquetesSol() << " tiquetes. " << endl;
                            servicios->next();
                        }
                    }
                    if (usuarios->getSize() == 0)
                        cout << "No hay servicios definidas." << endl;
                    else {
                        usuarios->goToStart();
                        cout << "Tiquetes emitidos por usuario: " << endl;
                        for (int i = 0; i < usuarios->getSize(); i++) {
                            cout << usuarios->getElement()->getNombre() << ": "
                                << usuarios->getElement()->getTiquetesEmitidos() << " tiquetes. " << endl;
                            usuarios->next();
                        }
                    }
                }
                cout << "Presione Enter para volver al menú principal...";
                cin.ignore(1000, '\n');
                for (int i = 0; i < 50; ++i) {
                    cout << endl;
                }
                break;
            case 6:
                cout << "Cerrando el programa... ";
                c = false;
                cout << "Adios.";
                break;
            default:
                for (int i = 0; i < 50; ++i) {
                    cout << endl;
                }
                cout << "ERROR: Opción no valida." << endl << endl;
                break;
            }
        }
        //Faltan catch especificos
        catch (const std::invalid_argument) {
            for (int i = 0; i < 50; ++i) {
                cout << endl;
            }
            cout << "ERROR: Opción no valida." << endl << endl;
        }
        catch (const exception& e) {
            for (int i = 0; i < 50; ++i) {
                cout << endl;
            }
            cout << e.what() << endl << endl;
        }
    }
    return 0;
};