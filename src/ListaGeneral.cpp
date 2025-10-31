//
// Created by automated edit
//

#include "ListaGeneral.h"
#include "SensorBase.h"
#include <iostream>

ListaGeneral::~ListaGeneral() {
    NodoGeneral* it = cabeza;
    std::cout << "\n--- Liberación de Memoria en Cascada ---\n";
    while (it) {
        NodoGeneral* sig = it->siguiente;
        if (it->sensor) {
            std::cout << "[Destructor General] Liberando Nodo: " << it->sensor->getNombre() << ".\n";
            delete it->sensor;
            it->sensor = nullptr;
        }
        delete it;
        it = sig;
    }
    cabeza = nullptr;
    std::cout << "Sistema cerrado. Memoria limpia.\n";
}

void ListaGeneral::insertar(SensorBase* sensor) {
    if (!sensor) return;
    NodoGeneral* nodo = new NodoGeneral(sensor);
    if (!cabeza) {
        cabeza = nodo;
        std::cout << "[Log] Insertando nodo para sensor: " << sensor->getNombre() << "\n";
        return;
    }
    NodoGeneral* it = cabeza;
    while (it->siguiente) it = it->siguiente;
    it->siguiente = nodo;
    std::cout << "[Log] Insertando nodo para sensor: " << sensor->getNombre() << "\n";
}

void ListaGeneral::procesarTodos() {
    NodoGeneral* it = cabeza;
    std::cout << "\nOpción 4: Ejecutar Procesamiento Polimórfico\n\n";
    std::cout << "--- Ejecutando Polimorfismo ---\n";
    while (it) {
        if (it->sensor) {
            std::cout << "-> Procesando Sensor " << it->sensor->getNombre() << "...\n";
            it->sensor->procesarLectura();
        }
        it = it->siguiente;
    }
    std::cout << "\n";
}