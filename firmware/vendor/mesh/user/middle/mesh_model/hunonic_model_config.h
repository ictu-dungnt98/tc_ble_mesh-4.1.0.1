#ifndef HUNONIC_MODEL_CONFIG_H__
#define HUNONIC_MODEL_CONFIG_H__

#define ACCESS_MODEL_VENDOR(id, company) ((id << 16) | company)

#define ACCESS_COMPANY_ID_NORDIC 0x0059
#define ACCESS_COMPANY_ID_HUNONIC ACCESS_COMPANY_ID_NORDIC

/*
**  Format:
**  SUB_GROUP_ADDRESS_GATEWAY_MODEL_##NAME
**  PUB_GROUP_ADDRESS_GATEWAY_MODEL_##NAME
**
**  NAME##MODEL_ID_GATEWAY
**  NAME##MODEL_ID_NODE
*/

#define ACCESS_HANDLE_INVALID   (0xFFFF)
#define HEALTH_SERVER_MODEL_ID  0x0002

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

typedef enum
{
    //* for hunonic model
    HUNONIC_OPCODE_GATEWAY_COMMON_RX = 0xC0,
    HUNONIC_OPCODE_GATEWAY_COMMON_TX = 0xC1,
    HUNONIC_OPCODE_GATEWAY_DFU_RX = 0xC2,
    HUNONIC_OPCODE_GATEWAY_DFU_TX = 0xC3,

    //* for model switch
    HUNONIC_OPCODE_GATEWAY_SWITCH_RX = 0xD0,
    HUNONIC_OPCODE_GATEWAY_SWITCH_TX = 0xD1,

    //* for model ocsensor
    HUNONIC_OPCODE_GATEWAY_OCSENSOR_RX = 0xD2,
    HUNONIC_OPCODE_GATEWAY_OCSENSOR_TX = 0xD3,

    //* for model mtsensor
    HUNONIC_OPCODE_GATEWAY_MTSENSOR_RX = 0xD4,
    HUNONIC_OPCODE_GATEWAY_MTSENSOR_TX = 0xD5,

    //* for model smsensor
    HUNONIC_OPCODE_GATEWAY_SMSENSOR_RX = 0xD6,
    HUNONIC_OPCODE_GATEWAY_SMSENSOR_TX = 0xD7,

    //* for model thsensor
    HUNONIC_OPCODE_GATEWAY_THSENSOR_RX = 0xD8,
    HUNONIC_OPCODE_GATEWAY_THSENSOR_TX = 0xD9,
} hunonic_opcodes_t;


#endif /* HUNONIC_MODEL_CONFIG_H__ */