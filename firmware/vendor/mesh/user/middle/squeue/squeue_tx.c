#include "squeue_tx.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t sq_tx_init(sq_tx_t *queue, uint32_t sizeof_item, uint32_t num_items)
{
    if (sizeof_item == 0 || num_items == 0) {
        return 0;
    }

    if ((MAX_QUEUE_TX_SIZE / sizeof_item) > num_items) {
        queue->num_items = num_items;
    } else {
        queue->num_items = MAX_QUEUE_TX_SIZE / sizeof_item;
    }

    queue->sizeof_item = sizeof_item;
    queue->head = 0;
    queue->tail = 0;
    memset(queue->buffer, 0, sizeof(queue->buffer));

    return 1;
}

/* private function */
static void sq_tx_inc_tail(sq_tx_t *queue)
{
    queue->tail++;
    if (queue->tail >= queue->num_items) {
        queue->tail = 0;
    }
}

/* private function */
static void sq_tx_inc_head(sq_tx_t *queue)
{
    queue->head++;
    if (queue->head >= queue->num_items) {
        queue->head = 0;
    }
}

uint8_t sq_tx_is_empty(sq_tx_t *queue)
{
    if (queue->head == queue->tail) {
        return 1;
    }

    return 0;
}

uint8_t sq_tx_is_full(sq_tx_t *queue)
{
    if (queue->head == 0 && queue->tail == queue->num_items - 1) {
        return 1;
    }

    else if (queue->tail == queue->head - 1) {
        return 1;
    }

    return 0;
}

uint8_t sq_tx_push(sq_tx_t *queue, void *item)
{
    if (sq_tx_is_full(queue)) {
        return 0;
    }

    memcpy(queue->buffer + queue->tail * queue->sizeof_item, item, queue->sizeof_item);
    sq_tx_inc_tail(queue);

    return 1;
}

uint8_t sq_tx_pop(sq_tx_t *queue, void *item)
{
    if (sq_tx_is_empty(queue)) {
        return 0;
    }
    
    memset(item, 0, queue->sizeof_item);
    memcpy(item, queue->buffer + queue->head * queue->sizeof_item, queue->sizeof_item);
	memset(queue->buffer + queue->head * queue->sizeof_item, 0, queue->sizeof_item);
    sq_tx_inc_head(queue);

    return 1;
}


