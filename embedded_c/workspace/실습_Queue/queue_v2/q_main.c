#include "queue.h"

int main()
{
    queue_t q;
    int value = 0;

    init(&q, 8);

    deq(&q, &value); 
    enq(&q, 10); enq(&q, 20); enq(&q, 30); enq(&q, 40);
    enq(&q, 50); enq(&q, 60); enq(&q, 70); enq(&q, 80);
    printq(&q);

    deq(&q, &value); deq(&q, &value); 
    deq(&q, &value); deq(&q, &value);
 
    printq(&q);
    enq(&q, 10);
    enq(&q, 20);
    printq(&q);
    deinit(&q);
}