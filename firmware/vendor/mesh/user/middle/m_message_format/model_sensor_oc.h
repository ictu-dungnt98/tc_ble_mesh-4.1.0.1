#ifndef MESSAGE_OCSENSOR_MODEL_H__
#define MESSAGE_OCSENSOR_MODEL_H__


#include "nrf_mesh_defines.h"

enum ocsensor_msg_set_type_t
{
    OCSENSOR_SET_TYPE_NOT_SUPPORT = 0,        /* not support. */
    OCSENSOR_SET_TYPE_GET_INFO,               /* get info device. */
    OCSENSOR_SET_TYPE_GET_INFO_HAVE_INTERNET, /* get info when gateway have internet. */
    OCSENSOR_SET_TYPE_SET_INTERVAL_WAKEUP,    /* set intervel device wakeup. */
};

enum ocsensor_msg_rep_type_t
{
    OCSENSOR_REP_TYPE_NOT_SUPPORT = 0,        /* not support. */
    OCSENSOR_REP_TYPE_REP_STATE,              /* reply state. */
    OCSENSOR_REP_TYPE_REP_INFO,               /* reply device. */
};

enum ocsensor_msg_interval_wakeup_t
{
    OCSENSOR_INTERVAL_2S,
    OCSENSOR_INTERVAL_3S,
    OCSENSOR_INTERVAL_5S,
    OCSENSOR_INTERVAL_7S,
    OCSENSOR_INTERVAL_12S,
    OCSENSOR_INTERVAL_17S,
    OCSENSOR_INTERVAL_28S,
};

typedef struct __attribute((packed))
{
    uint8_t state;
    uint8_t battery_percent;
    uint8_t is_change_state;
} ocsensor_msg_state_t;

typedef struct __attribute((packed))
{
    uint8_t interval;
} ocsensor_msg_set_interval_wakeup_t;

typedef struct __attribute((packed))
{
    uint8_t state;
    uint8_t battery_percent;
    uint8_t interval;
    uint32_t sw_ver;
    uint32_t hw_ver;
} ocsensor_msg_info_t;

typedef union __attribute((packed))
{
    ocsensor_msg_set_interval_wakeup_t interval;
} ocsensor_msg_set_t;

typedef union __attribute((packed))
{
    ocsensor_msg_state_t state;
    ocsensor_msg_info_t info;
} ocsensor_msg_rep_t;

uint32_t get_len_ocsensor_msg_set_by_cmd(uint32_t cmd);

#endif /* MESSAGE_OCSENSOR_MODEL_H__ */