#include "hardware.h"
#include <stdint.h>

void hw_led_stt_set(uint8_t value)
{
	gpio_write(LED_STT_PIN, value);
}

void hw_led_stt_toggle(void)
{
	gpio_toggle(LED_STT_PIN);
}

void hw_led_stt_init(void)
{
    gpio_set_func(LED_STT_PIN, AS_GPIO);
	gpio_set_input_en(LED_STT_PIN, 0); 
	gpio_set_output_en(LED_STT_PIN, 1);
}

uint32_t sys_get_tick_ms(void)
{
    return clock_time() / 16000;
}
