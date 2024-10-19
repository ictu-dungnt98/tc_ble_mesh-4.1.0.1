/********************************************************************************************************
 * @file	main.c
 *
 * @brief	for TLSR chips
 *
 * @author	telink
 * @date	Sep. 30, 2010
 *
 * @par     Copyright (c) 2017, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#include "vendor/mesh/user/app/user_main.h"

extern void user_init();
extern void main_loop();
void blc_pm_select_none();
extern void show_mesh_info(void);

#if (HCI_ACCESS == HCI_USE_UART)
#include "proj/drivers/uart.h"
extern my_fifo_t hci_rx_fifo;

int sdk_log_enable = SDK_LOG_ENABLE;
u16 uart_tx_irq = 0, uart_rx_irq = 0;

_attribute_ram_code_ void irq_uart_handle()
{
	unsigned char irqS = reg_dma_rx_rdy0;
	if (irqS & FLD_DMA_CHN_UART_RX) // rx
	{
		uart_rx_irq++;
		reg_dma_rx_rdy0 = FLD_DMA_CHN_UART_RX;
		u8 *w = hci_rx_fifo.p + (hci_rx_fifo.wptr & (hci_rx_fifo.num - 1)) * hci_rx_fifo.size;
		if (w[0] != 0)
		{
			my_fifo_next(&hci_rx_fifo);
			u8 *p = hci_rx_fifo.p + (hci_rx_fifo.wptr & (hci_rx_fifo.num - 1)) * hci_rx_fifo.size;
			reg_dma0_addr = (u16)((u32)p);
		}
	}

	if (irqS & FLD_DMA_CHN_UART_TX) // tx
	{
		uart_tx_irq++;
		reg_dma_rx_rdy0 = FLD_DMA_CHN_UART_TX;
	}
}
#endif

_attribute_ram_code_ void irq_handler(void)
{
#if ACTIVE_SCAN_ENABLE
	rp_active_scan_req_proc();
#endif

	irq_blt_sdk_handler(); // ble irq proc

#if (HCI_ACCESS == HCI_USE_UART)
	irq_uart_handle();
#endif
}

FLASH_ADDRESS_DEFINE;
_attribute_ram_code_ int main(void) // must run in ramcode
{
	FLASH_ADDRESS_CONFIG;
#if (PINGPONG_OTA_DISABLE && (0 == FW_START_BY_LEGACY_BOOTLOADER_EN))
	ota_fw_check_over_write(); // must at first for main_
#endif

#if SLEEP_FUNCTION_DISABLE
	blc_pm_select_none();
#else
	blc_pm_select_internal_32k_crystal();
#endif

	cpu_wakeup_init();

	int deepRetWakeUp = pm_is_MCU_deepRetentionWakeup(); // MCU deep retention wakeUp
	rf_drv_init(RF_MODE_BLE_1M);
	gpio_init(!deepRetWakeUp); // analog resistance will keep available in deepSleep mode, so no need initialize again
	clock_init(SYS_CLK_CRYSTAL);

	LOG_USER_MSG_INFO(0, 0, "Start user init...");
	user_init();
	show_mesh_info();
	user_main_init();
	irq_enable();

	while (1)
	{
		wd_clear(); // clear watch dog
		main_loop();
		user_main_loop();
	}
}
