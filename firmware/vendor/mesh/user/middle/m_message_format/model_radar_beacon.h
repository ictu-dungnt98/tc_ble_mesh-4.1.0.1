#ifndef RADAR_BEACON_H__
#define RADAR_BEACON_H__

#include "proj/tl_common.h"
#if !WIN32
#include "proj/mcu/watchdog_i.h"
#endif
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/ble/blt_config.h"
#include "vendor/common/user_config.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#define RADAR_ID_LEN    32

typedef struct __attribute((packed)){
    uint8_t uid;
    uint8_t radar_mac[6];
    uint8_t radar_id[32];
} req_link_radar_t;
typedef struct __attribute((packed)){
    uint8_t uid;
    uint8_t result;
} rep_link_radar_t;

typedef struct __attribute((packed)){
    uint8_t uid;
} req_rm_radar_t;
typedef struct __attribute((packed)){
    uint8_t uid;
    uint8_t result;
} rep_rm_radar_t;

typedef struct __attribute((packed)){
    uint8_t uid;
} req_info_radar_t;
typedef struct __attribute((packed)){
    uint8_t uid;
    uint8_t enable;
    uint32_t t_fan;
    uint8_t radar_id[RADAR_ID_LEN];
} rep_info_radar_t;

typedef struct __attribute((packed)){
    uint8_t uid;
    uint8_t enable;
} req_set_radar_enable_t;
typedef struct __attribute((packed)){
    uint8_t result;
    uint8_t uid;
    uint8_t enable;
} rep_set_radar_enable_t;

typedef struct __attribute((packed)){
    uint8_t uid;
    uint32_t t_fan;
} req_set_defer_radar_t;
typedef struct __attribute((packed)){
    uint8_t result;
    uint8_t uid;
    uint32_t t_fan;
} rep_set_defer_radar_t;

typedef union __attribute((packed))
{
    req_link_radar_t req_link_radar;
    req_rm_radar_t req_rm_radar;
    req_info_radar_t req_info_radar;
    req_set_radar_enable_t req_set_radar_enable;
    req_set_defer_radar_t req_set_defer_radar;
} radar_msg_set_t;

typedef union __attribute((packed))
{
    rep_link_radar_t rep_link_radar;
    rep_rm_radar_t rep_rm_radar;
    rep_info_radar_t rep_info_radar;
    rep_set_radar_enable_t rep_set_radar_enable;
    rep_set_defer_radar_t rep_set_defer_radar;
} radar_msg_rep_t;


#endif /* MESSAGE_SWITCH_MODEL_H__ */
