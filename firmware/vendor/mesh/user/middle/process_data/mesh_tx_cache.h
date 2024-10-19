#ifndef MESH_TX_CACHE_H_
#define MESH_TX_CACHE_H_

#include "vendor/mesh/user/middle/uart/m_uart.h"
#include "vendor/mesh/user/config/app_config.h"
#include "vendor/mesh/user/config/system_typedef.h"
#include "vendor/mesh/user/hardware/hardware.h"
#include "vendor/mesh/user/middle/mesh_model/vendor_model_hunonic.h"
#include "vendor/mesh/user/middle/mesh_model/hunonic_model_config.h"
#include "vendor/mesh/user/middle/squeue/squeue.h"

void cache_msg_resend_loop(void);
void check_rsp_and_clr_cache(mesh_pkg_t *rx_data);
void cache_msg_wait_rsp(mesh_pkg_t *tx_data);
void cache_msg_init(void);

#endif