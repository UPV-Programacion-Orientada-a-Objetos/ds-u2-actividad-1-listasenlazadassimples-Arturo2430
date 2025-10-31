//
// Created by arturo on 10/30/25.
//

#ifndef DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SERIALREADER_H
#define DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SERIALREADER_H

// Interfaz para leer datos del puerto serial (ESP32)
class SerialReader {
public:
    struct Reading {
        char type;
        union {
            float temp;
            int pressure;
        } value;
    };

    SerialReader();
    ~SerialReader();

    bool begin(const char* port, unsigned long baud);
    
    void close();

    bool readNext(Reading& out);

    bool available() const;

private:
    class SerialImpl;
    SerialImpl* pimpl;
};

#endif //DS_U2_ACTIVIDAD_1_LISTASENLAZADASSIMPLES_ARTURO2430_SERIALREADER_H