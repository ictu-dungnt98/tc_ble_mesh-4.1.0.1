#ifndef MESSAGE_GATEWAY_H__
#define MESSAGE_GATEWAY_H__

#include <stdint.h>

#define MESH_KEY_SZIE   (16)
#define MESH_UUID_SIZE (16)
#define MESH_UNPROV_URI_SIZE (4)
#define TB03_FW_SEGMENT_SIZE (128)

typedef enum
{
    OPCODE_GATEWAY_SET_INVALID,
    OPCODE_GATEWAY_SET_PROV_GW,
    OPCODE_GATEWAY_SET_RM_GW,
    OPCODE_GATEWAY_SET_TB03_OTA_START,
    OPCODE_GATEWAY_SET_TB03_OTA_DATA,
    OPCODE_GATEWAY_SET_TB03_CHECK_MD5,
    OPCODE_GATEWAY_SET_TB03_OTA_END,
    OPCODE_GATEWAY_GET_VERSION,
    OPCODE_GATEWAY_GET_MESH_INFO,
    OPCODE_GATEWAY_KICKOUT_MESH,
} opcode_gateway_set_t;

typedef enum
{
    OPCODE_GATEWAY_REP_INVALID,
    OPCODE_GATEWAY_REP_PROV_GW,
    OPCODE_GATEWAY_REP_RM_GW,
    OPCODE_GATEWAY_REP_TB03_OTA_START,
    OPCODE_GATEWAY_REP_TB03_OTA_DATA,
    OPCODE_GATEWAY_REP_TB03_CHECK_MD5,
    OPCODE_GATEWAY_REP_VERSION,
    OPCODE_GATEWAY_REP_MESH_INFO,
} opcode_gateway_rep_t;

/* format message set. */
typedef struct __attribute((packed))
{
    uint8_t netkey[MESH_KEY_SZIE];
    uint8_t appkey[MESH_KEY_SZIE];
    uint16_t device_addr;
} gateway_set_prov_gw_t;

typedef struct __attribute((packed))
{
    uint8_t result;
} gateway_rep_prov_gw_t;

typedef struct __attribute((packed))
{
    uint16_t address;
} gateway_set_rm_gw_t;

typedef struct __attribute((packed))
{
    uint16_t result;
    uint16_t address;
} gateway_rep_rm_gw_t;

typedef struct __attribute((packed))
{
    uint32_t major;
    uint32_t minor;
    uint32_t path;
    uint32_t build;
} gw_ble_version_t;

typedef struct __attribute((packed))
{
    uint8_t uid;
} gateway_get_version_t;

typedef struct __attribute((packed))
{
    gw_ble_version_t sw;
    gw_ble_version_t hw;
} gateway_rep_version_t;

typedef struct __attribute((packed))
{
    uint32_t total_len_fw;
    uint8_t crc16[16];
} tb03_ota_start_t;

typedef struct __attribute((packed))
{
    uint8_t result;
    uint32_t total_len_fw;
} tb03_ota_start_rep_t;

typedef struct __attribute((packed))
{
    uint32_t offset;
    uint32_t len;
    uint8_t data[TB03_FW_SEGMENT_SIZE];
} tb03_ota_data_t;

typedef struct __attribute((packed))
{
    uint8_t result;
    uint32_t offset;
} tb03_ota_data_rep_t;

typedef struct __attribute((packed))
{
    uint8_t unused;
} gateway_get_mesh_info_t;

typedef struct __attribute((packed))
{
    uint8_t netkey[17];
    uint8_t appkey[17];
    uint32_t iv_cur;
    uint32_t iv_tx;
    uint32_t iv_rx;
} gateway_rep_mesh_info_t;

#endif /* MESSAGE_GATEWAY_H__ */