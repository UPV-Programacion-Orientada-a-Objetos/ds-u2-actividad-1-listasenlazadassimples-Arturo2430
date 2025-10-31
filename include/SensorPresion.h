//
// Created by arturo on 10/30/25.
//

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORPRESION_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORPRESION_H
#include "SensorBase.h"
#include "ListaSensor.h"

class SensorPresion : public SensorBase {
private:
	ListaSensor<int> historial;

public:
	explicit SensorPresion(const char* nombre = "") : SensorBase(nombre) {}
	~SensorPresion() override = default;

	void procesarLectura() override;
	void imprimirInfo() const override;

	void registrarLectura(int valor) { historial.insertar(valor); }
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORPRESION_H