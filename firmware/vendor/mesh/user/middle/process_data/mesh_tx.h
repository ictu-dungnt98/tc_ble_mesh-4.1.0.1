#ifndef MESH_TX_H_
#define MESH_TX_H_

#include "vendor/mesh/user/middle/uart/m_uart.h"
#include "vendor/mesh/user/config/app_config.h"
#include "vendor/mesh/user/config/system_typedef.h"
#include "vendor/mesh/user/hardware/hardware.h"
#include "vendor/mesh/user/middle/mesh_model/vendor_model_hunonic.h"
#include "vendor/mesh/user/middle/mesh_model/hunonic_model_config.h"
#include "vendor/mesh/user/middle/squeue/squeue.h"

typedef struct
{
    u16 adr_dst;
    u8 rsp_max;
    u16 op;
    mesh_parameter_t par;
    int len;
    u8 rsp_op;
    u8 tid;
} mesh_msg_tx_t;

void mesh_tx_data_init(void);
void mesh_tx_data_loop(void);
int mesh_send(u16 adr_dst, u8 rsp_max, u16 op, u8 *par, int len, u8 rsp_op, u8 tid);

#endif