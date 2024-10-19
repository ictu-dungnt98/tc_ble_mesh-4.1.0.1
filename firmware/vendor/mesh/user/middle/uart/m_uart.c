#include <stdint.h>

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"
#include "drivers/8258/gpio_8258.h"
#include "drivers.h"
#include "proj/drivers/uart.h"

#include "vendor/common/system_time.h"

#include "m_uart.h"
#include "vendor/mesh/user/middle/squeue/squeue.h"
#include "vendor/mesh/user/middle/squeue/squeue_tx.h"
#include "vendor/mesh/user/hardware/hardware.h"
#include "vendor/mesh/user/config/app_config.h"

#define UART_MAX_QUEUE_ITEM (45)

static sq_tx_t tx_queue;
static sq_t rx_queue;
static uint8_t g_req_send_sersion = 0;

extern uint8_t esp32_to_mesh_handler(mesh_pkg_t *data);
extern void esp32_to_ble_mcu_handler(gateway_pkg_t *data);

typedef union __attribute((packed))
{
    uint8_t data[4];
    uint32_t fw_version;
} tb03_fw_version_t;

uint8_t reply_get_version_msg(void)
{
    if (g_req_send_sersion)
    {
        uint8_t tx_msg[13];
        tx_msg[0] = 0xFA;
        tx_msg[1] = 0xFB;
        tx_msg[2] = 0xFC;
        tx_msg[3] = 0xFD;
        tx_msg[4] = BLE_MCU_TO_ESP32;

        tb03_fw_version_t tb03_fw_version;
        tb03_fw_version.fw_version = SW_VER_BUILD;

        tx_msg[5] = tb03_fw_version.data[0];
        tx_msg[6] = tb03_fw_version.data[1];
        tx_msg[7] = tb03_fw_version.data[2];
        tx_msg[8] = tb03_fw_version.data[3];

        tx_msg[9] = 0xFA;
        tx_msg[10] = 0xFB;
        tx_msg[11] = 0xFC;
        tx_msg[12] = 0xFD;

        uart_Send((uint8_t *)&tx_msg, 13);

        g_req_send_sersion = 0;

        return 1;
    }

    return 0;
}

uint8_t rx_get_version_msg(uart_message_t rx_data)
{
    uint8_t *p_data = (uint8_t *)&rx_data;

    if (p_data[0] == 0xFA && p_data[1] == 0xFB &&
        p_data[2] == 0xFC && p_data[3] == 0xFD &&
        p_data[4] == ESP32_TO_BLE_MCU &&
        p_data[5] == OPCODE_GATEWAY_GET_VERSION &&
        p_data[6] == 0xFA && p_data[7] == 0xFB &&
        p_data[8] == 0xFC && p_data[9] == 0xFD)
    {
        LOG_USER_MSG_INFO(0, 0, "%s true", __func__);

        g_req_send_sersion = 1;

        return 1;
    }

    return 0;
}

int m_uart_rx_callback(uint8_t *data, size_t size)
{
    LOG_USER_MSG_INFO(data, size, "<<=== uart_rx[%d]", size);

    uart_message_t rx_data;

    if (size <= sizeof(rx_data))
    {
        memset(&rx_data, 0, sizeof(rx_data));
        memcpy(&rx_data, data, size);
        if (sq_push(&rx_queue, &rx_data))
        {
            return 0;
        }
    }

    LOG_USER_MSG_INFO(0, 0, "%s push to rx_queue fail", __func__);
    return -1;
}

int m_uart_send(uart_message_t *tx_data)
{
    uart_Send((uint8_t *)tx_data, sizeof(uart_message_t));
    return 0;
}

int m_uart_send_queue(uart_message_t *tx_data)
{
    LOG_USER_MSG_INFO(0, 0, "%s", __func__);

    if (sq_tx_push(&tx_queue, tx_data))
    {
        return 0;
    }

    LOG_USER_MSG_INFO(0, 0, "%s push to tx_queue fail", __func__);
    return -1;
}

void m_uart_tx_loop(void)
{
    uart_message_t tx_msg;

    static uint32_t time_ms = 0;

    if (sys_get_tick_ms() - time_ms < 100)
    {
        return;
    }
    time_ms = sys_get_tick_ms();

    if (reply_get_version_msg())
    {
        return;
    }

    if (sq_tx_pop(&tx_queue, &tx_msg))
    {
        LOG_USER_MSG_INFO((uint8_t *)&tx_msg, sizeof(tx_msg), "===>> uart_tx[%d]:", sizeof(tx_msg));
        uart_Send((uint8_t *)&tx_msg, sizeof(tx_msg));
    }
}

void m_uart_rx_loop(void)
{
    uart_message_t rx_data;

    if (sq_pop(&rx_queue, &rx_data))
    {
        LOG_USER_MSG_INFO(0, 0, "rx_data.type: %d", rx_data.type);

        if (rx_get_version_msg(rx_data))
        {
            return;
        }

        if (rx_data.type == ESP32_TO_MESH)
        {
            mesh_pkg_t *mesh_data = &rx_data.msg.mesh_pkg;
            esp32_to_mesh_handler(mesh_data);
        }
        else if (rx_data.type == ESP32_TO_BLE_MCU)
        {
            gateway_pkg_t *uart_data = &rx_data.msg.gateway_pkg;
            esp32_to_ble_mcu_handler(uart_data);
        }
    }
}

void m_uart_init(void)
{
    sq_init(&rx_queue, sizeof(uart_message_t), UART_MAX_QUEUE_ITEM);
    sq_tx_init(&tx_queue, sizeof(uart_message_t), 5);
}