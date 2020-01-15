#include "VescUart.h"
#include <SoftwareSerial.h>

// ESP8266 (NodeMCU): RX (D5), TX (D6 / GPIO12)
SoftwareSerial vescSerial(14, 12);
VescUart UART;

void setup() {
  Serial.begin(115200);
  vescSerial.begin(115200);
  UART.setSerialPort(&vescSerial);
}

void loop() {

  if ( UART.getVescValues() ) {
    Serial.print(" temp_vesc: "); Serial.print(UART.data.temp_vesc);
    Serial.print(" motor_current: "); Serial.print(UART.data.motor_current);
    Serial.print(" input_current: "); Serial.print(UART.data.input_current);
    Serial.print(" rpm: "); Serial.print(UART.data.rpm);
    Serial.print(" motor_speed: "); Serial.print(UART.data.motor_speed);
    Serial.print(" input_voltage: "); Serial.print(UART.data.input_voltage);
    Serial.print(" battery_level: "); Serial.print(UART.data.battery_level);
    Serial.print(" amps_discharged: "); Serial.print(UART.data.amps_discharged);
    Serial.print(" watt_discharged: "); Serial.print(UART.data.watt_discharged);
    Serial.print(" tachometer: "); Serial.print(UART.data.tachometer);
    Serial.print(" fault: "); Serial.print(UART.data.fault);
    Serial.println();
  }
  else {
    Serial.println("Failed to get data!");
  }

  delay(100);
}
