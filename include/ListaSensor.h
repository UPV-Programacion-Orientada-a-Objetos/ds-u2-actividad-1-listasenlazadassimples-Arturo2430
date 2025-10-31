/**
 * @file ListaSensor.h
 * @brief Implementación de lista enlazada simple genérica para almacenar lecturas de sensores
 * @author Arturo
 * @date 30/10/2025
 */

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTASENSOR_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTASENSOR_H
#include <cstddef>
#include <utility>

/**
 * @struct Nodo
 * @brief Nodo genérico para la lista enlazada
 * @tparam T Tipo de dato que almacena el nodo (int, float, etc.)
 */
template <typename T>
struct Nodo {
	T dato; ///< Dato almacenado en el nodo
	Nodo<T>* siguiente; ///< Puntero al siguiente nodo en la lista
	
	/**
	 * @brief Constructor del nodo
	 * @param d Dato a almacenar
	 */
	explicit Nodo(const T& d) : dato(d), siguiente(nullptr) {}
};

/**
 * @class ListaSensor
 * @brief Lista enlazada simple genérica para almacenar lecturas de sensores
 * @tparam T Tipo de dato de las lecturas (float para temperatura, int para presión)
 * 
 * Implementa una lista enlazada simple con gestión manual de memoria.
 * Sigue la Regla de los Tres para evitar fugas de memoria.
 */
template <typename T>
class ListaSensor {
private:
	Nodo<T>* cabeza; ///< Puntero al primer nodo de la lista

public:
	/**
	 * @brief Constructor por defecto
	 * Inicializa una lista vacía
	 */
	ListaSensor() : cabeza(nullptr) {}

	/**
	 * @brief Destructor
	 * Libera toda la memoria de los nodos (Regla de los Tres)
	 */
	~ListaSensor() { clear(); }

	/**
	 * @brief Inserta un nuevo valor al final de la lista
	 * @param valor Valor a insertar
	 */
	void insertar(const T& valor) {
		Nodo<T>* nuevo = new Nodo<T>(valor);
		if (!cabeza) {
			cabeza = nuevo;
			return;
		}
		Nodo<T>* it = cabeza;
		while (it->siguiente) it = it->siguiente;
		it->siguiente = nuevo;
	}

	/**
	 * @brief Verifica si la lista está vacía
	 * @return true si la lista no tiene elementos, false en caso contrario
	 */
	bool vacia() const { return cabeza == nullptr; }

	/**
	 * @brief Elimina todos los nodos de la lista y libera memoria
	 */
	void clear() {
		Nodo<T>* it = cabeza;
		while (it) {
			Nodo<T>* sig = it->siguiente;
			delete it;
			it = sig;
		}
		cabeza = nullptr;
	}

	// Acceso basico
	Nodo<T>* head() const { return cabeza; }
    
	// Elimina el nodo con el valor minimo y devuelve true si se elimino
	bool eliminarMin(T& out) {
		if (!cabeza) return false;
		Nodo<T>* prev = nullptr;
		Nodo<T>* cur = cabeza;
		Nodo<T>* minPrev = nullptr;
		Nodo<T>* minNode = cabeza;
		while (cur) {
			if (cur->dato < minNode->dato) {
				minPrev = prev;
				minNode = cur;
			}
			prev = cur;
			cur = cur->siguiente;
		}

		// eliminar minNode
		if (minPrev) {
			minPrev->siguiente = minNode->siguiente;
		} else {
			// minNode es cabeza
			cabeza = minNode->siguiente;
		}

		out = minNode->dato;
		delete minNode;
		return true;
	}
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTASENSOR_H