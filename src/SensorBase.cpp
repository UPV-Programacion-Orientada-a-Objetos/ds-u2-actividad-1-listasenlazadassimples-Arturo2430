//
// Implementacion minima de SensorBase
//

#include "SensorBase.h"
#include <cstring>
#include <iostream>

SensorBase::SensorBase(const char * nombre_in) {
    if (nombre_in) {
        std::strncpy(this->nombre, nombre_in, sizeof(this->nombre));
        this->nombre[sizeof(this->nombre)-1] = '\0';
    } else {
        this->nombre[0] = '\0';
    }
}

void SensorBase::printNombre() {
    std::cout << nombre << std::endl;
}
//
// Created by arturo on 10/30/25.
//