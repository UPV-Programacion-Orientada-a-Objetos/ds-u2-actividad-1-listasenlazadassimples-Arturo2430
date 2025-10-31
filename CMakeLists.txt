add_executable(new_target main.cpp
        include/SensorBase.h
        include/SensorTemperatura.h
        include/SensorPresion.h
        include/ListaGeneral.h
        include/ListaSensor.h
        include/SerialReader.h
        src/SensorBase.cpp
        src/SensorTemperatura.cpp
        src/SensorPresion.cpp
        src/ListaGeneral.cpp
        src/SerialReader.cpp)
