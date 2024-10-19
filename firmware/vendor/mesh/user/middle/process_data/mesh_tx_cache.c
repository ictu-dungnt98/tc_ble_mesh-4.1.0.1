#include "vendor/mesh/user/middle/uart/m_uart.h"
#include "vendor/mesh/user/config/app_config.h"
#include "vendor/mesh/user/config/system_typedef.h"
#include "vendor/mesh/user/hardware/hardware.h"
#include "vendor/mesh/user/middle/mesh_model/vendor_model_hunonic.h"
#include "vendor/mesh/user/middle/mesh_model/hunonic_model_config.h"

#include "mesh_tx.h"
#include "mesh_tx_cache.h"

#define MAX_SIZE_CACHE_TABLE 20

typedef struct
{
    uint8_t retry;
    uint32_t timestamp_us;
    uint8_t is_used;
    mesh_pkg_t mesh_pkg;
} cache_msg_t;

static cache_msg_t wait_rsp_table[MAX_SIZE_CACHE_TABLE];

void cache_msg_wait_rsp(mesh_pkg_t *tx_data)
{
    if ((tx_data->model_id == COMMON_MODEL_ID_NODE))
    {
        return;
    }

    if (tx_data->para.cmd != SW_REQ_SET_STATE &&
        tx_data->para.cmd != SW_REQ_SET_LOOP_TIMER &&
        tx_data->para.cmd != SW_REQ_DEL_LOOP_TIMER)
    {
        LOG_USER_MSG_INFO(0, 0, "No need cache message: %d", tx_data->para.cmd);
        return;
    }

    int i;
    for (i = 0; i < ARR_SIZE(wait_rsp_table); i++)
    {
        if (wait_rsp_table[i].is_used == 0)
        {
            wait_rsp_table[i].is_used = 1;
            wait_rsp_table[i].retry = 3;
            wait_rsp_table[i].timestamp_us = clock_time();
            memset(&wait_rsp_table[i].mesh_pkg, 0, sizeof(wait_rsp_table[i].mesh_pkg));
            memcpy(&wait_rsp_table[i].mesh_pkg, tx_data, sizeof(wait_rsp_table[i].mesh_pkg));
            LOG_USER_MSG_INFO(0, 0, "cache msg success", 0);
            return;
        }
    }

    if (i >= ARR_SIZE(wait_rsp_table))
    {
        LOG_USER_MSG_INFO(0, 0, "cache data fail", 0);
    }
}

void check_rsp_and_clr_cache(mesh_pkg_t *rx_data)
{
    if ((rx_data->model_id == COMMON_MODEL_ID_NODE))
    {
        return;
    }

    if (rx_data->para.cmd != SW_REP_SET_STATE &&
        rx_data->para.cmd != SW_REP_SET_LOOP_TIMER &&
        rx_data->para.cmd != SW_REP_DEL_LOOP_TIMER)
    {
        return;
    }

    for (int i = 0; i < ARR_SIZE(wait_rsp_table); i++)
    {
        if (wait_rsp_table[i].is_used == 1)
        {
            if (rx_data->address == wait_rsp_table[i].mesh_pkg.address)
            {
                if (rx_data->para.cmd == SW_REP_SET_STATE)
                {
                    if (rx_data->para.data.sw_msg_rep.state.tid == wait_rsp_table[i].mesh_pkg.para.data.sw_msg_rep.state.tid)
                    {
                        memset(&wait_rsp_table[i], 0, sizeof(wait_rsp_table[i]));
                        LOG_USER_MSG_INFO(0, 0, "clear cache data success", 0);
                    }
                }
                else
                {
                    if (rx_data->para.data.sw_msg_rep.loop_timer.tid == wait_rsp_table[i].mesh_pkg.para.data.sw_msg_rep.loop_timer.tid)
                    {
                        memset(&wait_rsp_table[i], 0, sizeof(wait_rsp_table[i]));
                        LOG_USER_MSG_INFO(0, 0, "clear cache data success", 0);
                    }
                }
            }
        }
    }
}

void cache_msg_resend_loop(void)
{
    uint16_t addr = 0;
    uint16_t model_id = 0;
    uint16_t opcode = 0;
    uint8_t *param = 0;
    uint32_t param_len = 0;

    for (int i = 0; i < ARR_SIZE(wait_rsp_table); i++)
    {
        if (wait_rsp_table[i].is_used == 1)
        {
            if (clock_time_exceed(wait_rsp_table[i].timestamp_us, 500*1000)) /* 300ms */
            {
                wait_rsp_table[i].timestamp_us = clock_time();

                if (wait_rsp_table[i].retry > 0)
                {
                    wait_rsp_table[i].retry--;

                    addr = wait_rsp_table[i].mesh_pkg.address;
                    model_id = wait_rsp_table[i].mesh_pkg.model_id;
                    opcode = wait_rsp_table[i].mesh_pkg.opcode_mesh;
                    param = (uint8_t *)&wait_rsp_table[i].mesh_pkg.para;
                    param_len = wait_rsp_table[i].mesh_pkg.len_para;

                    LOG_USER_MSG_INFO(0, 0, "Resend message cached", 0);
                    mesh_send(addr, 1, opcode, param, param_len, 0, 0);
                }
            }
        }
    }
}

void cache_msg_init(void)
{
    memset(&wait_rsp_table, 0, sizeof(wait_rsp_table));
}