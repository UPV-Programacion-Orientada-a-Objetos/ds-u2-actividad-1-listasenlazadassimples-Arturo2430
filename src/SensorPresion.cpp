//
// Created by automated edit
//

#include "SensorPresion.h"
#include <iostream>

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

void SensorPresion::imprimirInfo() const {
    std::cout << "Sensor Presion: " << getNombre() << "\n";
}