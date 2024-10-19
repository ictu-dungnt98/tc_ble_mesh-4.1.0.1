#ifndef _OTA_H_
#define _OTA_H_

#include <stdint.h>
#include "vendor/mesh/user/middle/uart/m_uart.h"

#define DFU_TIMEOUT_VALUE (30)
#define NRF_MESH_DFU_SEGMENT_LENGTH (16)
#define DFU_REPEAT_SEG (0)

void gateway_update_start(gateway_pkg_t *data);
void gateway_update_write_fw(gateway_pkg_t *data);
void gateway_update_end(gateway_pkg_t *data);
void gateway_update_check_md5(gateway_pkg_t *data);

#endif