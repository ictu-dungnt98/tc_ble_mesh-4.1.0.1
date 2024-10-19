#include "vendor/mesh/user/middle/uart/m_uart.h"
#include "vendor/mesh/user/config/app_config.h"
#include "vendor/mesh/user/config/system_typedef.h"
#include "vendor/mesh/user/hardware/hardware.h"
#include "vendor/mesh/user/middle/mesh_model/vendor_model_hunonic.h"
#include "vendor/mesh/user/middle/mesh_model/hunonic_model_config.h"
#include "vendor/mesh/user/middle/squeue/squeue.h"

#define MESH_MAX_QUEUE_ITEM 50

static sq_t tx_queue;

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

int mesh_send(u16 adr_dst, u8 rsp_max, u16 op, u8 *par, int len, u8 rsp_op, u8 tid)
{
    mesh_msg_tx_t new_msg;

    memset(&new_msg, 0, sizeof(new_msg));
    new_msg.adr_dst = adr_dst;
    new_msg.rsp_max = rsp_max;
    new_msg.op = op;
    memcpy(&new_msg.par, par, len);
    new_msg.len = len;
    new_msg.rsp_op = rsp_op;
    new_msg.tid = tid;

    if (sq_push(&tx_queue, &new_msg))
    {
        return 0;
    }

    LOG_USER_MSG_INFO(0, 0, "%s push to tx_queue fail", __func__);
    return -1;
}

void mesh_tx_data_loop(void)
{
    static uint32_t old_time = 0;
    if (sys_get_tick_ms() - old_time < 100)
    {
        return;
    }
    old_time = sys_get_tick_ms();

    mesh_msg_tx_t tx_msg;

    if (sq_pop(&tx_queue, &tx_msg))
    {
        SendOpParaDebug_vendor(tx_msg.adr_dst, tx_msg.rsp_max, tx_msg.op,
                               (u8 *)&tx_msg.par, tx_msg.len,
                               tx_msg.rsp_op, tx_msg.tid);
    }
}

void mesh_tx_data_init(void)
{
    sq_init(&tx_queue, sizeof(mesh_msg_tx_t), MESH_MAX_QUEUE_ITEM);
}