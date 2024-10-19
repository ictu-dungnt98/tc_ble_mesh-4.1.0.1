#include "proj/tl_common.h"
#if !WIN32
#include "proj/mcu/watchdog_i.h"
#endif
#include "../../proj_lib/ble/ll/ll.h"
#include "../../proj_lib/ble/blt_config.h"
#include "../../vendor/common/user_config.h"
#include "../../proj_lib/sig_mesh/app_mesh.h"

#include "vendor_model_hunonic.h"
#include "vendor/mesh/user/hardware/hardware.h"
#include "vendor/mesh/user/middle/uart/m_uart.h"

#include "vendor/mesh/user/middle/process_data/mesh_tx.h"
#include "vendor/mesh/user/middle/process_data/mesh_tx_cache.h"

uint32_t mesh_md_hunonic_addr = FLASH_ADR_VD_HUNONIC;
model_vd_hunonic_t model_vd_hunonic;

extern void check_rsp_and_clr_cache(mesh_pkg_t *tx_data);
extern int check_ota_state(void);

static int vendor_rx_handle(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
    hw_led_stt_set(LED_ON);

    uart_message_t message;
    mesh_op_resource_t *pRes = (mesh_op_resource_t *)cb_par->res;

    message.type = MESH_TO_ESP32;
    message.msg.mesh_pkg.opcode_mesh = cb_par->op;
    message.msg.mesh_pkg.address = cb_par->adr_src;
    message.msg.mesh_pkg.model_id = (pRes->id >> (pRes->sig ? 0 : 16));
    message.msg.mesh_pkg.len_para = par_len;
    memset(&message.msg.mesh_pkg.para, 0, par_len);
    memcpy(&message.msg.mesh_pkg.para, par, par_len);

    if (message.msg.mesh_pkg.opcode_mesh == 0xD0)
    {
        LOG_USER_MSG_INFO(0, 0,"vendor_rx %s. address: %d", __func__, message.msg.mesh_pkg.address);
        LOG_USER_MSG_INFO(0, 0,"vendor_rx %s. opcode_mesh: %x", __func__, message.msg.mesh_pkg.opcode_mesh);
        LOG_USER_MSG_INFO(0, 0,"vendor_rx %s. model_id: %x", __func__, message.msg.mesh_pkg.model_id);
        LOG_USER_MSG_INFO(0, 0,"vendor_rx %s. par_len: %x", __func__, par_len);
        LOG_USER_MSG_INFO(0, 0,"vendor_rx %s. cmd: %x", __func__, message.msg.mesh_pkg.para.cmd);
    }

    if (check_ota_state() == 0)
    {
        if (message.msg.mesh_pkg.opcode_mesh == 0xD0 &&
            (message.msg.mesh_pkg.para.cmd == SW_REP_SET_COLOR_ON ||
             message.msg.mesh_pkg.para.cmd == SW_REP_SET_COLOR_OFF))
        {
            m_uart_send_queue(&message);
        }
        else
        {
            m_uart_send(&message);
        }
    }

    check_rsp_and_clr_cache(&message.msg.mesh_pkg);

    hw_led_stt_set(LED_OFF);

    return -1;
}

static int common_model_rx_handle(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
    // LOG_USER_MSG_INFO(0, 0,"vendor rx %s", __func__);
    return vendor_rx_handle(par, par_len, cb_par);
}

static int switch_model_rx_handle(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
    // LOG_USER_MSG_INFO(0, 0,"vendor rx %s, address: %u", __func__, cb_par->adr_src);
    return vendor_rx_handle(par, par_len, cb_par);
}

static int ocsensor_model_rx_handle(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
    // LOG_USER_MSG_INFO(0, 0,"vendor rx %s", __func__);
    return vendor_rx_handle(par, par_len, cb_par);
}

static int mtsensor_model_rx_handle(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
    // LOG_USER_MSG_INFO(0, 0,"vendor rx %s", __func__);
    return vendor_rx_handle(par, par_len, cb_par);
}

