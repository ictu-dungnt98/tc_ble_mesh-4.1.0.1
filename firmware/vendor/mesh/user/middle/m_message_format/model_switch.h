#ifndef MESSAGE_SWITCH_MODEL_H__
#define MESSAGE_SWITCH_MODEL_H__

#include "nrf_mesh_defines.h"
#include "vendor/mesh/user/middle/m_message_format/model_switch_beacon.h"
#include "vendor/mesh/user/middle/m_message_format/model_radar_beacon.h"

enum act_id_t
{
    ACT_ID_USER = 0,
    ACT_ID_BUTTON = 1,
    ACT_ID_LOOP_TIMER = 2,
    ACT_ID_PRESS_MODE = 3,
    ACT_ID_ALARM = 4,
    ACT_ID_LINKED_SCENE = 5,
    ACT_ID_CONDITION_SCENE = 6,
    ACT_ID_LEAKAGE_CURRENT = 7,
    ACT_ID_LINK_CBCT = 19,
};

enum po_type_t
{
    PO_TYPE_SET_LAST_SATE,
    PO_TYPE_SET_ON,
    PO_TYPE_SET_OFF,
};

enum pressMode_t
{
    PRESS_MODE_OFF,
    PRESS_MODE_WHEN_ON,
    PRESS_MODE_WHEN_OFF,
    PRESS_MODE_WHEN_ON_OFF,
};

enum switch_msg_set_type_t
{
    SW_REQ_SET_NOT_SUPPORT,
    SW_REQ_GET_INFO,
    SW_REQ_SET_STATE,
    SW_REQ_GET_STATE, /* not used. move get state to common model */
    SW_REQ_SET_PO,
    SW_REQ_SET_CHILD_LOCK,
    SW_REQ_SET_PRESS_MODE,
    SW_REQ_GET_PRESS_MODE,
    SW_REQ_SET_LOOP_TIMER,
    SW_REQ_DEL_LOOP_TIMER,
    SW_REQ_SET_COLOR_ON,
    SW_REQ_SET_COLOR_OFF,
    SW_REQ_GET_COLOR,
    SW_REQ_SET_BRIGTHNESS,
    SW_REQ_GET_BRIGTHNESS,
    SW_REQ_ENABLE_PROXY,
    /* beacon_link from hs to switch */
    BEACON_REQ_GET_LIST_LINK,
    BEACON_REQ_REMOVE_LINK,
    BEACON_REQ_ENABLE_LINK,
    BEACON_REQ_SET_DEFER,
    BEACON_REQ_ADD_ALARM_LINK,
    BEACON_REQ_RM_ALARM_LINK,
    BEACON_REQ_GET_ALARM_LINK,
    /* radar */
    REQ_LINK_RADAR,
    REQ_REMOVE_RADAR,
    REQ_INFO_RADAR,
    REQ_SET_RADAR_DEFER,
    REQ_SET_RADAR_ENABLE,
};

enum switch_msg_rep_type_t
{
    SW_REQ_REP_NOT_SUPPORT,
    SW_REP_SET_STATE,
    SW_REP_GET_STATE,
    SW_REP_GET_INFO_1,
    SW_REP_GET_INFO_2,
    SW_REP_SET_PO,
    SW_REP_SET_CHILD_LOCK,
    SW_REP_SET_PRESS_MODE,
    SW_REP_GET_PRESS_MODE,
    SW_REP_SET_LOOP_TIMER,
    SW_REP_DEL_LOOP_TIMER,
    SW_REP_SET_COLOR_ON,
    SW_REP_SET_COLOR_OFF,
    SW_REP_SET_BRIGHTNESS,
    SW_REP_GET_BRIGHTNESS,
    SW_REP_ENABLE_PROXY,
    /* beacon_link from switch to hs */
    BEACON_REP_GET_LIST,
    BEACON_REP_REMOVE_LINK,
    BEACON_REP_ENABLE_LINK,
    BEACON_REP_SET_DEFER,
    BEACON_REP_ADD_ALARM_LINK,
    BEACON_REP_RM_ALARM_LINK,
    BEACON_REP_GET_ALARM_LINK,
    /* radar */
    REP_LINK_RADAR,
    REP_REMOVE_RADAR,
    REP_INFO_RADAR,
    REP_SET_RADAR_DEFER,
    REP_SET_RADAR_ENABLE,
};

