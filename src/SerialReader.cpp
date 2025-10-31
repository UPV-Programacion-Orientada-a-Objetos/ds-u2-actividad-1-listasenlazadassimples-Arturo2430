#include "SerialReader.h"
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/ioctl.h>
#include <iostream>

class SerialReader::SerialImpl {
public:
    int fd;
    char buffer[256];
    size_t bufferPos;

    SerialImpl() : fd(-1), bufferPos(0) {}
    
    ~SerialImpl() {
        if (fd >= 0) {
            ::close(fd);
        }
    }
};

SerialReader::SerialReader() : pimpl(new SerialImpl()) {}

SerialReader::~SerialReader() {
    delete pimpl;
}

bool SerialReader::begin(const char* port, unsigned long baud) {
    struct termios tty;
    
    // abrir puerto
    pimpl->fd = open(port, O_RDWR);
    if (pimpl->fd < 0) {
        std::cerr << "[SerialReader] Error abriendo " << port << std::endl;
        return false;
    }

    // obtener atributos actuales
    if (tcgetattr(pimpl->fd, &tty) != 0) {
        std::cerr << "[SerialReader] Error en tcgetattr" << std::endl;
        close();
        return false;
    }

    // configurar puerto
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);
    
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;
    
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 1;
    
    // aplicar configuración
    if (tcsetattr(pimpl->fd, TCSANOW, &tty) != 0) {
        std::cerr << "[SerialReader] Error en tcsetattr" << std::endl;
        close();
        return false;
    }

    std::cout << "[SerialReader] Puerto " << port << " abierto a " << baud << " baud" << std::endl;
    return true;
}

void SerialReader::close() {
    if (pimpl->fd >= 0) {
        ::close(pimpl->fd);
        pimpl->fd = -1;
    }
}

bool SerialReader::available() const {
    if (pimpl->fd < 0) return false;
    
    int bytes;
    ioctl(pimpl->fd, FIONREAD, &bytes);
    return bytes > 0;
}

bool SerialReader::readNext(Reading& out) {
    if (pimpl->fd < 0) return false;

    // leer hasta encontrar un newline
    char c;
    while (true) {
        if (read(pimpl->fd, &c, 1) > 0) {
            if (c == '\n') {
                pimpl->buffer[pimpl->bufferPos] = '\0';
                pimpl->bufferPos = 0;
                
                // parsear buffer
                char type;
                char* value_str;
                
                type = pimpl->buffer[0];
                value_str = strchr(pimpl->buffer, ',');
                
                if (!value_str) return false;
                value_str++;
                
                out.type = type;
                if (type == 'T') {
                    out.value.temp = atof(value_str);
                    std::cout << "[SerialReader] Leído: Temperatura=" << out.value.temp << "°C" << std::endl;
                } else if (type == 'P') {
                    out.value.pressure = atoi(value_str);
                    std::cout << "[SerialReader] Leído: Presión=" << out.value.pressure << " hPa" << std::endl;
                } else {
                    return false;
                }
                
                return true;
            } else if (pimpl->bufferPos < sizeof(pimpl->buffer)-1) {
                pimpl->buffer[pimpl->bufferPos++] = c;
            }
        } else {
            usleep(100000);
        }
    }
    
    return false;
}