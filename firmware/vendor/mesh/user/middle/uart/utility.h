#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdint.h>

uint16_t get_len_msg_gateway_set(uint16_t opcode);
uint16_t get_len_msg_gateway_rep(uint16_t opcode);

uint32_t hunonic_ticks_diff_compute(uint32_t ticks_to, uint32_t ticks_from);
uint32_t hunonic_ticks_get_ticks(void);
uint32_t hunonic_ticks_us2ticks(uint32_t us);
uint32_t hunonic_ticks_ms2ticks(uint32_t ms);
uint32_t hunonic_ticks_s2ticks(uint32_t s);

#endif