/* ======== INFO ========= */
typedef struct __attribute((packed))
{
    uint8_t uid;
    uint8_t channel; // bit mask channel
    uint8_t state;   // bit mask state
} switch_msg_child_lock_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
    uint8_t channel_num;
    uint8_t state : 4;
    uint8_t child_lock : 4;
    uint8_t po;
} switch_msg_info_1_t;

typedef struct __attribute((packed))
{
    uint32_t sw_version;
    // uint32_t hw_version;
} switch_msg_info_2_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
} switch_msg_get_info_t;

/* ======== STATE ========= */
typedef struct __attribute((packed))
{
    uint8_t tid;
    uint8_t uid;
    uint8_t channel_change : 4; /* switch channel change. use for automation detect pin change state */
    uint8_t channel_num : 4;    /* switch channel number. */
    uint8_t state;              /* switch state. */
    uint8_t action_id;          /* @See: act_id_t. */
    uint8_t is_link;
} switch_msg_state_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
} switch_msg_get_state_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
    uint8_t po; /* set power on state @see: po_type_t. */
} switch_msg_po_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
    uint8_t index;
    uint8_t mode;
    uint32_t second;
} switch_msg_press_mode_t;

typedef struct __attribute((packed))
{
    uint8_t result;
} switch_msg_rep_test_leakage_t;

/* ====== Loop Timer ====== */
typedef struct __attribute((packed))
{
    uint8_t tid;
    uint8_t uid;
    uint8_t action;
    uint16_t t_ac1;
    uint16_t t_c;
} switch_msg_set_loop_timer_t;

typedef struct __attribute((packed))
{
    uint8_t tid;
    uint8_t uid;
    uint8_t index;
} switch_msg_del_loop_timer_t;

typedef struct __attribute((packed))
{
    uint8_t tid;
    uint8_t uid;
    uint8_t index;
    uint8_t result;
} switch_msg_rep_loop_timer_t;

/* ======= Color ====== */
typedef struct __attribute((packed))
{
    uint8_t uid;
    uint32_t color;
} switch_msg_set_color_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
} switch_msg_get_color_t;

/* ======= Brigthness ====== */
typedef struct __attribute((packed))
{
    uint8_t uid;
    struct __attribute((packed))
    {
        uint8_t hr;
        uint8_t min;
        uint8_t brigthness;
    } day;

    struct __attribute((packed))
    {
        uint8_t hr;
        uint8_t min;
        uint8_t brigthness;
    } night;
} switch_msg_set_brigthness_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
} switch_msg_get_brigthness_t;

typedef struct __attribute((packed))
{
    uint8_t is_enable;
} sw_set_enalbe_proxy_t;
typedef struct __attribute((packed))
{
    uint8_t is_enable;
    uint8_t result;
} sw_rep_enalbe_proxy_t;

/*****************************************************************************
 * Switch msg set, rep.
 *****************************************************************************/

typedef union __attribute((packed))
{
    switch_msg_get_info_t get_info;
    switch_msg_state_t set_state;
    // switch_msg_get_state_t get_state; /* not used. get state from common model */
    switch_msg_po_t set_po;    
    switch_msg_child_lock_t set_childLock;
    switch_msg_press_mode_t set_press_mode;
    switch_msg_press_mode_t get_press_mode;
    switch_msg_set_loop_timer_t set_loop_timer;
    switch_msg_del_loop_timer_t del_loop_timer;
    switch_msg_set_color_t set_color_on;
    switch_msg_set_color_t set_color_off;
    switch_msg_get_color_t get_color;
    switch_msg_set_brigthness_t set_brigthness;
    switch_msg_get_brigthness_t get_brigthness;
    sw_set_enalbe_proxy_t set_enalbe_proxy;

    /* beacon_link */
    beacon_msg_set_t  beacon_link_set;
    radar_msg_set_t radar_msg_set;
} switch_msg_set_t;

typedef union __attribute((packed))
{
    switch_msg_info_1_t info1;
    switch_msg_info_2_t info2;
    switch_msg_state_t state;
    switch_msg_po_t set_po;
    switch_msg_child_lock_t set_childLock;
    switch_msg_press_mode_t press_mode;
    switch_msg_rep_loop_timer_t loop_timer;
    switch_msg_set_color_t set_color_on;
    switch_msg_set_color_t set_color_off;
    switch_msg_set_brigthness_t set_brigthness;
    sw_rep_enalbe_proxy_t rep_enable_proxy;

    /* beacon_link */
    beacon_msg_rep_t  beacon_link_rep;
    radar_msg_rep_t radar_msg_rep;
} switch_msg_rep_t;

#endif /* MESSAGE_SWITCH_MODEL_H__ */
