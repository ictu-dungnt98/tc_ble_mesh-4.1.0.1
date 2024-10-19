#ifndef MESSAGE_COMMON_MODEL_H__
#define MESSAGE_COMMON_MODEL_H__

#include <stdint.h>

typedef enum
{
    COMMON_REMOVE_NODE,
    COMMON_UPDATE_TIMESTAMP,
    COMMON_LPN_ENTER_DFU,
    COMMON_PING_ALL_NODE,
    COMMON_REQ_GET_STATE,
    COMMON_REQ_GET_INFO,
    COMMON_REQ_RESET_DEVICE,
} common_model_set_t;

typedef enum
{
    COMMON_REMOVE_NODE_REP,
} common_model_rep_t;

enum add_node_status_t
{
    ADD_NODE_STATUS_FALSE = 0,
    ADD_NODE_STATUS_SUCCESS,
};

typedef struct __attribute((packed))
{
    uint32_t timestamp;
} update_time_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
    uint32_t address;
} remove_node_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
} get_state_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
} get_info_t;

typedef union __attribute((packed))
{
    update_time_t update_time;
    remove_node_t remove_node;
    get_state_t get_state;
    get_info_t get_info;
} common_msg_set_t;

typedef union __attribute((packed))
{
    uint8_t uid;
} common_msg_rep_t;

uint32_t com_get_len_msg_set_by_cmd(uint32_t type);

#endif /* MESSAGE_COMMON_MODEL_H__ */