#ifndef MESSAGE_SMSENSOR_MODEL_H__
#define MESSAGE_SMSENSOR_MODEL_H__


#include "nrf_mesh_defines.h"
#include "model_sensor_th.h"

enum SMSENSOR_msg_set_type_t
{
    SMSENSOR_SET_TYPE_NOT_SUPPORT = 0,
    SMSENSOR_SET_TYPE_GET_INFO, /* not used */
    SMSENSOR_SET_TYPE_GET_INFO_HAVE_INTERNET, /* not used */
    SMSENSOR_SET_TYPE_SET_INTERVAL_WAKEUP, /* not used */
    SMSENSOR_SET_TYPE_SET_THRESHOLD_ALARM,

    THSENSOR_SET_TYPE_GET_INFO = 0x20,
    THSENSOR_SET_TYPE_GET_INFO_HAVE_INTERNET, /* not used */
};

enum SMSENSOR_msg_rep_type_t
{
    SMSENSOR_REP_TYPE_NOT_SUPPORT = 0,        /* not support. */
    SMSENSOR_REP_TYPE_REP_STATE,              /* reply state. */
    SMSENSOR_REP_TYPE_REP_INFO,               /* reply device. */
    SMSENSOR_REP_TYPE_REP_INFO_HAVE_INTERNET, /* reply info when gateway have internet. */
    SMSENSOR_REP_TYPE_REP_INTERVAL_WAKEUP,    /* reply intervel device wakeup. */
    SMSENSOR_REP_TYPE_DEBUG_MEASEURE_ADC,     /* reply debug adc measure. */
    SMSENSOR_REP_TYPE_SET_THRESHOLD_ALARM,    /* reply threshold smoke alarm. */

    /* temperature sensor */
    THSENSOR_REP_TYPE_REP_INFO = 0x20,        /* reply device. */
    THSENSOR_REP_TYPE_REP_INFO_HAVE_INTERNET, /* reply info when gateway have internet. */
    THSENSOR_REP_TYPE_REP_STATE,              /* reply state thsensor. */
};

typedef struct __attribute((packed))
{
    uint16_t threshold;
} smsensor_msg_threshold_smoke_t;

typedef struct __attribute((packed))
{
    uint16_t after;
    uint16_t before;
} smsensor_msg_debug_measure_adc_t;

typedef struct __attribute((packed))
{
    uint8_t battery_percent : 7; /* battery helth. 0-100% */
    uint8_t warning : 1;         /* warning level */
    uint8_t is_change_state;
} smsensor_msg_state_t;

typedef struct __attribute((packed))
{
    uint8_t battery_percent : 7; /* battery helth. 0-100% */
    uint8_t warning : 1;         /* warning level */
    uint32_t sw_version;
    uint32_t hw_version;
    uint16_t threshold;
} smsensor_msg_info_t;

typedef union __attribute((packed))
{
    smsensor_msg_threshold_smoke_t set_threshold;
} smsensor_msg_set_t;

typedef union __attribute((packed))
{
    /* smoke sensor */
    smsensor_msg_info_t info;
    smsensor_msg_state_t state;
    smsensor_msg_threshold_smoke_t threshold;
    smsensor_msg_debug_measure_adc_t measure_adc;
    /* temperature huminity sensor */
    thsensor_msg_state_t thsensor_state;
    thsensor_msg_info_t thsensor_info;
} smsensor_msg_rep_t;

uint32_t smsensor_get_len_msg_set(uint32_t type);

#endif /* MESSAGE_SMSENSOR_MODEL_H__ */