#include "gateway_data.h"

#include "vendor/mesh/user/config/app_config.h"
#include "vendor/mesh/user/middle/uart/m_uart.h"
#include "vendor/mesh/user/middle/uart/utility.h"
#include "vendor/mesh/user/middle/ota/m_ota.h"
#include "vendor/mesh/user/middle/mesh_model/vendor_model_hunonic.h"
#include "vendor/mesh/user/middle/mesh_model/hunonic_model_config.h"
#include "vendor/mesh/user/middle/mesh_provision/ble_config.h"

#include "../../vendor/common/app_provison.h"
#include "../../vendor/common/mesh_node.h"

typedef struct
{
    uint16_t vendor;
    uint16_t model_id;
    uint16_t address;
} m_model_id_t;

typedef struct
{
    uint16_t cmd;
    void (*callback)(gateway_pkg_t *);
} m_gateway_handler_t;

void show_mesh_info(void);

void gateway_provisioning(gateway_pkg_t *data)
{
    LOG_USER_MSG_INFO(0, 0, "%s", __func__);
    LOG_USER_MSG_INFO(data->data.prov_gw_set.netkey, 16, "netkey: ", 0);
    LOG_USER_MSG_INFO(data->data.prov_gw_set.appkey, 16, "appkey: ", 0);
    LOG_USER_MSG_INFO(0, 0, "address: %d", data->data.prov_gw_set.device_addr);

    m_model_id_t model_sub_list[] = {
        {0x0000, 0x0002, 0x0000},                                                                         // health server
        {0x0000, 0x0003, SUB_GROUP_ADDRESS_GATEWAY_HEALTH_NODE},                                          // health client
        {ACCESS_COMPANY_ID_HUNONIC, COMMON_MODEL_ID_GATEWAY, SUB_GROUP_ADDRESS_GATEWAY_MODEL_COMMON},     // Hunonic common gateway
        {ACCESS_COMPANY_ID_HUNONIC, SWITCH_MODEL_ID_GATEWAY, SUB_GROUP_ADDRESS_GATEWAY_MODEL_SWITCH},     // Hunonic switch gateway
        {ACCESS_COMPANY_ID_HUNONIC, OCSENSOR_MODEL_ID_GATEWAY, SUB_GROUP_ADDRESS_GATEWAY_MODEL_OCSENSOR}, // Hunonic ocsensor gateway
        {ACCESS_COMPANY_ID_HUNONIC, MTSENSOR_MODEL_ID_GATEWAY, SUB_GROUP_ADDRESS_GATEWAY_MODEL_MTSENSOR}, // Hunonic mtsensor gateway
        {ACCESS_COMPANY_ID_HUNONIC, SMSENSOR_MODEL_ID_GATEWAY, SUB_GROUP_ADDRESS_GATEWAY_MODEL_SMSENSOR}, // Hunonic smsensor gateway
        {ACCESS_COMPANY_ID_HUNONIC, THSENSOR_MODEL_ID_GATEWAY, SUB_GROUP_ADDRESS_GATEWAY_MODEL_THSENSOR}, // Hunonic thsensor gateway
    };
    m_model_id_t model_pub_list[] = {
        {0x0000, 0x0002, 0x0000},                                       // health server
        {0x0000, SUB_GROUP_ADDRESS_GATEWAY_HEALTH_NODE, 0x0000},        // health client
        {ACCESS_COMPANY_ID_HUNONIC, COMMON_MODEL_ID_GATEWAY, 0x0000},   // Hunonic common gateway
        {ACCESS_COMPANY_ID_HUNONIC, SWITCH_MODEL_ID_GATEWAY, 0x0000},   // Hunonic switch gateway
        {ACCESS_COMPANY_ID_HUNONIC, OCSENSOR_MODEL_ID_GATEWAY, 0x0000}, // Hunonic ocsensor gateway
        {ACCESS_COMPANY_ID_HUNONIC, MTSENSOR_MODEL_ID_GATEWAY, 0x0000}, // Hunonic mtsensor gateway
        {ACCESS_COMPANY_ID_HUNONIC, SMSENSOR_MODEL_ID_GATEWAY, 0x0000}, // Hunonic smsensor gateway
        {ACCESS_COMPANY_ID_HUNONIC, THSENSOR_MODEL_ID_GATEWAY, 0x0000}, // Hunonic thsensor gateway
    };

    ble_config_add_netkey(data->data.prov_gw_set.device_addr, data->data.prov_gw_set.netkey, HUNONIC_NETKEY_INDEX);
    ble_config_add_appkey(data->data.prov_gw_set.appkey, HUNONIC_NETKEY_INDEX, HUNONIC_APPKEY_INDEX);

    for (uint16_t i = 0; i < ARR_SIZE(model_sub_list); i++)
    {
        ble_config_bind_appkey(data->data.prov_gw_set.device_addr,
                               HUNONIC_APPKEY_INDEX,
                               model_sub_list[i].vendor,
                               model_sub_list[i].model_id);

        if (model_sub_list[i].address != 0x0000)
        {
            ble_config_set_sub_model(data->data.prov_gw_set.device_addr,
                                     model_sub_list[i].address,
                                     model_sub_list[i].vendor,
                                     model_sub_list[i].model_id);
        }

        if (model_pub_list[i].address != 0x0000)
        {
            ble_config_set_pub_model(data->data.prov_gw_set.device_addr,
                                     model_pub_list[i].address,
                                     model_pub_list[i].model_id);
        }
    }

    if (is_provision_success())
    {
        LOG_USER_MSG_INFO(0, 0, "%s Device is provisioned", __func__);

        show_mesh_info();
    }
    else
    {
        LOG_USER_MSG_INFO(0, 0, "%s Device is unprovision", __func__);
    }
}

