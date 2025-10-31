/**
 * @file SensorBase.cpp
 * @brief Implementación de la clase base abstracta SensorBase
 * @author Arturo
 * @date 30/10/2025
 */

#include "SensorBase.h"
#include <cstring>
#include <iostream>

/**
 * @brief Constructor de SensorBase
 * @param nombre_in Nombre del sensor
 * 
 * Copia el nombre proporcionado al arreglo interno, asegurando
 * terminación correcta con null para evitar desbordamientos.
 */
SensorBase::SensorBase(const char * nombre_in) {
    if (nombre_in) {
        std::strncpy(this->nombre, nombre_in, sizeof(this->nombre));
        this->nombre[sizeof(this->nombre)-1] = '\0';
    } else {
        this->nombre[0] = '\0';
    }
}

/**
 * @brief Imprime el nombre del sensor
 * 
 * Muestra el identificador del sensor en la salida estándar.
 */
void SensorBase::printNombre() {
    std::cout << nombre << std::endl;
}
//
// Created by arturo on 10/30/25.
//