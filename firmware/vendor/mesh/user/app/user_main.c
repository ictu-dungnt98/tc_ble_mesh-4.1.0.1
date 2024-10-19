#include "vendor/common/mesh_node.h"
#include "vendor/mesh/user/config/app_config.h"
#include "vendor/mesh/user/hardware/hardware.h"
#include "vendor/mesh/user/middle/uart/m_uart.h"
#include "vendor/mesh/user/middle/process_data/gateway_data.h"
#include "vendor/mesh/user/middle/process_data/mesh_data.h"

#include "vendor/mesh/user/middle/process_data/mesh_tx.h"
#include "vendor/mesh/user/middle/process_data/mesh_tx_cache.h"

extern void gateway_report_version(gateway_pkg_t *data);

void user_main_init(void)
{
    printf("Start project HomeServer TB04");
    
    extern u8 tbl_mac[6];
    (void)tbl_mac;    
    LOG_USER_MSG_INFO(tbl_mac, 6, "%s MAC Address: ", __func__);
    LOG_USER_MSG_INFO(0, 0, "Device is %s", is_provision_success() ? "provision success" : "unprovision");
    
    extern u32 ota_program_offset;
    (void)ota_program_offset;
    LOG_USER_MSG_INFO(0, 0, "Hello from app_hs_init(): 0x%02X", ota_program_offset);

    /* led stt */
    hw_led_stt_init();
    
    /* uart */
    m_uart_init();

    /* send version to esp32 */
    gateway_report_version(NULL);

    cache_msg_init();
    mesh_tx_data_init();
}

void user_main_loop(void)
{
    m_uart_tx_loop();
    m_uart_rx_loop();
    cache_msg_resend_loop();
    mesh_tx_data_loop();
}
