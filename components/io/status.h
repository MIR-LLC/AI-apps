#ifndef _STATUS_H_
#define _STATUS_H_

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#define GET_BIT_POS(mask) 31 - __builtin_clz(mask)
#define ALL_BITS(pos)     BIT##pos - 1

#define STATUS_STATE_BLE_CONNECTED_MSK BIT0
#define STATUS_ALL_BITS_MSK            ALL_BITS(1)

extern EventGroupHandle_t xStatusEventGroup;

#endif // _STATUS_H_
