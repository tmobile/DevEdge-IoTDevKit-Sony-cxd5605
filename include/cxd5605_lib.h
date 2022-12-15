/*
 * Copyright (c) 2022 T-Mobile USA, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CXD5605_LIB_H
#define CXD5605_LIB_H

#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>

typedef enum shim_cmd_enum {
	CMD_VERSION = 1,
	CMD_PULSE,
	CMD_OPERATING_MODE,
	CMD_TIME_SET,
	CMD_WARM_START,
	CMD_HOT_START,
	CMD_HOT_START_TTFF,
	CMD_COLD_START,
	CMD_SENTENCE_SELECT,
	CMD_ASSIST_GEN_FUNCTION_CONTROL,
	CMD_STOP,
	CMD_WAKE_UP,
	CMD_SLEEP
} shim_cmd_enum_t;

// This is where you find a table in the flash
// of the file sizes.  This needs to be updated
// when you change firmware.
#define FILE_SIZES 0

// These are the address of where the files start.
// They may have to be adjusted as the files change
// sizes.
#define FILE1_START 4096
#define FILE2_START 8192
#define FILE3_START 614400
#define FILE4_START 618496

// These are debug items that you can turn on
// #define TRACESTATE
// #define TRACEPACKETS

/***Firmware uploading state machines***/
#define ERASE_FIRMWARE 0
#define GET_ERASE_FIRMWARE_RES 1
#define CHECK_BUF_AVAILABILITY 2
#define GET_BUF_AVAILABILITY 3
#define SEND_FILE1 4
#define SEND_FILE2 5
#define SEND_FILE3 6
#define SEND_FILE4 7
#define SEND_EXEC 8
#define BUFFER_3 9
#define CHECK_BUFFER_3 10
#define EXECUTION_STATUS_CHECK 11
#define EXECUTION_STATUS_CHECK_RESULT 12
#define BUFFER_2 13
#define CHECK_BUFFER_2 14
#define COMMAND_EXECUTION_RESULT_CHECK 15
#define COMMAND_EXECUTION_RESULT_CHECK_RET 16

#define ERROR_STATE 98
#define WAIT 99

#define ERROR_STOP 30

#define CHECK_ALL_BUFFERS 0x0F
#define CHECK_GOOD_PACKET 0x00

#define BUFFER_0 0xA0
#define BUFFER_1 0xA1

#define LOADH 0x02
#define LOADC1 0x04
#define LOADC2 0x05
#define EXEC 0x06

#define GNSS_GPIO_NAME "GPIO_F"
#define GNSS_BOOT_REC 6
#define GNSS_RSTn 8
#define GNSS_INT 7
#define GNSS_PWR_ON 10

#define SHIM_CXD5605_ADDRESS 0x24
#define SHIM_MAXFIELDS 32


#define MAX_INT_CNT 3

#define PIN_IN 13

struct shim_drv_data {
	struct gpio_callback gpio_cb;
	gpio_flags_t mode;
	int index;
	int aux;
};

typedef void (*cxd5605_nmea_cb)(struct gnss_global_data *pvt);
typedef void (*cxd5605_resp_cb)(struct cxd5605_data *drv_data, struct cxd5605_cmd_data *cxd5605_cmd_data, int cmd, int ret);

int cxd5605_lib_init(const struct device *dev);
int cxd5605_pulse(const struct device *dev, int param);
int cxd5605_sentence_select(const struct device *dev, int param);
int cxd5605_cold_start(const struct device *dev);
int cxd5605_wake_up(const struct device *dev);
int cxd5605_operating_mode(const struct device *dev, int mode, int pos_cycle, int sleep_time);
int cxd5605_hot_start(const struct device *dev);
int cxd5605_hot_start_ttff(const struct device *dev);
int cxd5605_warm_start(const struct device *dev);
int cxd5605_time_set(const struct device *dev, int year, int month, int day, int hour, int minute, int second);
int cxd5605_sleep(const struct device *dev, int transfer_state);
int cxd5605_version(const struct device *dev);
int cxd5605_assist_gen_function_control(const struct device *dev, int enable);
int cxd5605_stop(const struct device *dev);

int cxd5605_register_resp_callback(const struct device *dev, cxd5605_resp_cb resp);
int cxd5605_register_nmea_callback(const struct device *dev, cxd5605_nmea_cb nmea);

#endif
