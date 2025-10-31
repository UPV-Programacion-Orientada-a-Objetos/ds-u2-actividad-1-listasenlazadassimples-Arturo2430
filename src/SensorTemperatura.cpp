//
// Created by automated edit
//

#include "SensorTemperatura.h"
#include <iostream>

void SensorTemperatura::procesarLectura() {
    float eliminado = 0.0f;
    if (!historial.eliminarMin(eliminado)) {
        std::cout << "[Sensor Temp] No hay lecturas para procesar.\n";
        return;
    }

    Nodo<float>* it = historial.head();
    int count = 0;
    double sum = 0.0;
    while (it) {
        sum += it->dato;
        ++count;
        it = it->siguiente;
    }

    if (count == 0) {
        std::cout << "[Sensor Temp] Lectura más baja (" << eliminado << ") eliminada. No quedan lecturas.\n";
    } else {
        double avg = sum / count;
        std::cout << "[Sensor Temp] Promedio calculado sobre " << count << " lectura" 
                  << (count == 1 ? "" : "s") << " (" << avg << ").\n";
    }
    
    // Log de liberación de memoria
    std::cout << "  [Destructor Sensor " << getNombre() << "] Liberando Lista Interna...\n";
    std::cout << "    [Log] Nodo<float> " << eliminado << " liberado.\n";
}

void SensorTemperatura::imprimirInfo() const {
    std::cout << "--- Sensor de Temperatura ---" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
}