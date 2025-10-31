//
// Sistema IoT de Monitoreo Polimórfico con Menú Interactivo
//
#include "ListaGeneral.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "SerialReader.h"
#include <iostream>
#include <limits>

#define SERIAL_PORT "/dev/ttyUSB0"

// Estructura para almacenar sensores creados
struct SensorInfo {
    char id[50];
    SensorBase* sensor;
    SensorInfo* siguiente;
};

class RegistroSensores {
private:
    SensorInfo* cabeza;
    
public:
    RegistroSensores() : cabeza(nullptr) {}
    
    void agregar(const char* id, SensorBase* sensor) {
        SensorInfo* nuevo = new SensorInfo();
        // copiar id
        size_t i = 0;
        for (; id[i] && i < sizeof(nuevo->id)-1; ++i) {
            nuevo->id[i] = id[i];
        }
        nuevo->id[i] = '\0';
        
        nuevo->sensor = sensor;
        nuevo->siguiente = nullptr;
        
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            SensorInfo* it = cabeza;
            while (it->siguiente) it = it->siguiente;
            it->siguiente = nuevo;
        }
    }
    
    SensorBase* buscar(const char* id) {
        SensorInfo* it = cabeza;
        while (it) {
            // comparar ids
            bool igual = true;
            for (size_t i = 0; it->id[i] || id[i]; ++i) {
                if (it->id[i] != id[i]) {
                    igual = false;
                    break;
                }
            }
            if (igual) return it->sensor;
            it = it->siguiente;
        }
        return nullptr;
    }
    
    void listar() {
        if (!cabeza) {
            std::cout << "  No hay sensores registrados.\n";
            return;
        }
        SensorInfo* it = cabeza;
        while (it) {
            std::cout << "  - " << it->id << "\n";
            it = it->siguiente;
        }
    }
};

