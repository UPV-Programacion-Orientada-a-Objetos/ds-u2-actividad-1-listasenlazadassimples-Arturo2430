//
// Created by arturo on 10/30/25.
//

/**
 * @file ListaGeneral.h
 * @brief Lista de gestión polimórfica para sensores
 * @author Arturo
 * @date 30/10/2025
 */

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTAGENERAL_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTAGENERAL_H
#include <cstddef>

class SensorBase; // forward declaration para evitar includes circulares

/**
 * @struct NodoGeneral
 * @brief Nodo para la lista general de sensores
 * 
 * Almacena punteros a SensorBase para lograr polimorfismo.
 * Permite guardar diferentes tipos de sensores en una sola lista.
 */
struct NodoGeneral {
	SensorBase* sensor; ///< Puntero polimórfico al sensor (puede ser SensorTemperatura, SensorPresion, etc.)
	NodoGeneral* siguiente; ///< Puntero al siguiente nodo
	
	/**
	 * @brief Constructor del nodo
	 * @param s Puntero al sensor a almacenar
	 */
	explicit NodoGeneral(SensorBase* s) : sensor(s), siguiente(nullptr) {}
};

/**
 * @class ListaGeneral
 * @brief Lista enlazada de gestión polimórfica para todos los sensores del sistema
 * 
 * Mantiene una lista de punteros a SensorBase, permitiendo almacenar
 * diferentes tipos de sensores y procesarlos de manera unificada mediante polimorfismo.
 * Se encarga de liberar la memoria de los sensores al destruirse.
 */
class ListaGeneral {
private:
	NodoGeneral* cabeza; ///< Puntero al primer sensor de la lista

public:
	/**
	 * @brief Constructor por defecto
	 * Inicializa una lista vacía de sensores
	 */
	ListaGeneral() : cabeza(nullptr) {}

	/**
	 * @brief Destructor
	 * Libera la memoria de todos los nodos y sensores (destrucción polimórfica)
	 */
	~ListaGeneral();

	/**
	 * @brief Inserta un nuevo sensor al final de la lista
	 * @param sensor Puntero al sensor a insertar (la lista toma ownership del puntero)
	 * @note La lista es responsable de liberar la memoria del sensor
	 */
	void insertar(SensorBase* sensor);

	/**
	 * @brief Procesa todos los sensores de la lista de manera polimórfica
	 * 
	 * Itera sobre todos los sensores y llama al método procesarLectura()
	 * de cada uno, ejecutando la lógica específica de cada tipo de sensor.
	 */
	void procesarTodos();

	/**
	 * @brief Verifica si la lista está vacía
	 * @return true si no hay sensores, false en caso contrario
	 */
	bool vacia() const { return cabeza == nullptr; }
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTAGENERAL_H