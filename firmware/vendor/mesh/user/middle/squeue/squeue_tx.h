#ifndef _SQUEUE_TX_H_
#define _SQUEUE_TX_H_
/*
 * Copyright (c) 2021 <Hunonic>
 * Author		: dungnt98
 * Email		: nguyentrongdung0498@gmail.com
 * Create on	: 2021/12/15
 *
 * brief: Static Queue Library
 */

#include <stdint.h>

#define MAX_QUEUE_TX_SIZE  (1000)  

typedef struct {
    uint32_t sizeof_item;
    uint32_t num_items;
    uint32_t head;
    uint32_t tail;
    uint8_t buffer[MAX_QUEUE_TX_SIZE];
} sq_tx_t;

uint8_t sq_tx_init(sq_tx_t *queue, uint32_t sizeof_item, uint32_t num_items);
uint8_t sq_tx_push(sq_tx_t *queue, void *item);
uint8_t sq_tx_pop(sq_tx_t *queue, void *item);
uint8_t sq_tx_is_empty(sq_tx_t *queue);
uint8_t sq_tx_is_full(sq_tx_t *queue);
void sq_tx_free(sq_tx_t *queue);

#endif