#include "VescUart.h"

VescUart::VescUart(void) {

}

void VescUart::setSerialPort(Stream* port){
  serialPort = port;
}

int VescUart::receiveUartMessage(uint8_t * payloadReceived) {

  // Messages <= 255 starts with "2", 2nd byte is length
  // Messages > 255 starts with "3" 2nd and 3rd byte is length combined with 1st >>8 and then &0xFF

  uint16_t counter = 0;
  uint16_t endMessage = 256;
  bool messageRead = false;
  uint8_t messageReceived[256];
  uint16_t lenPayload = 0;

  uint32_t timeout = millis() + 100; // Defining the timestamp for timeout (100ms before timeout)

  while ( millis() < timeout && messageRead == false) {

    while (serialPort->available()) {

      messageReceived[counter++] = serialPort->read();

      if (counter == 2) {

        switch (messageReceived[0]){
          case 2:
            endMessage = messageReceived[1] + 5; //Payload size + 2 for sice + 3 for SRC and End.
            lenPayload = messageReceived[1];
            break;

          case 3:
            // ToDo: Add Message Handling > 255 (starting with 3)
            break;

          default:

            break;
        }
      }

      if (counter >= sizeof(messageReceived)) {
        break;
      }

      if (counter == endMessage && messageReceived[endMessage - 1] == 3) {
        messageReceived[endMessage] = 0;
        messageRead = true;
        break; // Exit if end of message is reached, even if there is still more data in the buffer.
      }
    }
  }

  bool unpacked = false;

  if (messageRead) {
    unpacked = unpackPayload(messageReceived, endMessage, payloadReceived);
  }

  if (unpacked) {
    // Message was read
    return lenPayload;
  }
  else {
    // No Message Read
    return 0;
  }
}


bool VescUart::unpackPayload(uint8_t * message, int lenMes, uint8_t * payload) {

  uint16_t crcMessage = 0;
  uint16_t crcPayload = 0;

  // Rebuild crc:
  crcMessage = message[lenMes - 3] << 8;
  crcMessage &= 0xFF00;
  crcMessage += message[lenMes - 2];

  // Extract payload:
  memcpy(payload, &message[2], message[1]);

  crcPayload = crc16(payload, message[1]);

  if (crcPayload == crcMessage) {
    return true;
  }
  else {
    return false;
  }
}


int VescUart::packSendPayload(uint8_t * payload, int lenPay) {

  uint16_t crcPayload = crc16(payload, lenPay);
  int count = 0;
  uint8_t messageSend[256];

  if (lenPay <= 256){
    messageSend[count++] = 2;
    messageSend[count++] = lenPay;
  }
  else{
    messageSend[count++] = 3;
    messageSend[count++] = (uint8_t)(lenPay >> 8);
    messageSend[count++] = (uint8_t)(lenPay & 0xFF);
  }

  memcpy(&messageSend[count], payload, lenPay);

  count += lenPay;
  messageSend[count++] = (uint8_t)(crcPayload >> 8);
  messageSend[count++] = (uint8_t)(crcPayload & 0xFF);
  messageSend[count++] = 3;
  messageSend[count] = '\0';

  // Sending package
  serialPort->write(messageSend, count);

  // Returns number of send bytes
  return count;
}


bool VescUart::processReadPacket(uint8_t * message) {

  COMM_PACKET_ID packetId;

  int32_t ind = 0;

  packetId = (COMM_PACKET_ID)message[0];
  message++; // Removes the packetId from the actual message (payload)

  switch (packetId) {
    case COMM_GET_VALUES_SETUP_SELECTIVE: // Structure defined here: https://github.com/vedderb/bldc/blob/43c3bbaf91f5052a35b75c2ff17b5fe99fad94d1/commands.c#L164

      ind = 4; // Skip the mask

      data.temp_vesc          = buffer_get_float16(message, 1e1, &ind);
      data.motor_current      = buffer_get_float32(message, 1e2, &ind);
      data.input_current      = buffer_get_float32(message, 1e2, &ind);
      data.rpm                = buffer_get_float32(message, 1e0, &ind);
      data.motor_speed        = buffer_get_float32(message, 1e3, &ind);
      data.input_voltage      = buffer_get_float16(message, 1e1, &ind);
      data.battery_level      = buffer_get_float16(message, 1e3, &ind);
      data.amps_discharged    = buffer_get_float32(message, 1e1, &ind);
      data.watt_discharged    = buffer_get_float32(message, 1e4, &ind);
      data.tachometer         = buffer_get_int32(message, &ind);
      data.fault = message[ind];
      return true;

    default:
      return false;
      break;
  }
}


bool VescUart::getVescValues(void) {
  uint8_t command[5];
  command[0] = { COMM_GET_VALUES_SETUP_SELECTIVE };
  //values selected : 0x00014BED
  command[1] = { 0x00 }; //mask MSB
  command[2] = { 0x01 }; //mask
  command[3] = { 0x4B }; //mask
  command[4] = { 0xED }; //mask LSB
  uint8_t payload[256];

  packSendPayload(command, 5);
  // delay(1); //needed, otherwise data is not read

  int lenPayload = receiveUartMessage(payload);

  if (lenPayload > 0 && lenPayload < 55) {
    bool readed = processReadPacket(payload); //returns true if sucessful
    return readed;
  }
  else
  {
    return false;
  }
}
