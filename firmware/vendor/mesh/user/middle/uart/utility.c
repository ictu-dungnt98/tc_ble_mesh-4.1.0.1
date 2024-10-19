#include <stdint.h>
#include "m_uart.h"
#include "drivers/8258/timer.h"

// uint16_t get_len_msg_gateway_set(uint16_t opcode)
// {
//     gateway_pkg_t gateway_pkg;

//     switch (opcode)
//     {
//     case OPCODE_GATEWAY_SET_PROV_GW:
//         return sizeof(gateway_pkg.cmd) + sizeof(gateway_set_prov_gw_t);
//         break;

//     case OPCODE_GATEWAY_SET_RM_GW:
//         return sizeof(gateway_pkg.cmd) + sizeof(gateway_set_rm_gw_t);
//         break;

//     case OPCODE_GATEWAY_SET_PROV_NODE:
//         return sizeof(gateway_pkg.cmd) + sizeof(gateway_set_prov_node_t);
//         break;

//     case OPCODE_GATEWAY_SET_SETUP_NODE:
//         return sizeof(gateway_pkg.cmd) + sizeof(gateway_set_setup_node_t);
//         break;

//     case OPCODE_GATEWAY_GET_VERSION:
//         return sizeof(gateway_pkg.cmd);
//         break;
//     default:
//         return 0;
//     }
// }


// uint16_t get_len_msg_gateway_rep(uint16_t opcode)
// {
//     gateway_pkg_t gateway_pkg;

//     switch (opcode)
//     {
//     case OPCODE_GATEWAY_REP_PROV_GW:
//         return sizeof(gateway_pkg.cmd) + sizeof(gateway_rep_prov_gw_t);
//         break;

//     case OPCODE_GATEWAY_REP_RM_GW:
//         return sizeof(gateway_pkg.cmd) + sizeof(gateway_rep_rm_gw_t);
//         break;
   
//     case OPCODE_GATEWAY_REP_VERSION:
//         return sizeof(gateway_pkg.cmd) + sizeof(gateway_rep_version_t);
//         break;

//     default:
//         return 0;
//     }
// }

uint32_t hunonic_ticks_diff_compute(uint32_t ticks_to, uint32_t ticks_from)
{
    return (ticks_to - ticks_from);
}

uint32_t hunonic_ticks_get_ticks()
{
    return clock_time();
}

uint32_t hunonic_ticks_us2ticks(uint32_t us)
{
    return (us * CLOCK_SYS_CLOCK_1US);
}

uint32_t hunonic_ticks_ms2ticks(uint32_t ms)
{
    return hunonic_ticks_us2ticks(ms * 1000);
}

uint32_t hunonic_ticks_s2ticks(uint32_t s)
{
    return hunonic_ticks_ms2ticks(s * 1000);
}