void gateway_removing(gateway_pkg_t *data)
{
    LOG_USER_MSG_INFO(0, 0, "%s", __func__);
    kick_out(0);
}

void gateway_report_version(gateway_pkg_t *params)
{
    LOG_USER_MSG_INFO(0, 0, "%s", __func__);
    LOG_USER_MSG_INFO(0, 0, "%s SW_VER_BUILD: %d", __func__, SW_VER_BUILD);

    uart_message_t tx_msg;

    memset(&tx_msg, 0, sizeof(tx_msg));

    tx_msg.type = BLE_MCU_TO_ESP32;
    tx_msg.msg.gateway_pkg.cmd = OPCODE_GATEWAY_REP_VERSION;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.hw.major = 0xFFFFFFFF;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.hw.major = 0xFFFFFFFF;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.hw.minor = 0xFFFFFFFF;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.hw.path = 0xFFFFFFFF;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.hw.build = 0xFFFFFFFF;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.sw.major = SW_VER_MAJOR;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.sw.minor = SW_VER_MINOR;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.sw.path = SW_VER_PATH;
    tx_msg.msg.gateway_pkg.data.tb03_version_rep.sw.build = SW_VER_BUILD;

    m_uart_send(&tx_msg);
}

void gateway_factory_reset(gateway_pkg_t *params)
{
    LOG_USER_MSG_INFO(0, 0, "%s", __func__);
    kick_out(0);
}

