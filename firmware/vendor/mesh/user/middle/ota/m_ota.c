#include "m_ota.h"
#include "vendor/mesh/user/middle/uart/m_uart.h"
#include <stdint.h>
#include "drivers.h"
#include "proj_lib/sig_mesh/app_mesh.h"
#include "m_md5.h"

#define LEN_TO_WRITE 16
#define MD5_LEN 16

typedef enum
{
    WAIT_RSP_RESULT = 0,
    OTA_START_OK,
    OTA_START_FAIL,
    WRITE_DATA_OK,
    WRITE_DATA_FAIL,
    MD5_OK,
    MD5_FAIL
} ota_rsp_t;

static md5_ctx sMD5Ctx;
static uint8_t pui8MD5[MD5_LEN];

static uint8_t is_ota_processing = 0;
static uint32_t g_total_len_written = 0;
static uint32_t g_total_firmware_len = 0;
static uint8_t rx_crc16[16];

extern u32 ota_firmware_size_k;
extern u32 ota_program_offset;
extern int bls_ota_clearNewFwDataArea(int check_only);

int check_ota_state(void)
{
    return is_ota_processing;
}

static int32_t check_file(uint32_t start_addr, uint32_t file_size)
{
    md5_final(pui8MD5, &sMD5Ctx);

    LOG_USER_MSG_INFO(pui8MD5, MD5_LEN, "MD5 output:", 0);
    LOG_USER_MSG_INFO(rx_crc16, MD5_LEN, "MD5 in file:", 0);

    if (memcmp(pui8MD5, rx_crc16, MD5_LEN) == 0)
        return 1;
    else
        return 0;
}

void gateway_update_start(gateway_pkg_t *data)
{
    LOG_USER_MSG_INFO(0, 0, "%s", __func__);

    g_total_len_written = 0;
    memset(rx_crc16, 0, sizeof(rx_crc16));

    g_total_firmware_len = data->data.tb03_ota_start_set.total_len_fw;
    memcpy(rx_crc16, data->data.tb03_ota_start_set.crc16, MD5_LEN);

    LOG_USER_MSG_INFO(0, 0, "g_address_to_write: %d", ota_program_offset);
    LOG_USER_MSG_INFO(0, 0, "g_total_firmware_len/ota_firmware_size_k: %d/%d", g_total_firmware_len, (ota_firmware_size_k << 10));

    bls_ota_clearNewFwDataArea(0);

    uart_message_t tx_msg;
    memset((void *)&tx_msg, 0, sizeof(tx_msg));
    tx_msg.type = BLE_MCU_TO_ESP32;
    tx_msg.msg.gateway_pkg.cmd = OPCODE_GATEWAY_REP_TB03_OTA_START;
    if ((ota_firmware_size_k << 10) > g_total_firmware_len)
    {
        tx_msg.msg.gateway_pkg.data.tb03_ota_start_rep.result = OTA_START_OK;
        md5_init(&sMD5Ctx);
    }
    else
    {
        tx_msg.msg.gateway_pkg.data.tb03_ota_start_rep.result = OTA_START_FAIL;
    }
    m_uart_send(&tx_msg);
}

