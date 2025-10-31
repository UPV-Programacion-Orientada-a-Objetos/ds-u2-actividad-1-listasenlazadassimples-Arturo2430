//
// Created by arturo on 10/30/25.
//

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTASENSOR_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTASENSOR_H
#include <cstddef>
#include <utility>

// Lista enlazada simple generica para almacenar lecturas
template <typename T>
struct Nodo {
	T dato;
	Nodo<T>* siguiente;
	explicit Nodo(const T& d) : dato(d), siguiente(nullptr) {}
};

template <typename T>
class ListaSensor {
private:
	Nodo<T>* cabeza;

public:
	ListaSensor() : cabeza(nullptr) {}

	// Regla de los tres minima: destructor
	~ListaSensor() { clear(); }

	// Insertar al final
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

	bool vacia() const { return cabeza == nullptr; }

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