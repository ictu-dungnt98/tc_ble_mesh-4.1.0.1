#pragma once

#include <stdint.h>

#include "freertos/semphr.h"

#include "llist.h"
#include "json_key.h"
#include "opcode.h"
#include "app_log.h"
#include "macros.h"
#include "uid_mark.h"
#include "app_tid.h"

#include "hunonic_model_config.h"
#include "hunonic_opcodes.h"
#include "message_switch_model.h"
#include "message_ocsensor_model.h"
#include "message_mtsensor_model.h"
#include "message_smsensor_model.h"
#include "message_common_model.h"
#include "message_time_model.h"

#include "message_gateway.h"

#define DIFF_SEC_1900_1970 ((uint32_t)2208988800L)
#define DIFF_SEC_GMT7 (uint32_t)25200L
#define DIFF_SEC_1900_1970_GMT7 (DIFF_SEC_1900_1970 + DIFF_SEC_GMT7)


#define INFO_API_LOCK(c) xSemaphoreTake(c->mutex, portMAX_DELAY)
#define INFO_API_UNLOCK(c) xSemaphoreGive(c->mutex)

#define _IP2STR(x) (x >> 0) & 0xFF, (x >> 8) & 0xFF, (x >> 16) & 0xFF, (x >> 24) & 0xFF

#define FILE_NAME_RESET_REASON "/spiffs/reset_reason.txt"

#define FILE_NAME_FILEBIN "/spiffs/TBxxOTA.bin"
#define FILE_NAME_NODE_INFO "/spiffs/nodeInfo.bin"

#define FILE_NAME_SCENE_NAME "/spiffs/scene_name.txt"
#define FILE_NAME_SCENE_NODE "/spiffs/scene_node.txt"

#define FILE_NAME_SCENE_NAME_BAK "/spiffs/scene_name.bak"
#define FILE_NAME_SCENE_NODE_BAK "/spiffs/scene_node.bak"

#define FILE_NAME_INFO_SERVER "/spiffs/info_server.txt"
#define FILE_NAME_INDEX_SERVER "/spiffs/index_server.txt"

#define SCENE_NAME_FOMART_LINE "id:%u, name:%s\r\n"

typedef struct
{
    uint32_t len;
    uint8_t data[];
} uint8_arr_t;


typedef enum
{
    MSG_SRC_TCP = (1 << 0),
    MSG_SRC_UDP = (1 << 1),
    MSG_SRC_MQTT = (1 << 2),
    MSG_SRC_UART = (1 << 3),
    MSG_SRC_SELF = (1 << 4),
} msg_src_t;

typedef struct
{
    uint16_t address;
    union
    {
        struct
        {
            uint8_t state;
            uint8_t act_id;
        } state_switch;

        struct
        {
            uint8_t state;
        } state_ocsensor, state_smsensor;

        struct
        {
            uint8_t state;
            uint8_t darkLight;
        } state_mtsensor;
    };
} event_state_t;

bool convert_string2Hex(char *str, uint16_t len, uint8_t *arr);