#ifndef _QUEUE_H_
#define _QUEUE_H_

#define E_OK            0
#define E_QUEUE_FULL    1
#define E_QUEUE_EMPTY   2
#define E_MEMORY_ALLOC_FAIL 3

typedef struct {
    int *data;
    int front;
    int rear;
    int len;
} queue_t;

int init(queue_t*, int);
int deinit(queue_t*);
int enq(queue_t*, int);
int deq(queue_t*, int*);
int printq(queue_t*);

#endif