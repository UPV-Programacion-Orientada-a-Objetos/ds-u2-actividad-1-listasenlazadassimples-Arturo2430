/**
 * @file SensorPresion.cpp
 * @brief Implementación del sensor de presión atmosférica
 * @author Arturo
 * @date 30/10/2025
 */

#include "SensorPresion.h"
#include <iostream>

/**
 * @brief Procesa las lecturas de presión calculando el promedio
 * 
 * Recorre todas las lecturas almacenadas y calcula su promedio aritmético.
 * Muestra logs de liberación de memoria para cada nodo procesado.
 */
void SensorPresion::procesarLectura() {
    Nodo<int>* it = historial.head();
    if (!it) {
        std::cout << "[Sensor Presion] No hay lecturas para procesar.\n";
        return;
    }

    long sum = 0;
    int count = 0;
    while (it) {
        std::cout << "    [Log] Nodo<int> " << it->dato << " liberado.\n";
        sum += it->dato;
        ++count;
        it = it->siguiente;
    }

    double avg = static_cast<double>(sum) / count;
    std::cout << "[Sensor Presion] Promedio calculado sobre " << count << " lectura" 
              << (count == 1 ? "" : "s") << " (" << avg << ").\n";
    
    // Log de destrucción
    std::cout << "  [Destructor Sensor " << getNombre() << "] Liberando Lista Interna...\n";
}

/**
 * @brief Imprime información del sensor de presión
 * 
 * Muestra el nombre y tipo del sensor en formato legible.
 */
void SensorPresion::imprimirInfo() const {
    std::cout << "Sensor Presion: " << getNombre() << "\n";
}