//
// Created by arturo on 10/30/25.
//

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORBASE_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORBASE_H

#include <cstddef>

// Clase base abstracta para todos los sensores
class SensorBase {
protected:
	char nombre[50];

public:

	// Constructor
	explicit SensorBase(const char * nombre);

	// Destructor
	virtual ~SensorBase() = default;


	void setNombre(const char* n) {
		if (!n) { nombre[0] = '\0'; return; }
		size_t i = 0;
		for (; n[i] && i < sizeof(nombre)-1; ++i) nombre[i] = n[i];
		nombre[i] = '\0';
	}


	virtual void procesarLectura() = 0;
	virtual void imprimirInfo() const = 0;
	void printNombre();
	const char* getNombre() const { return nombre; }
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORBASE_H