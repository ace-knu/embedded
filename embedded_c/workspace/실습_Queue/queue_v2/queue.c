#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int init(queue_t *q, int len)
{
    q->data = (int*)malloc(sizeof(int) * len);
    if (q->data == NULL)
        return E_MEMORY_ALLOC_FAIL;

    q->front = 0;
    q->rear = 0;
    q->len = len;
    return E_OK;
}

int deinit(queue_t *q)
{
    free(q->data);
    return E_OK;
}

int enq(queue_t *q, int value)
{
    int rear = q->rear;
    int len = q->len;
    int front = q->front;
    int q_len; // 큐 사용량

    // Check if this queue is full
    q_len = (front > rear)? rear+len : rear;
    q_len -= front;
    if (q_len == (len - 1)) {
        printf("Queue is full\n");
        return E_QUEUE_FULL;
    }
    *(q->data + rear) = value; //데이터 저장
    rear++;
    if (rear == len)
        rear = 0;
    q->rear = rear;
    return E_OK;
}

int deq(queue_t *q, int *value)
{
    int front = q->front;
    int rear = q->rear;
    int len = q->len;
    int q_len = 0;

    if (front == rear) {
        printf("Queue is empty\n");
        return E_QUEUE_EMPTY;
    }

    *value = *(q->data + front);
    front++;
    if (front == len)
        front = 0;
    
    q->front = front;
    return E_OK;
}

int printq(queue_t *q)
{
    for (int i = q->front; i != q->rear; i++) {
        if (i == q->len) i = 0;
        printf("%d -> ", *(q->data + i));
    }
    printf("\n");
    return E_OK;
}