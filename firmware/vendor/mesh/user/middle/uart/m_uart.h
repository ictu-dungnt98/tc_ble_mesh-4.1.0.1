#ifndef _M_UART_H_
#define _M_UART_H_

#include <stdint.h>
#include "vendor/mesh/user/middle/process_data/gateway_data.h"
#include "vendor/mesh/user/middle/m_message_format/model_switch.h"
#include "vendor/mesh/user/middle/m_message_format/model_common.h"
#include "vendor/mesh/user/middle/m_message_format/model_sensor_sm.h"
#include "vendor/mesh/user/middle/m_message_format/model_sensor_oc.h"
#include "vendor/mesh/user/middle/m_message_format/model_sensor_mt.h"
#include "vendor/mesh/user/middle/m_message_format/model_sensor_th.h"

#define RETRY_MSG_MESH 10
#define RESEND_TIME_MAX 2000
#define RESEND_TIME_MIN 200

typedef enum
{
    OPCODE_UART_INVALID = 0,
    ESP32_TO_MESH = 10,
    MESH_TO_ESP32 = 11,
    ESP32_TO_BLE_MCU = 20,
    BLE_MCU_TO_ESP32 = 21,
    TCP_TO_ESP32 = 22,
    ESP32_to_TCP = 23,
    MQTT_TO_ESP32 = 24,
    ESP32_TO_MQTT = 25,
} msg_type_t;

#define MAX_LEN_MESH_PKG 64
#define MAX_LEN_UART_PKG 64

typedef union __attribute((packed))
{
    switch_msg_set_t sw_msg_set;
    switch_msg_rep_t sw_msg_rep;
    common_msg_set_t common_msg_set;
    common_msg_rep_t common_msg_rep;
    smsensor_msg_set_t smsensor_msg_set;
    smsensor_msg_rep_t smsensor_msg_rep;
    ocsensor_msg_set_t ocsensor_msg_set;
    ocsensor_msg_rep_t ocsensor_msg_rep;
    mtsensor_msg_set_t mtsensor_msg_set;
    mtsensor_msg_rep_t mtsensor_msg_rep;
} mesh_para_t;


typedef struct __attribute((packed))
{
    uint8_t cmd;
    mesh_para_t data; /* maximun 7 bytes */
} mesh_parameter_t;   /* maximun 8 bytes */

typedef struct __attribute((packed))
{
    uint16_t address;
    uint16_t model_id;
    uint16_t opcode_mesh;
    uint8_t len_para;
    mesh_parameter_t para; /* maximun 8 bytes */
} mesh_pkg_t;

typedef union __attribute((packed))
{
    /* esp32 to tb03 */
    gateway_set_prov_gw_t prov_gw_set;
    gateway_set_rm_gw_t rm_gw_set;
    tb03_ota_start_t tb03_ota_start_set;
    tb03_ota_data_t tb03_ota_data_set;
    gateway_get_version_t tb03_get_version;
    gateway_get_mesh_info_t gateway_get_mesh_info;

    /* tb03 to esp32 */
    gateway_rep_prov_gw_t prov_gw_rep;
    gateway_rep_rm_gw_t rm_gw_rep;
    tb03_ota_start_rep_t tb03_ota_start_rep;
    tb03_ota_data_rep_t tb03_ota_data_rep;
    gateway_rep_version_t tb03_version_rep;
    gateway_rep_mesh_info_t gateway_rep_mesh_info;
} gateway_msg_t;


typedef struct __attribute((packed))
{
    uint16_t cmd;
    gateway_msg_t data;
} gateway_pkg_t;

typedef union __attribute((packed))
{
    mesh_pkg_t mesh_pkg;
    gateway_pkg_t gateway_pkg;
} msg_t;

typedef struct __attribute((packed))
{
    uint16_t type; /* reference to enum msg_type_t */
    msg_t msg;
} uart_message_t;

void m_uart_init(void);
int m_uart_send(uart_message_t *tx_data);
int m_uart_send_queue(uart_message_t *tx_data);

void m_uart_tx_loop(void);
void m_uart_rx_loop(void);

#endif