#ifndef _HUNONIC_OPCODES_H_
#define _HUNONIC_OPCODES_H_

typedef enum 
{
    //* for hunonic model
    OPCODE_COMMON_2_GATEWAY = 0xC0,
    OPCODE_GATEWAY_2_COMMON = 0xC1,

    /* dfu */
    OPCODE_DFU_2_GATEWAY = 0xC2,
    OPCODE_GATEWAY_2_DFU = 0xC3,

    //* for model switch
    OPCODE_SWITCH_2_GATEWAY = 0xD0,
    OPCODE_GATEWAY_2_SWITCH = 0xD1,

    //* for model ocsensor
    OPCODE_OCSENSOR_2_GATEWAY = 0xD2,
    OPCODE_GATEWAY_2_OCSENSOR = 0xD3,

    //* for model mtsensor
    OPCODE_MTSENSOR_2_GATEWAY = 0xD4,
    OPCODE_GATEWAY_2_MTSENSOR = 0xD5,

    //* for model smsensor
    OPCODE_SMSENSOR_2_GATEWAY = 0xD6,
    OPCODE_GATEWAY_2_SMSENSOR = 0xD7,

    //* for model thsensor
    OPCODE_THSENSOR_2_GATEWAY = 0xD8,
    OPCODE_GATEWAY_2_THSENSOR = 0xD9,
} hunonic_opcodes_t;

#endif //_HUNONIC_OPCODES_H_