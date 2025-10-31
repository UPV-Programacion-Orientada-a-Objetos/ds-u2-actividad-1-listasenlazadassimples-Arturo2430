//
// Created by arturo on 10/30/25.
//

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORTEMPERATURA_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORTEMPERATURA_H
#include "SensorBase.h"
#include "ListaSensor.h"

class SensorTemperatura : public SensorBase {
private:
	ListaSensor<float> historial;

public:

	// Contructor
	explicit SensorTemperatura(const char* nombre) : SensorBase(nombre) {}

	// Destructor
	~SensorTemperatura() override = default;

	void procesarLectura() override;
	void imprimirInfo() const override;
	void registrarLectura(float valor) { historial.insertar(valor); }
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORTEMPERATURA_H