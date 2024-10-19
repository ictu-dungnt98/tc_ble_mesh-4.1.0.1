#ifndef MESSAGE_MTSENSOR_MODEL_H__
#define MESSAGE_MTSENSOR_MODEL_H__


#include "nrf_mesh_defines.h"

enum mtsensor_set_type_t
{
    MTSENSOR_SET_TYPE_NOT_SUPPORT = 0,        /* not support. */
    MTSENSOR_SET_TYPE_SET_PCNLUX,             /* set percent lux. */
    MTSENSOR_SET_TYPE_SET_TIME,               /* set delay time */
};

enum mtsensor_rep_type_t
{
    MTSENSOR_REP_TYPE_NOT_SUPPORT = 0,        /* not support. */
    MTSENSOR_REP_TYPE_REP_STATE,              /* reply state. */
    MTSENSOR_REP_TYPE_REP_INFO,               /* reply device. */
    MTSENSOR_SET_TYPE_REP_SET_PCNLUX,         /* reply pcnlux device wakeup. */
    MTSENSOR_SET_TYPE_REP_SET_TIME,           /* reply delay time device wakeup. */
};

typedef struct __attribute((packed))
{
    uint8_t detect : 1;          /* mtsensor state. 1 detect, 0 no detection detected */
    uint8_t battery_percent : 7; /* battery helth. 0-100% */
    uint32_t darkLight : 1;      /* dark light. 0 is dark, 1 is light */
    uint32_t lux : 31;           /* Lux Value */
    uint8_t is_change_state;
} mtsensor_state_t;

typedef struct __attribute((packed))
{
    uint8_t pcnLux;
} mtsensor_set_pcnlux_t;

typedef struct __attribute((packed))
{
    uint32_t time;
} mtsensor_set_time_t;

typedef struct __attribute((packed))
{
    uint8_t detect : 1;          /* mtsensor state. 1 detect, 0 no detection detected */
    uint8_t battery_percent : 7; /* battery helth. 0-100% */
    uint32_t darkLight : 1;      /* dark light. 0 is dark, 1 is light */
    uint32_t lux : 31;           /* Lux Value */
    uint8_t percen_lux;
    uint32_t delay_time;
    uint32_t sw_version;
    uint32_t hw_version;
} mtsensor_info_t;

typedef union __attribute((packed))
{
    mtsensor_set_pcnlux_t set_pcnLux;
    mtsensor_set_time_t set_time;
} mtsensor_msg_set_t;

typedef union __attribute((packed))
{
    mtsensor_state_t state;
    mtsensor_info_t info;
    mtsensor_set_pcnlux_t pcnLux;
    mtsensor_set_time_t time;
} mtsensor_msg_rep_t;

uint32_t mtsensor_get_len_msg_set(uint32_t cmd);

#endif /* MESSAGE_MTSENSOR_MODEL_H__ */