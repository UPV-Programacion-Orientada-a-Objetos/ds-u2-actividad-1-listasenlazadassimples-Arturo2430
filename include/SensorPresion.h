/**
 * @file SensorPresion.h
 * @brief Sensor de presión que almacena lecturas de tipo int
 * @author Arturo
 * @date 30/10/2025
 */

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORPRESION_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORPRESION_H
#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorPresion
 * @brief Sensor especializado para mediciones de presión atmosférica
 * 
 * Almacena lecturas de presión como valores enteros (hPa) en una lista enlazada.
 * Al procesar, calcula el promedio de todas las lecturas.
 */
class SensorPresion : public SensorBase {
private:
	ListaSensor<int> historial; ///< Lista enlazada que almacena las lecturas de presión

public:
	/**
	 * @brief Constructor
	 * @param nombre_in Identificador del sensor (ej: "P-105")
	 */
	explicit SensorPresion(const char* nombre_in = "") : SensorBase(nombre_in) {}
	
	/**
	 * @brief Destructor por defecto
	 */
	~SensorPresion() override = default;

	/**
	 * @brief Procesa las lecturas de presión
	 * 
	 * Calcula el promedio de todas las lecturas almacenadas.
	 */
	void procesarLectura() override;
	
	/**
	 * @brief Imprime información del sensor de presión
	 */
	void imprimirInfo() const override;

	/**
	 * @brief Registra una nueva lectura de presión
	 * @param valor Presión en hectopascales (hPa)
	 */
	void registrarLectura(int valor) { historial.insertar(valor); }
};