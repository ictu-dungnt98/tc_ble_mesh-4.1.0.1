#ifndef _HARDWARE_
#define _HARDWARE_

#include "proj/tl_common.h"
#include "vendor/common/system_time.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#define LED_STT_PIN     GPIO_PD2
#define LED_ON          0
#define LED_OFF         !LED_ON

void hw_led_stt_init(void);
void hw_led_stt_toggle(void);
void hw_led_stt_set(uint8_t value);

uint32_t sys_get_tick_ms(void);

#endif