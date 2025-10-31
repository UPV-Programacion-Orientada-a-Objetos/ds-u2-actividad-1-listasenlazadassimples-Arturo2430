//
// Created by arturo on 10/30/25.
//

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTAGENERAL_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTAGENERAL_H
#include <cstddef>

class SensorBase;

// Nodo para la lista general que contiene punteros a SensorBase
struct NodoGeneral {
	SensorBase* sensor;
	NodoGeneral* siguiente;
	explicit NodoGeneral(SensorBase* s) : sensor(s), siguiente(nullptr) {}
};

class ListaGeneral {
private:
	NodoGeneral* cabeza;

public:
	// Constructor
	ListaGeneral() : cabeza(nullptr) {}

	// Destructor
	~ListaGeneral();

	// Insertar al final
	void insertar(SensorBase* sensor);

	// Procesar todos los sensores
	void procesarTodos();

	// Metodos auxiliares
	bool vacia() const { return cabeza == nullptr; }
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_LISTAGENERAL_H