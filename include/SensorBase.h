/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los sensores del sistema IoT
 * @author Arturo
 * @date 30/10/2025
 */

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORBASE_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORBASE_H

#include <cstddef>

/**
 * @class SensorBase
 * @brief Clase base abstracta que define la interfaz común para todos los sensores
 * 
 * Esta clase utiliza polimorfismo para permitir el manejo uniforme de diferentes
 * tipos de sensores (temperatura, presión, etc.) en el sistema.
 */
class SensorBase {
protected:
	char nombre[50]; ///< Identificador único del sensor (máximo 49 caracteres)

public:
	/**
	 * @brief Constructor de la clase SensorBase
	 * @param nombre Identificador del sensor (ej: "T-001", "P-105")
	 */
	explicit SensorBase(const char * nombre);

	/**
	 * @brief Destructor virtual para permitir destrucción polimórfica correcta
	 */
	virtual ~SensorBase() = default;

	/**
	 * @brief Establece el nombre del sensor
	 * @param n Nuevo nombre para el sensor
	 */
	void setNombre(const char* n) {
		if (!n) { nombre[0] = '\0'; return; }
		size_t i = 0;
		for (; n[i] && i < sizeof(nombre)-1; ++i) nombre[i] = n[i];
		nombre[i] = '\0';
	}

	/**
	 * @brief Procesa las lecturas almacenadas del sensor
	 * @pure Método virtual puro que debe ser implementado por las clases derivadas
	 * 
	 * Cada tipo de sensor implementa su propia lógica de procesamiento:
	 * - SensorTemperatura: Elimina la lectura mínima y calcula promedio
	 * - SensorPresion: Calcula el promedio de todas las lecturas
	 */
	virtual void procesarLectura() = 0;
	
	/**
	 * @brief Imprime información del sensor
	 * @pure Método virtual puro que debe ser implementado por las clases derivadas
	 */
	virtual void imprimirInfo() const = 0;
	
	/**
	 * @brief Imprime el nombre del sensor en la salida estándar
	 */
	void printNombre();
	
	/**
	 * @brief Obtiene el nombre del sensor
	 * @return Puntero constante al nombre del sensor
	 */
	const char* getNombre() const { return nombre; }
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SENSORBASE_H