void gateway_update_write_fw(gateway_pkg_t *data)
{
    uint8_t result = WRITE_DATA_OK;
    uart_message_t tx_msg;

    uint32_t new_offset = data->data.tb03_ota_data_set.offset;
    uint32_t len_fw = data->data.tb03_ota_data_set.len;
    uint8_t *p_new_fw = data->data.tb03_ota_data_set.data;

    uint32_t addr_to_write = ota_program_offset + new_offset;
    uint32_t len_to_write = LEN_TO_WRITE;
    uint32_t len_written = 0;

    static uint32_t old_offset = 0;
    uint8_t avaliable_write = 0;

    // LOG_USER_MSG_INFO(0, 0, "%s new_offset: %d", __func__, new_offset);

    /* if esp32 does not receive respond from tb03, it will resend data at old offset.
    tb03 does not need re-write those data again.*/
    if (old_offset == 0 || old_offset != new_offset)
    {
        old_offset = new_offset;
        avaliable_write = 1;
    }
    else
    {
        LOG_USER_MSG_INFO(0, 0, " old offsset. Do not need write", 0);
    }

    if (avaliable_write)
    {
        if ((g_total_len_written + len_fw) > g_total_firmware_len)
        {
            LOG_USER_MSG_INFO(0, 0, "%s: Total len write was invalid: %d/%d", __func__, (g_total_len_written + len_fw), g_total_firmware_len);
            bls_ota_clearNewFwDataArea(0);
            result = WRITE_DATA_FAIL;
            goto _write_fw_exit;
        }

        if ((g_total_len_written + len_fw) > (ota_firmware_size_k << 10))
        {
            LOG_USER_MSG_INFO(0, 0, "%s: Firmware size is too big: %d/%d", __func__, g_total_len_written + len_fw, (ota_firmware_size_k << 10));
            bls_ota_clearNewFwDataArea(0);
            result = WRITE_DATA_FAIL;
            goto _write_fw_exit;
        }

        if (len_fw > TB03_FW_SEGMENT_SIZE)
        {
            LOG_USER_MSG_INFO(0, 0, "%s: Len_fw was invalid: %d/%d", __func__, len_fw, TB03_FW_SEGMENT_SIZE);
            bls_ota_clearNewFwDataArea(0);
            result = WRITE_DATA_FAIL;
            goto _write_fw_exit;
        }

        do
        {
            if ((addr_to_write + len_to_write) > (ota_program_offset + (ota_firmware_size_k << 10)))
            {
                /* overwrite */
                LOG_USER_MSG_INFO(0, 0, "%s: Firmware overwrite", __func__);
                result = WRITE_DATA_FAIL;
                bls_ota_clearNewFwDataArea(0);
                goto _write_fw_exit;
            }
            else
            {
                flash_write_page(addr_to_write, len_to_write, &p_new_fw[len_written]);
                addr_to_write += len_to_write;
                len_written += len_to_write;

                if ((len_fw - len_written) < 16)
                {
                    len_to_write = (len_fw - len_written);
                }
            }

        } while (len_written < len_fw);

        /* confirm write */
        uint8_t verify[TB03_FW_SEGMENT_SIZE];
        memset(&verify, 0xFF, sizeof(verify));
        flash_read_page((ota_program_offset + new_offset), len_fw, verify);

        if (memcmp(data->data.tb03_ota_data_set.data, verify, len_fw) != 0)
        {
            LOG_USER_MSG_INFO(0, 0, "%s write flash fail", __func__);
            result = WRITE_DATA_FAIL;
            bls_ota_clearNewFwDataArea(0);
        }
        else
        {
            result = WRITE_DATA_OK;
            g_total_len_written += len_fw;
            LOG_USER_MSG_INFO(0, 0, "g_total_len_written: %d/%d", g_total_len_written, g_total_firmware_len);

            /* update MD5 result */
            md5_update(&sMD5Ctx, (uint8_t *)verify, len_fw);
        }
    }

_write_fw_exit:
    /* respond */
    // LOG_USER_MSG_INFO(0, 0, "write respond result: %d", result);

    memset((void *)&tx_msg, 0, sizeof(tx_msg));
    tx_msg.type = BLE_MCU_TO_ESP32;
    tx_msg.msg.gateway_pkg.cmd = OPCODE_GATEWAY_REP_TB03_OTA_DATA;
    tx_msg.msg.gateway_pkg.data.tb03_ota_data_rep.result = result;
    tx_msg.msg.gateway_pkg.data.tb03_ota_data_rep.offset = new_offset;
    m_uart_send(&tx_msg);
}

void gateway_update_check_md5(gateway_pkg_t *data)
{
    LOG_USER_MSG_INFO(0, 0, "%s", __func__);

    uint8_t result = MD5_FAIL;

    if (g_total_firmware_len != g_total_len_written)
    {
        LOG_USER_MSG_INFO(0, 0, "%s: %d/%d", __func__, g_total_len_written, g_total_firmware_len);
        LOG_USER_MSG_INFO(0, 0, "TB03 OTA Fail", __func__);
        bls_ota_clearNewFwDataArea(0);
    }
    else
    {
        if (check_file(ota_program_offset, g_total_firmware_len) == 1)
        {
            LOG_USER_MSG_INFO(0, 0, "%s Check MD5 OK", __func__);
            result = MD5_OK;

            u32 flag = 0x4B;
            flash_write_page(ota_program_offset + 8, 1, (u8 *)&flag);
            flag = 0x00;
            flash_write_page((ota_program_offset ? 0 : 0x40000) + 8, 4, (u8 *)&flag);
        }
        else
        {
            LOG_USER_MSG_INFO(0, 0, "%s MD5 error", __func__);
            bls_ota_clearNewFwDataArea(0);
        }
    }

    /* respond */
    uart_message_t tx_msg;
    memset((void *)&tx_msg, 0, sizeof(tx_msg));
    tx_msg.type = BLE_MCU_TO_ESP32;
    tx_msg.msg.gateway_pkg.cmd = OPCODE_GATEWAY_REP_TB03_CHECK_MD5;
    tx_msg.msg.gateway_pkg.data.tb03_ota_data_rep.result = result;
    m_uart_send(&tx_msg);
}

void gateway_update_end(gateway_pkg_t *data)
{
    irq_disable();
    start_reboot();
}
