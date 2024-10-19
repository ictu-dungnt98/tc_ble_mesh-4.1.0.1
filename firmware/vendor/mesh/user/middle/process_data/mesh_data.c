#include "vendor/mesh/user/middle/uart/m_uart.h"
#include "vendor/mesh/user/config/app_config.h"
#include "vendor/mesh/user/config/system_typedef.h"
#include "vendor/mesh/user/hardware/hardware.h"
#include "vendor/mesh/user/middle/mesh_model/vendor_model_hunonic.h"
#include "vendor/mesh/user/middle/mesh_model/hunonic_model_config.h"

#include "mesh_tx.h"
#include "mesh_tx_cache.h"

typedef struct
{
    uint16_t model_id;
    model_common_t *pModel;
} data_handler_t;

uint8_t esp32_to_mesh_handler(mesh_pkg_t *mesh_pkg)
{
    // LOG_USER_MSG_INFO(0, 0, "%s", __func__);

    data_handler_t opcode_model[] = {
        {COMMON_MODEL_ID_NODE, &model_vd_hunonic.common_model},
        {SWITCH_MODEL_ID_NODE, &model_vd_hunonic.switch_model},
        {OCSENSOR_MODEL_ID_NODE, &model_vd_hunonic.ocsensor_model},
        {MTSENSOR_MODEL_ID_NODE, &model_vd_hunonic.mtsensor_model},
        {SMSENSOR_MODEL_ID_NODE, &model_vd_hunonic.smsensor_model},
        {THSENSOR_MODEL_ID_NODE, &model_vd_hunonic.thsensor_model},
    };

    uint16_t addr = mesh_pkg->address;
    uint16_t model_id = mesh_pkg->model_id;
    uint16_t opcode = mesh_pkg->opcode_mesh;
    uint8_t *param = (uint8_t *)&mesh_pkg->para;
    uint32_t param_len = mesh_pkg->len_para;

    // LOG_USER_MSG_INFO(0, 0, "%s: opcode: %4X", __func__, opcode);
    // LOG_USER_MSG_INFO(0, 0, "%s: model_id: %4X", __func__, model_id);
    // LOG_USER_MSG_INFO(0, 0, "%s: addr: %d", __func__, addr);
    // LOG_USER_MSG_INFO(0, 0, "%s: param_len: %d", __func__, param_len);

    for (uint8_t i = 0; i < ARR_SIZE(opcode_model); i++)
    {
        if (opcode_model[i].model_id == model_id)
        {
            printf("got this, send to node over MESH");

            hw_led_stt_set(LED_ON);

            if ((model_id == COMMON_MODEL_ID_NODE) &&
                (mesh_pkg->para.cmd == COMMON_LPN_ENTER_DFU ||
                 mesh_pkg->para.cmd == COMMON_PING_ALL_NODE ||
                 mesh_pkg->para.cmd == COMMON_UPDATE_TIMESTAMP ||
                 mesh_pkg->para.cmd == COMMON_REMOVE_NODE))
            {
                // ret = SendOpParaDebug_vendor(addr, 0, opcode, param, param_len, 0, 0);
                mesh_send(addr, 0, opcode, param, param_len, 0, 0);
            }
            else
            {
                // ret = SendOpParaDebug_vendor(addr, 1, opcode, param, param_len, 0, 0);
                mesh_send(addr, 1, opcode, param, param_len, 0, 0);
                cache_msg_wait_rsp(mesh_pkg);
            }

            hw_led_stt_set(LED_OFF);
        }
    }

    return SUCCESS_CODE;
}