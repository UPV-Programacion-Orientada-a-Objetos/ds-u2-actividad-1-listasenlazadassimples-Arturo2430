/**
 * @file ListaGeneral.cpp
 * @brief Implementación de la lista de gestión polimórfica
 * @author Arturo
 * @date 30/10/2025
 */

#include "ListaGeneral.h"
#include "SensorBase.h"
#include <iostream>

/**
 * @brief Destructor de ListaGeneral
 * 
 * Libera toda la memoria en cascada:
 * 1. Libera cada sensor (destrucción polimórfica)
 * 2. Libera cada nodo de la lista
 * 
 * Muestra logs detallados del proceso de liberación.
 */
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

/**
 * @brief Inserta un sensor al final de la lista
 * @param sensor Puntero al sensor (la lista toma ownership)
 * 
 * Crea un nuevo nodo y lo añade al final de la lista.
 * Muestra un log de la operación.
 */
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

/**
 * @brief Procesa todos los sensores de manera polimórfica
 * 
 * Itera sobre la lista y llama al método procesarLectura() de cada sensor.
 * Gracias al polimorfismo, cada sensor ejecuta su propia implementación:
 * - SensorTemperatura: elimina mínimo y calcula promedio
 * - SensorPresion: calcula promedio de todas las lecturas
 */
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