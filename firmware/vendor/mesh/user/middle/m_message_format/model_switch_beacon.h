#ifndef BEACON_LINK_H__
#define BEACON_LINK_H__

#include "nrf_mesh_defines.h"
#include <stdint.h>


typedef struct __attribute((packed))
{
    uint8_t not_used;
} req_get_link_list_t;
typedef struct __attribute((packed))
{
    uint8_t mac[6];
    uint8_t index:4;
    uint8_t enable;
    uint8_t bat;
    uint32_t version;
    uint32_t delay_s;
} rep_get_link_list_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
    uint8_t mac[6];
} rm_link_t;
typedef struct __attribute((packed))
{
    uint8_t uid;
    uint8_t mac[6];
    uint8_t result;
    uint8_t has_a_link;
} rep_rm_link_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
    uint8_t index : 2;
    uint8_t enable : 1;
} req_enable_link_t;
typedef struct __attribute((packed))
{
    uint8_t uid;
    uint8_t index : 2;
    uint8_t enable : 1;
    uint8_t result : 1;
} rep_enable_link_t;

typedef struct __attribute((packed))
{
    uint8_t index;
    uint32_t delay_s;
} set_defer_t;
typedef struct __attribute((packed))
{
    uint32_t delay_s;
    uint8_t index : 2;
    uint8_t result : 1;
} rep_set_defer_t;

typedef struct __attribute((packed))
{
    uint8_t index;
    uint8_t uid;
    uint32_t t_start;
    uint32_t t_end;
} add_alarm_link_t;
typedef struct __attribute((packed))
{
    uint8_t index;
    uint8_t uid;
    uint8_t result;
} rep_add_alarm_link_t;

typedef struct __attribute((packed))
{
    uint8_t index;
    uint8_t uid;
} rm_alarm_link_t;
typedef struct __attribute((packed))
{
    uint8_t index;
    uint8_t uid;
    uint8_t result;
} rep_rm_alarm_link_t;

typedef struct __attribute((packed))
{
    uint8_t index;
} get_list_alarm_t;
typedef struct __attribute((packed))
{
    uint8_t index;
    uint16_t t_start;
    uint16_t t_end;
} rep_get_list_alarm_link_t;

typedef union __attribute((packed))
{
    req_get_link_list_t req_get_list;
    rm_link_t remove_link;
    req_enable_link_t set_enable;
    set_defer_t set_defer;
    add_alarm_link_t add_alarm_link;
    rm_alarm_link_t rm_alarm_link;
    get_list_alarm_t get_list_alarm;
} beacon_msg_set_t;

typedef union __attribute((packed))
{
    rep_get_link_list_t rep_get_link_list;
    rep_rm_link_t rep_remove_link;
    rep_enable_link_t rep_enable_link;
    rep_set_defer_t rep_set_defer;
    rep_add_alarm_link_t rep_add_alarm_link;
    rep_rm_alarm_link_t rep_rm_alarm_link;
    rep_get_list_alarm_link_t rep_get_list_alarm;
} beacon_msg_rep_t;

#endif /* MESSAGE_SWITCH_MODEL_H__ */
