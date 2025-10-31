cmake_minimum_required(VERSION 3.16)
project(iot_polimorfico LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(iot_polimorfico
        main.cpp
        src/SensorBase.cpp
        src/SensorTemperatura.cpp
        src/SensorPresion.cpp
        src/ListaGeneral.cpp
        src/SerialReader.cpp
)

target_include_directories(iot_polimorfico PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
