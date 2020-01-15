#ifndef _VESCUART_h
#define _VESCUART_h

#include <Arduino.h>
#include "datatypes.h"
#include "buffer.h"
#include "crc.h"

class VescUart
{
    /** Struct to store the telemetry data returned by the VESC */
    struct dataPackage {
      float temp_vesc;
      float motor_current;
      float input_current;
      float rpm;
      float motor_speed;
      float input_voltage;
      float battery_level;
      float amps_discharged;
      float watt_discharged;
      long tachometer;
      uint8_t fault;
    };

  public:
    /**
       @brief      Class constructor
    */
    VescUart(void);

    /** Variabel to hold measurements returned from VESC */
    dataPackage data;

    /**
       @brief      Set the serial port for uart communication
       @param      port  - Reference to Serial port (pointer)
    */
    void setSerialPort(Stream* port);

    /**
       @brief      Sends a command to VESC and stores the returned data

       @return     True if successfull otherwise false
    */
    bool getVescValues(void);

  private:

    /** Variabel to hold the reference to the Serial object to use for UART */
    Stream* serialPort = NULL;

    /**
       @brief      Packs the payload and sends it over Serial

       @param      payload  - The payload as a unit8_t Array with length of int lenPayload
       @param      lenPay   - Length of payload
       @return     The number of bytes send
    */
    int packSendPayload(uint8_t * payload, int lenPay);

    /**
       @brief      Receives the message over Serial

       @param      payloadReceived  - The received payload as a unit8_t Array
       @return     The number of bytes receeived within the payload
    */
    int receiveUartMessage(uint8_t * payloadReceived);

    /**
       @brief      Verifies the message (CRC-16) and extracts the payload

       @param      message  - The received UART message
       @param      lenMes   - The lenght of the message
       @param      payload  - The final payload ready to extract data from
       @return     True if the process was a success
    */
    bool unpackPayload(uint8_t * message, int lenMes, uint8_t * payload);

    /**
       @brief      Extracts the data from the received payload

       @param      message  - The payload to extract data from
       @return     True if the process was a success
    */
    bool processReadPacket(uint8_t * message);
};

#endif
