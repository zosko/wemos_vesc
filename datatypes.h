/*
	Copyright 2016 Benjamin Vedder	benjamin@vedder.se

	This file is part of the VESC firmware.

	The VESC firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The VESC firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
  FAULT_CODE_NONE = 0,
  FAULT_CODE_OVER_VOLTAGE,
  FAULT_CODE_UNDER_VOLTAGE,
  FAULT_CODE_DRV,
  FAULT_CODE_ABS_OVER_CURRENT,
  FAULT_CODE_OVER_TEMP_FET,
  FAULT_CODE_OVER_TEMP_MOTOR,
  FAULT_CODE_GATE_DRIVER_OVER_VOLTAGE,
  FAULT_CODE_GATE_DRIVER_UNDER_VOLTAGE,
  FAULT_CODE_MCU_UNDER_VOLTAGE,
  FAULT_CODE_BOOTING_FROM_WATCHDOG_RESET,
  FAULT_CODE_ENCODER
} mc_fault_code;

// Communication commands
typedef enum {
  COMM_FW_VERSION = 0,
  COMM_JUMP_TO_BOOTLOADER,
  COMM_ERASE_NEW_APP,
  COMM_WRITE_NEW_APP_DATA,
  COMM_GET_VALUES,
  COMM_SET_DUTY,
  COMM_SET_CURRENT,
  COMM_SET_CURRENT_BRAKE,
  COMM_SET_RPM,
  COMM_SET_POS,
  COMM_SET_HANDBRAKE,
  COMM_SET_DETECT,
  COMM_SET_SERVO_POS,
  COMM_SET_MCCONF,
  COMM_GET_MCCONF,
  COMM_GET_MCCONF_DEFAULT,
  COMM_SET_APPCONF,
  COMM_GET_APPCONF,
  COMM_GET_APPCONF_DEFAULT,
  COMM_SAMPLE_PRINT,
  COMM_TERMINAL_CMD,
  COMM_PRINT,
  COMM_ROTOR_POSITION,
  COMM_EXPERIMENT_SAMPLE,
  COMM_DETECT_MOTOR_PARAM,
  COMM_DETECT_MOTOR_R_L,
  COMM_DETECT_MOTOR_FLUX_LINKAGE,
  COMM_DETECT_ENCODER,
  COMM_DETECT_HALL_FOC,
  COMM_REBOOT,
  COMM_ALIVE,
  COMM_GET_DECODED_PPM,
  COMM_GET_DECODED_ADC,
  COMM_GET_DECODED_CHUK,
  COMM_FORWARD_CAN,
  COMM_SET_CHUCK_DATA,
  COMM_CUSTOM_APP_DATA,
  COMM_NRF_START_PAIRING,
  COMM_GPD_SET_FSW,
  COMM_GPD_BUFFER_NOTIFY,
  COMM_GPD_BUFFER_SIZE_LEFT,
  COMM_GPD_FILL_BUFFER,
  COMM_GPD_OUTPUT_SAMPLE,
  COMM_GPD_SET_MODE,
  COMM_GPD_FILL_BUFFER_INT8,
  COMM_GPD_FILL_BUFFER_INT16,
  COMM_GPD_SET_BUFFER_INT_SCALE,
  COMM_GET_VALUES_SETUP,
  COMM_SET_MCCONF_TEMP,
  COMM_SET_MCCONF_TEMP_SETUP,
  COMM_GET_VALUES_SELECTIVE,
  COMM_GET_VALUES_SETUP_SELECTIVE,
  COMM_EXT_NRF_PRESENT,
  COMM_EXT_NRF_ESB_SET_CH_ADDR,
  COMM_EXT_NRF_ESB_SEND_DATA,
  COMM_EXT_NRF_ESB_RX_DATA,
  COMM_EXT_NRF_SET_ENABLED,
  COMM_DETECT_MOTOR_FLUX_LINKAGE_OPENLOOP,
  COMM_DETECT_APPLY_ALL_FOC,
  COMM_JUMP_TO_BOOTLOADER_ALL_CAN,
  COMM_ERASE_NEW_APP_ALL_CAN,
  COMM_WRITE_NEW_APP_DATA_ALL_CAN,
  COMM_PING_CAN,
  COMM_APP_DISABLE_OUTPUT
} COMM_PACKET_ID;

/** Struct to store the telemetry data returned by the VESC */
typedef struct {
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
} mc_value;

#endif /* DATATYPES_H_ */
