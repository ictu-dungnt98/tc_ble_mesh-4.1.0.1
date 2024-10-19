#include "ble_config.h"
#include "vendor/mesh/user/middle/mesh_model/vendor_model_hunonic.h"

#include "../../vendor/common/app_provison.h"
#include "../../vendor/common/mesh_node.h"

void ble_config_add_devkey(uint8_t *p_devkey, bool self_key)
{
    uint8_t devkey[16];

    if (p_devkey)
    {
        memcpy(devkey, p_devkey, 16);
    }
    else
    {
        for (uint8_t i = 0; i < sizeof(devkey); i++)
            devkey[i] = rand();
    }

    set_dev_key(devkey);
}

void ble_config_add_netkey(uint16_t address, uint8_t *netkey, uint32_t netkey_idx)
{
    provison_net_info_str provison_net_info = {
        .key_index = netkey_idx,
        .iv_index = {0, 0, 0, 0},
        .unicast_address = address,
    };
    provison_net_info.flags = 0;
    memcpy(provison_net_info.net_work_key, netkey, 16);
    memset(provison_net_info.iv_index, 0, sizeof(provison_net_info.iv_index));

    mesh_provision_par_handle((uint8_t *)&provison_net_info);
    mesh_key_node_identity_set_prov_set();
}

void ble_config_add_appkey(uint8_t *appkey, uint32_t netkey_idx, uint32_t appkey_idx)
{
    mesh_cb_fun_par_t cb_par = {
        .model = (uint8_t *)&model_sig_cfg_s,
        .op = APPKEY_ADD,
    };

    struct __attribute((packed))
    {
        struct __attribute((packed))
        {
            uint8_t key_id_1_lsb;     /**< 8 LSB of the first key index. */
            uint8_t key_id_1_msb : 4; /**< 4 MSB of the first key index. */
            uint8_t key_id_2_lsb : 4; /**< 4 LSB of the second key index. */
            uint8_t key_id_2_msb;     /**< 8 MSB of the second key index. */
        } index;
        uint8_t appkey[16];
    } cmd_sig_cfg_appkey_set;

    cmd_sig_cfg_appkey_set.index.key_id_1_lsb = netkey_idx & 0xFF;
    cmd_sig_cfg_appkey_set.index.key_id_1_msb = (netkey_idx >> 8) & 0xF;

    cmd_sig_cfg_appkey_set.index.key_id_2_lsb = appkey_idx & 0xF;
    cmd_sig_cfg_appkey_set.index.key_id_2_msb = (appkey_idx >> 4) & 0xFF;

    memcpy(cmd_sig_cfg_appkey_set.appkey, appkey, 16);

    //DEBUG_LOG_HEX("cmd_sig_cfg_appkey_set", (uint8_t *)&cmd_sig_cfg_appkey_set, sizeof(cmd_sig_cfg_appkey_set));
    int ret = mesh_cmd_sig_cfg_appkey_set((uint8_t *)&cmd_sig_cfg_appkey_set, sizeof(cmd_sig_cfg_appkey_set), &cb_par);
    printf("mesh_cmd_sig_cfg_appkey_set() ret: %d\n", ret);
}

void ble_config_bind_appkey(uint16_t address, uint32_t appkey_idx, uint16_t vendor_id, uint16_t model_id)
{
    mesh_cb_fun_par_t cb_par = {
        .model = (uint8_t *)&model_sig_cfg_s,
        .op = MODE_APP_BIND,
    };

    struct
    {
        uint16_t address;
        uint16_t appkey_idx;
        uint32_t model_id;

    } cmd_sig_cfg_bind = {
        .address = address,
        .appkey_idx = appkey_idx,
        .model_id = ACCESS_MODEL_VENDOR(model_id, vendor_id),
    };

    int size = sizeof(cmd_sig_cfg_bind);
    if (vendor_id == 0x0000)
    {
        size -= sizeof(uint32_t) / 2;
        cmd_sig_cfg_bind.model_id = model_id;
    }

    //DEBUG_LOG_HEX("cmd_sig_cfg_bind", (uint8_t *)&cmd_sig_cfg_bind, size);
    int ret = mesh_cmd_sig_cfg_bind((uint8_t *)&cmd_sig_cfg_bind, size, &cb_par);
    printf("mesh_cmd_sig_cfg_bind() ret: %d\n", ret);
}

void ble_config_set_sub_model(uint16_t address, uint16_t sub_addr, uint16_t vendor_id, uint16_t model_id)
{
    mesh_cb_fun_par_t cb_par = {
        .model = (uint8_t *)&model_sig_cfg_s,
        .op = CFG_MODEL_SUB_ADD,
    };

    struct
    {
        uint16_t address;
        uint16_t sub_addr;
        uint32_t model_id;
    } cmd_sig_cfg_model_sub_set = {
        .address = address,
        .sub_addr = sub_addr,
        .model_id = ACCESS_MODEL_VENDOR(model_id, vendor_id),
    };

    int size = sizeof(cmd_sig_cfg_model_sub_set);
    if (vendor_id == 0x0000)
    {
        size -= sizeof(uint32_t) / 2;
        cmd_sig_cfg_model_sub_set.model_id = model_id;
    }

    //DEBUG_LOG_HEX("mesh_cmd_sig_cfg_model_sub_set", (uint8_t *)&cmd_sig_cfg_model_sub_set, size);
    int ret = mesh_cmd_sig_cfg_model_sub_set((uint8_t *)&cmd_sig_cfg_model_sub_set, size, &cb_par);
    printf("mesh_cmd_sig_cfg_model_sub_set() ret: %d\n", ret);
}

void ble_config_set_pub_model(uint16_t address, uint16_t sub_addr, uint16_t model_id)
{
}
