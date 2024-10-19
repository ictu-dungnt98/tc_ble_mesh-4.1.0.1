#ifndef TH_SENSOR_H_
#define TH_SENSOR_H_

#include <stdint.h>

typedef struct __attribute((packed))
{
    uint8_t battery_percent; /* battery helth. 0-100% */
    uint16_t temp;           /* Temparature, need /10 convert to float real.*/
    uint16_t humi;           /* Humidity , need / 10 convert to float real.*/
    uint8_t is_change_state;
} thsensor_msg_state_t;

typedef struct __attribute((packed))
{
    uint8_t battery_percent; /* battery helth. 0-100% */
    uint16_t temp;           /* Temparature, need /10 convert to float real.*/
    uint16_t humi;           /* Humidity , need / 10 convert to float real.*/
    uint32_t sw_version;
    uint32_t hw_version;
} thsensor_msg_info_t;

#endif /* MESSAGE_SMSENSOR_MODEL_H__ */