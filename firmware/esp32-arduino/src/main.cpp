// Simulador de sensores para ESP32
// Envia datos aleatorios de temperatura y presion por serial

#include <Arduino.h>

// Formato del mensaje:
// T,valor    -> para temperatura (float)
// P,valor    -> para presion (int)

unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL = 2000;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  if (millis() - lastSend >= SEND_INTERVAL) {
    // alternar entre temperatura y presión
    if (random(2) == 0) {
      // temperatura: random entre 15.0 y 45.0
      float temp = 15.0 + (random(300) / 10.0);
      Serial.print("T,");
      Serial.println(temp, 1);  // un decimal
    } else {
      // presión: random entre 980 y 1020
      int pressure = 980 + random(41);
      Serial.print("P,");
      Serial.println(pressure);
    }
    
    lastSend = millis();
  }
}