extern u32 mesh_adv_tx_cmd_sno;
extern mesh_iv_idx_st_t iv_idx_st;
extern model_vd_hunonic_t model_vd_hunonic;
extern u8 get_net_arr_idx_by_appkey(u16 appkey_idx);
void ble_get_mesh_params(gateway_pkg_t *params)
{
    u8 ak_array_idx;
    u8 nk_array_idx;
    model_common_t *p_com_md = &model_vd_hunonic.switch_model;
    nk_array_idx = get_net_arr_idx_by_appkey(p_com_md->pub_par.appkey_idx);
    ak_array_idx = get_ak_arr_idx(nk_array_idx, p_com_md->pub_par.appkey_idx);

    int nk_len = sizeof(mesh_key.net_key[nk_array_idx][0].key);
    int ak_len = sizeof(mesh_key.net_key[nk_array_idx][0].app_key[ak_array_idx].key);

    gateway_rep_mesh_info_t mesh_info;
    memset(&mesh_info, 0, sizeof(mesh_info));
    memcpy(&mesh_info.netkey, mesh_key.net_key[nk_array_idx][0].key, nk_len);
    memcpy(&mesh_info.appkey, mesh_key.net_key[nk_array_idx][0].app_key[ak_array_idx].key, ak_len);
    mesh_info.iv_cur = iv_idx_st.iv_cur;
    mesh_info.iv_tx = iv_idx_st.iv_tx;
    mesh_info.iv_rx = iv_idx_st.iv_rx;

    uart_message_t tx_msg;
    memset(&tx_msg, 0, sizeof(tx_msg));
    tx_msg.type = BLE_MCU_TO_ESP32;
    tx_msg.msg.gateway_pkg.cmd = OPCODE_GATEWAY_REP_MESH_INFO;
    memcpy(&tx_msg.msg.gateway_pkg.data.gateway_rep_mesh_info, &mesh_info, sizeof(mesh_info));
    m_uart_send(&tx_msg);

    LOG_USER_MSG_INFO(0, 0, "nk_array_idx: %d: %s", nk_array_idx, mesh_info.netkey);
    LOG_USER_MSG_INFO(0, 0, "ak_array_idx: %d: %s", ak_array_idx, mesh_info.appkey);
    LOG_USER_MSG_INFO(0, 0, "\"cur_iv\":%d, \"tx_iv\":%d, \"rx_iv\":%d",
                      mesh_info.iv_cur, mesh_info.iv_tx, mesh_info.iv_rx);
}

void show_mesh_info(void)
{
	uint8_t netkey[17] = {0};
	uint8_t appkey[17] = {0};

	u8 ak_array_idx;
	u8 nk_array_idx;
	model_common_t *p_com_md = &model_vd_hunonic.switch_model;
	nk_array_idx = get_net_arr_idx_by_appkey(p_com_md->pub_par.appkey_idx);
	ak_array_idx = get_ak_arr_idx(nk_array_idx, p_com_md->pub_par.appkey_idx);

	memcpy(netkey, mesh_key.net_key[nk_array_idx][0].key, 16);
	memcpy(appkey, mesh_key.net_key[nk_array_idx][0].app_key[ak_array_idx].key, 16);

	LOG_USER_MSG_INFO(0, 0, "nk_array_idx: %d: %s ", nk_array_idx, (char*)netkey);
	LOG_USER_MSG_INFO(0, 0, "ak_array_idx: %d: %s ", ak_array_idx, (char*)appkey);
	LOG_USER_MSG_INFO(0, 0, "\"cur_iv\":%d, \"tx_iv\":%d, \"rx_iv\":%d",
					  iv_idx_st.iv_cur, iv_idx_st.iv_tx, iv_idx_st.iv_rx);
}

m_gateway_handler_t array_handler[] = {
    {OPCODE_GATEWAY_SET_PROV_GW, gateway_provisioning},
    {OPCODE_GATEWAY_SET_RM_GW, gateway_removing},
    {OPCODE_GATEWAY_GET_VERSION, gateway_report_version},
    {OPCODE_GATEWAY_SET_TB03_OTA_START, gateway_update_start},
    {OPCODE_GATEWAY_SET_TB03_OTA_DATA, gateway_update_write_fw},
    {OPCODE_GATEWAY_SET_TB03_CHECK_MD5, gateway_update_check_md5},
    {OPCODE_GATEWAY_SET_TB03_OTA_END, gateway_update_end},
    {OPCODE_GATEWAY_GET_MESH_INFO, ble_get_mesh_params},
    {OPCODE_GATEWAY_KICKOUT_MESH, gateway_factory_reset}
};

void esp32_to_ble_mcu_handler(gateway_pkg_t *data)
{
    foreach_arr(i, array_handler)
    {
        if (array_handler[i].cmd == data->cmd)
        {
            if (array_handler[i].callback)
            {
                return array_handler[i].callback(data);
            }
        }
    }
}
