#ifndef __VENDOR_MODEL_HUNONIC_H__
#define __VENDOR_MODEL_HUNONIC_H__

#include "../../proj/tl_common.h"
#include "../../proj_lib/sig_mesh/app_mesh.h"

#include "hunonic_model_config.h"

#define GATEWAY_COMMON_MODEL_TX ACCESS_MODEL_VENDOR(COMMON_MODEL_ID_NODE, ACCESS_COMPANY_ID_HUNONIC)
#define GATEWAY_COMMON_MODEL_RX ACCESS_MODEL_VENDOR(COMMON_MODEL_ID_GATEWAY, ACCESS_COMPANY_ID_HUNONIC)

#define GATEWAY_SWITCH_MODEL_TX ACCESS_MODEL_VENDOR(SWITCH_MODEL_ID_NODE, ACCESS_COMPANY_ID_HUNONIC)
#define GATEWAY_SWITCH_MODEL_RX ACCESS_MODEL_VENDOR(SWITCH_MODEL_ID_GATEWAY, ACCESS_COMPANY_ID_HUNONIC)

#define GATEWAY_OCSENSOR_MODEL_TX ACCESS_MODEL_VENDOR(OCSENSOR_MODEL_ID_NODE, ACCESS_COMPANY_ID_HUNONIC)
#define GATEWAY_OCSENSOR_MODEL_RX ACCESS_MODEL_VENDOR(OCSENSOR_MODEL_ID_GATEWAY, ACCESS_COMPANY_ID_HUNONIC)

#define GATEWAY_MTSENSOR_MODEL_TX ACCESS_MODEL_VENDOR(MTSENSOR_MODEL_ID_NODE, ACCESS_COMPANY_ID_HUNONIC)
#define GATEWAY_MTSENSOR_MODEL_RX ACCESS_MODEL_VENDOR(MTSENSOR_MODEL_ID_GATEWAY, ACCESS_COMPANY_ID_HUNONIC)

#define GATEWAY_SMSENSOR_MODEL_TX ACCESS_MODEL_VENDOR(SMSENSOR_MODEL_ID_NODE, ACCESS_COMPANY_ID_HUNONIC)
#define GATEWAY_SMSENSOR_MODEL_RX ACCESS_MODEL_VENDOR(SMSENSOR_MODEL_ID_GATEWAY, ACCESS_COMPANY_ID_HUNONIC)

#define GATEWAY_THSENSOR_MODEL_TX ACCESS_MODEL_VENDOR(THSENSOR_MODEL_ID_NODE, ACCESS_COMPANY_ID_HUNONIC)
#define GATEWAY_THSENSOR_MODEL_RX ACCESS_MODEL_VENDOR(THSENSOR_MODEL_ID_GATEWAY, ACCESS_COMPANY_ID_HUNONIC)

typedef struct
{
    model_common_t common_model;
    model_common_t switch_model;
    model_common_t ocsensor_model;
    model_common_t mtsensor_model;
    model_common_t smsensor_model;
    model_common_t thsensor_model;
} model_vd_hunonic_t;

extern uint32_t mesh_md_hunonic_addr;
extern model_vd_hunonic_t model_vd_hunonic;

int vd_model_hunonic_health_client_callback(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);
int vd_model_hunonic_search_model_id_by_op_vendor(mesh_op_resource_t *op_res, u16 op, u8 tx_flag);
int vd_model_hunonic_is_cmd_with_tid(u8 *tid_pos_out, u16 op, u8 tid_pos_vendor_app);

#endif /* __VENDOR_MODEL_HUNONIC_H__ */