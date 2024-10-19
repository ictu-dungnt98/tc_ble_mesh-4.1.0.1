#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef HUNONIC_NETKEY_INDEX
#define HUNONIC_NETKEY_INDEX (0)
#endif

#ifndef HUNONIC_APPKEY_INDEX
#define HUNONIC_APPKEY_INDEX (0)
#endif

#ifndef HUNONIC_DEVKEY_INDEX
#define HUNONIC_DEVKEY_INDEX (1)
#endif

#ifndef HUNONIC_TTL_MAX
#define HUNONIC_TTL_MAX (16)
#endif

#ifndef HUNONIC_HCI_SIZE
#define HUNONIC_HCI_SIZE (256)
#endif

void ble_config_add_devkey(uint8_t *p_devkey, bool self_key);
void ble_config_add_netkey(uint16_t address, uint8_t *netkey, uint32_t netkey_idx);
void ble_config_add_appkey(uint8_t *appkey, uint32_t netkey_idx, uint32_t appkey_idx);
void ble_config_bind_appkey(uint16_t address, uint32_t appkey_idx, uint16_t vendor_id, uint16_t model_id);
void ble_config_set_sub_model(uint16_t address, uint16_t sub_addr, uint16_t vendor_id, uint16_t model_id);
void ble_config_set_pub_model(uint16_t address, uint16_t sub_addr, uint16_t model_id);
