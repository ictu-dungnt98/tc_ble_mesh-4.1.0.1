#ifndef HUNONIC_MODEL_CONFIG_H__
#define HUNONIC_MODEL_CONFIG_H__

#define ATTENTION_DURATION_S (5)

#define PROVISIONER_RETRY_COUNT (2)

#define NETWORK_TRANSMIT_COUNT (2)
#define NETWORK_TRANSMIT_INTERVAL_STEPS (1)

#define NODE_IN_NETWORK_NUM (30)
#define DEFAULT_TTL (NODE_IN_NETWORK_NUM)

#define APPKEY_INDEX (0)
#define NETKEY_INDEX (0)
#define ELEMENT_INDEX (0)

#define ADDRESS_GET_ALL_STATUS (0)

#define HUNONIC_COMPANY_ID ACCESS_COMPANY_ID_NORDIC

/*
**  Format:
**  SUB_GROUP_ADDRESS_GATEWAY_MODEL_##NAME
**  PUB_GROUP_ADDRESS_GATEWAY_MODEL_##NAME
**  
**  NAME##MODEL_ID_GATEWAY
**  NAME##MODEL_ID_NODE
*/

/* for time model */
#define TIME_MODEL_ID_NODE (0x1301)

/* for hunonic model. */
#define SUB_GROUP_ADDRESS_GATEWAY_MODEL_COMMON (0xC000)
#define PUB_GROUP_ADDRESS_GATEWAY_MODEL_COMMON (0xC001)
#define COMMON_MODEL_ID_GATEWAY (0x2000)
#define COMMON_MODEL_ID_NODE (0x2001)

/* for health model. */
#define SUB_GROUP_ADDRESS_GATEWAY_HEALTH_NODE (0xC002)
#define PUB_GROUP_ADDRESS_GATEWAY_HEALTH_NODE (0xC003)
#define HEALTH_MODEL_ID_GATEWAY (0x0003)
#define HEALTH_MODEL_ID_NODE (0x0002)

/* for switch model. */
#define SUB_GROUP_ADDRESS_GATEWAY_MODEL_SWITCH (0xC010)
#define PUB_GROUP_ADDRESS_GATEWAY_MODEL_SWITCH (0xC011)
#define SWITCH_MODEL_ID_GATEWAY (0x2002)
#define SWITCH_MODEL_ID_NODE (0x2003)

/* for open/close sensor model. */
#define SUB_GROUP_ADDRESS_GATEWAY_MODEL_OCSENSOR (0xC020)
#define PUB_GROUP_ADDRESS_GATEWAY_MODEL_OCSENSOR (0xC021)
#define OCSENSOR_MODEL_ID_GATEWAY (0x2004)
#define OCSENSOR_MODEL_ID_NODE (0x2005)

/* for motion sensor model. */
#define SUB_GROUP_ADDRESS_GATEWAY_MODEL_MTSENSOR (0xC030)
#define PUB_GROUP_ADDRESS_GATEWAY_MODEL_MTSENSOR (0xC031)
#define MTSENSOR_MODEL_ID_GATEWAY (0x2006)
#define MTSENSOR_MODEL_ID_NODE (0x2007)

/* for PB REMOTE model.  */
#define PUB_GROUP_ADDRESS_GATEWAY_MODEL_PBREMOTE (0xC040)
#define SUB_GROUP_ADDRESS_GATEWAY_MODEL_PBREMOTE (0xC041)

/* for smoke sensor model. */
#define SUB_GROUP_ADDRESS_GATEWAY_MODEL_SMSENSOR (0xC050)
#define PUB_GROUP_ADDRESS_GATEWAY_MODEL_SMSENSOR (0xC051)
#define SMSENSOR_MODEL_ID_GATEWAY (0x2008)
#define SMSENSOR_MODEL_ID_NODE (0x2009)

/* for humidity temperature sensor model. */
#define SUB_GROUP_ADDRESS_GATEWAY_MODEL_THSENSOR (0xC060)
#define PUB_GROUP_ADDRESS_GATEWAY_MODEL_THSENSOR (0xC061)
#define THSENSOR_MODEL_ID_GATEWAY (0x2010)
#define THSENSOR_MODEL_ID_NODE (0x2011)

#endif /* HUNONIC_MODEL_CONFIG_H__ */