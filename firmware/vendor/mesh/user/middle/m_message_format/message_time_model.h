#ifndef MESSAGE_TIME_MODEL_H__
#define MESSAGE_TIME_MODEL_H__

#include <stdint.h>

enum time_message_rep_type_t
{
    TIME_MESSAGE_REP_TYPE_NOT_SUPPORT = 0, /* not support. */
    TIME_MESSAGE_REP_TYPE_REP_INFO,        /* reply device. */
};

typedef struct __attribute((packed))
{
    uint32_t timeStamp;
    uint16_t year;
    uint8_t mth;
    uint8_t day;
    uint8_t dow;
    uint8_t hr;
    uint8_t min;
    uint8_t sec;
} time_message_info_t;

typedef struct __attribute((packed))
{
    uint8_t type; // @see: time_message_rep_type_t
    uint8_t tid;  // transition id
    uint8_t uid;  // user id

    union __attribute((packed))
    {
        time_message_info_t info;
    } payload;
} time_message_rep_t;

#endif /* MESSAGE_TIME_MODEL_H__ */