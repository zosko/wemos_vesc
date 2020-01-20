#include "VescUart.h"
#include <SoftwareSerial.h>

// ESP8266 (NodeMCU): RX (D5 / GPIO14), TX (D6 / GPIO12)
SoftwareSerial vescSerial(14, 12);

// ESP8266 (NodeMCU): RX (D7 / GPIO13), TX (D8 / GPIO15)
SoftwareSerial bluetooth(13, 15);

VescUart UART;

void setup() {
  Serial.begin(115200);
  vescSerial.begin(115200);
  bluetooth.begin(9600);
  UART.setSerialPort(&vescSerial);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  if ( UART.getVescValues() ) {
    digitalWrite(LED_BUILTIN, HIGH);
    
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

    bluetooth.write((const uint8_t *)&UART.data, sizeof(mc_value));
  }
  else {
    Serial.println("Failed to get data!");
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
}
