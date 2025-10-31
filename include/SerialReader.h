/**
 * @file SerialReader.h
 * @brief Interfaz para comunicación serial con ESP32
 * @author Arturo
 * @date 30/10/2025
 */

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SERIALREADER_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SERIALREADER_H

/**
 * @class SerialReader
 * @brief Lector de datos del puerto serial para comunicación con ESP32
 * 
 * Maneja la comunicación serial con el ESP32, leyendo datos en formato
 * "T,valor" para temperatura o "P,valor" para presión.
 * Utiliza el patrón PIMPL para ocultar detalles de implementación del sistema operativo.
 */
class SerialReader {
public:
    /**
     * @struct Reading
     * @brief Estructura que representa una lectura del sensor
     */
    struct Reading {
        char type; ///< Tipo de lectura: 'T' para temperatura, 'P' para presión
        union {
            float temp;      ///< Valor de temperatura (si type == 'T')
            int pressure;    ///< Valor de presión (si type == 'P')
        } value; ///< Valor de la lectura
    };

    /**
     * @brief Constructor
     */
    SerialReader();
    
    /**
     * @brief Destructor
     */
    ~SerialReader();

    /**
     * @brief Abre el puerto serial
     * @param port Ruta del puerto serial (ej: "/dev/ttyUSB0")
     * @param baud Velocidad en baudios (115200)
     * @return true si se abrió correctamente, false en caso de error
     */
    bool begin(const char* port, unsigned long baud);
    
    /**
     * @brief Cierra el puerto serial
     */
    void close();

    /**
     * @brief Lee la siguiente lectura del puerto serial
     * @param out Referencia donde se almacenará la lectura
     * @return true si se leyó correctamente, false si hay error o timeout
     * 
     * Formato esperado: "T,23.5" o "P,1013"
     */
    bool readNext(Reading& out);

    /**
     * @brief Verifica si hay datos disponibles en el buffer serial
     * @return true si hay datos por leer, false en caso contrario
     */
    bool available() const;

private:
    class SerialImpl; ///< Implementación privada (patrón PIMPL)
    SerialImpl* pimpl; ///< Puntero a la implementación
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SERIALREADER_H