void mostrarMenu() {
    std::cout << "\n===========================================\n";
    std::cout << "  SISTEMA IoT DE MONITOREO POLIMÓRFICO\n";
    std::cout << "===========================================\n";
    std::cout << "1. Crear Sensor (Temperatura)\n";
    std::cout << "2. Crear Sensor (Presión)\n";
    std::cout << "3. Registrar Lectura (Manual)\n";
    std::cout << "4. Registrar Lectura (desde ESP32)\n";
    std::cout << "5. Ejecutar Procesamiento Polimórfico\n";
    std::cout << "6. Cerrar Sistema\n";
    std::cout << "===========================================\n";
    std::cout << "Opción: ";
}

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::cout << "--- Sistema IoT de Monitoreo Polimórfico ---\n";
    
    ListaGeneral lista;
    RegistroSensores registro;
    SerialReader reader;
    bool serialAbierto = false;
    
    int opcion = 0;
    
    while (true) {
        mostrarMenu();
        
        if (!(std::cin >> opcion)) {
            limpiarBuffer();
            std::cout << "Entrada inválida. Intente de nuevo.\n";
            continue;
        }
        limpiarBuffer();
        
        switch (opcion) {
            case 1: {
                // Crear Sensor Temperatura
                std::cout << "\nOpción 1: Crear Sensor (Tipo Temp - FLOAT)\n";
                char id[50];
                std::cout << "Ingrese ID del sensor (ej: T-001): ";
                std::cin.getline(id, sizeof(id));
                
                if (registro.buscar(id)) {
                    std::cout << "Error: Ya existe un sensor con ese ID.\n";
                    break;
                }
                
                SensorTemperatura* temp = new SensorTemperatura(id);
                registro.agregar(id, temp);
                lista.insertar(temp);
                std::cout << "Sensor '" << id << "' creado e insertado en la lista de gestión.\n";
                break;
            }
            
            case 2: {
                // Crear Sensor Presión
                std::cout << "\nOpción 2: Crear Sensor (Tipo Presion - INT)\n";
                char id[50];
                std::cout << "Ingrese ID del sensor (ej: P-105): ";
                std::cin.getline(id, sizeof(id));
                
                if (registro.buscar(id)) {
                    std::cout << "Error: Ya existe un sensor con ese ID.\n";
                    break;
                }
                
                SensorPresion* pres = new SensorPresion(id);
                registro.agregar(id, pres);
                lista.insertar(pres);
                std::cout << "Sensor '" << id << "' creado e insertado en la lista de gestión.\n";
                break;
            }
            
            case 3: {
                // Registrar Lectura Manual
                std::cout << "\nOpción 3: Registrar Lectura (Manual)\n";
                std::cout << "Sensores disponibles:\n";
                registro.listar();
                
                char id[50];
                std::cout << "Ingrese ID del sensor: ";
                std::cin.getline(id, sizeof(id));
                
                SensorBase* sensor = registro.buscar(id);
                if (!sensor) {
                    std::cout << "Error: Sensor no encontrado.\n";
                    break;
                }
                
                // Intentar cast a cada tipo
                SensorTemperatura* temp = dynamic_cast<SensorTemperatura*>(sensor);
                if (temp) {
                    float valor;
                    std::cout << "Ingrese valor de temperatura (float): ";
                    std::cin >> valor;
                    limpiarBuffer();
                    temp->registrarLectura(valor);
                    std::cout << "ID: " << id << ". Valor: " << valor << " (float) - Registrado.\n";
                } else {
                    SensorPresion* pres = dynamic_cast<SensorPresion*>(sensor);
                    if (pres) {
                        int valor;
                        std::cout << "Ingrese valor de presión (int): ";
                        std::cin >> valor;
                        limpiarBuffer();
                        pres->registrarLectura(valor);
                        std::cout << "ID: " << id << ". Valor: " << valor << " (int) - Registrado.\n";
                    }
                }
                break;
            }
            
            case 4: {
                // Registrar Lectura desde ESP32
                std::cout << "\nOpción 4: Registrar Lectura (desde ESP32)\n";
                
                if (!serialAbierto) {
                    std::cout << "Abriendo puerto serial " << SERIAL_PORT << "...\n";
                    if (!reader.begin(SERIAL_PORT, 115200)) {
                        std::cerr << "Error: No se pudo abrir el puerto serial.\n";
                        std::cerr << "Verifique que el ESP32 esté conectado.\n";
                        break;
                    }
                    serialAbierto = true;
                }
                
                std::cout << "Sensores disponibles:\n";
                registro.listar();
                std::cout << "\nEsperando datos del ESP32 (presione Enter para cancelar)...\n";
                
                SerialReader::Reading reading;
                if (reader.readNext(reading)) {
                    SensorBase* sensor = nullptr;
                    
                    if (reading.type == 'T') {
                        // Buscar primer sensor de temperatura
                        std::cout << "Dato recibido: Temperatura = " << reading.value.temp << "°C\n";
                        std::cout << "Ingrese ID del sensor de temperatura para registrar: ";
                        char id[50];
                        std::cin.getline(id, sizeof(id));
                        
                        sensor = registro.buscar(id);
                        SensorTemperatura* temp = dynamic_cast<SensorTemperatura*>(sensor);
                        if (temp) {
                            temp->registrarLectura(reading.value.temp);
                            std::cout << "Lectura registrada en " << id << "\n";
                        } else {
                            std::cout << "Error: Sensor no encontrado o no es de temperatura.\n";
                        }
                    } else if (reading.type == 'P') {
                        std::cout << "Dato recibido: Presión = " << reading.value.pressure << " hPa\n";
                        std::cout << "Ingrese ID del sensor de presión para registrar: ";
                        char id[50];
                        std::cin.getline(id, sizeof(id));
                        
                        sensor = registro.buscar(id);
                        SensorPresion* pres = dynamic_cast<SensorPresion*>(sensor);
                        if (pres) {
                            pres->registrarLectura(reading.value.pressure);
                            std::cout << "Lectura registrada en " << id << "\n";
                        } else {
                            std::cout << "Error: Sensor no encontrado o no es de presión.\n";
                        }
                    }
                } else {
                    std::cout << "No se recibieron datos o timeout.\n";
                }
                break;
            }
            
            case 5: {
                // Ejecutar Procesamiento Polimórfico
                lista.procesarTodos();
                break;
            }
            
            case 6: {
                // Cerrar Sistema
                std::cout << "\nOpción 6: Cerrar Sistema (Liberar Memoria)\n";
                if (serialAbierto) {
                    reader.close();
                }
                // ListaGeneral destructor liberará todos los sensores
                std::cout << "Saliendo del sistema...\n";
                return 0;
            }
            
            default:
                std::cout << "Opción inválida. Intente de nuevo.\n";
                break;
        }
    }
    
    return 0;
}