static int smsensor_model_rx_handle(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
    // LOG_USER_MSG_INFO(0, 0,"vendor rx %s", __func__);
    return vendor_rx_handle(par, par_len, cb_par);
}

static int thsensor_model_rx_handle(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
    // LOG_USER_MSG_INFO(0, 0,"vendor rx %s", __func__);
    return vendor_rx_handle(par, par_len, cb_par);
}

static mesh_cmd_sig_func_t mesh_cmd_hunonic_func[] = {
    {HUNONIC_OPCODE_GATEWAY_COMMON_RX, 1, GATEWAY_COMMON_MODEL_TX, GATEWAY_COMMON_MODEL_RX, common_model_rx_handle, HUNONIC_OPCODE_GATEWAY_COMMON_TX},
    {HUNONIC_OPCODE_GATEWAY_SWITCH_RX, 1, GATEWAY_SWITCH_MODEL_TX, GATEWAY_SWITCH_MODEL_RX, switch_model_rx_handle, HUNONIC_OPCODE_GATEWAY_SWITCH_TX},
    {HUNONIC_OPCODE_GATEWAY_OCSENSOR_RX, 1, GATEWAY_OCSENSOR_MODEL_TX, GATEWAY_OCSENSOR_MODEL_RX, ocsensor_model_rx_handle, HUNONIC_OPCODE_GATEWAY_OCSENSOR_TX},
    {HUNONIC_OPCODE_GATEWAY_MTSENSOR_RX, 1, GATEWAY_MTSENSOR_MODEL_TX, GATEWAY_MTSENSOR_MODEL_RX, mtsensor_model_rx_handle, HUNONIC_OPCODE_GATEWAY_MTSENSOR_TX},
    {HUNONIC_OPCODE_GATEWAY_SMSENSOR_RX, 1, GATEWAY_SMSENSOR_MODEL_TX, GATEWAY_SMSENSOR_MODEL_RX, smsensor_model_rx_handle, HUNONIC_OPCODE_GATEWAY_SMSENSOR_TX},
    {HUNONIC_OPCODE_GATEWAY_THSENSOR_RX, 1, GATEWAY_THSENSOR_MODEL_TX, GATEWAY_THSENSOR_MODEL_RX, thsensor_model_rx_handle, HUNONIC_OPCODE_GATEWAY_THSENSOR_TX},
};

/* PUBLIC APIs. */

int vd_model_hunonic_health_client_callback(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
    // LOG_USER_MSG_INFO(0, 0,"vendor rx %s", __func__);
    LOG_USER_MSG_INFO(0, 0, "=============================", 0);
    LOG_USER_MSG_INFO(0, 0, "vendor health model addr : %u", cb_par->adr_src);
    LOG_USER_MSG_INFO(0, 0, "=============================", 0);
    vendor_rx_handle(par, par_len, cb_par);
    return -1;
}

int vd_model_hunonic_search_model_id_by_op_vendor(mesh_op_resource_t *op_res, u16 op, u8 tx_flag)
{
    LOG_USER_MSG_INFO(0, 0,"Hunonic search model with opcode: 0x%04X", op);

    foreach_arr(i, mesh_cmd_hunonic_func)
    {
        if (op == mesh_cmd_hunonic_func[i].op)
        {
            op_res->cb = mesh_cmd_hunonic_func[i].cb;
            op_res->op_rsp = mesh_cmd_hunonic_func[i].op_rsp;
            op_res->status_cmd = mesh_cmd_hunonic_func[i].status_cmd ? 1 : 0;
            op_res->sig = 0;
            op_res->id = mesh_cmd_hunonic_func[i].model_id_rx;

            LOG_USER_MSG_INFO(0, 0,"Hunonic found model with opcode: 0x%04X", op);
            return 0;
        }
    }

    return -1;
}

int vd_model_hunonic_is_cmd_with_tid(u8 *tid_pos_out, u16 op, u8 tid_pos_vendor_app)
{
    // LOG_MSG_INFO(TL_LOG_COMMON, 0, 0, "Hunonic vd_model TID - op", 0, op);
    return 0;
}