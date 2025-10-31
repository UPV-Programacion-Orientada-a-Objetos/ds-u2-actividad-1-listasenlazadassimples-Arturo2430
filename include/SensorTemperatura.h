/**
 * @file SensorTemperatura.h
 * @brief Sensor de temperatura que almacena lecturas de tipo float
 * @author Arturo
 * @date 30/10/2025
 */

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORTEMPERATURA_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORTEMPERATURA_H
#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorTemperatura
 * @brief Sensor especializado para mediciones de temperatura
 * 
 * Almacena lecturas de temperatura como valores float en una lista enlazada.
 * Al procesar, elimina la lectura más baja y calcula el promedio de las restantes.
 */
class SensorTemperatura : public SensorBase {
private:
	ListaSensor<float> historial; ///< Lista enlazada que almacena las lecturas de temperatura

public:
	/**
	 * @brief Constructor
	 * @param nombre_in Identificador del sensor (ej: "T-001")
	 */
	explicit SensorTemperatura(const char* nombre_in = "") : SensorBase(nombre_in) {}
	
	/**
	 * @brief Destructor por defecto
	 */
	~SensorTemperatura() override = default;

	/**
	 * @brief Procesa las lecturas de temperatura
	 * 
	 * Elimina la lectura más baja (posible valor anómalo) y calcula
	 * el promedio de las lecturas restantes.
	 */
	void procesarLectura() override;
	
	/**
	 * @brief Imprime información del sensor de temperatura
	 */
	void imprimirInfo() const override;

	/**
	 * @brief Registra una nueva lectura de temperatura
	 * @param valor Temperatura en grados Celsius
	 */
	void registrarLectura(float valor) { historial.insertar(valor); }
};