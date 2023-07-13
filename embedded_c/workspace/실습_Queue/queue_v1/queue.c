#include <stdio.h>
#include "queue.h"

int enqueue(int q[], int f, int *r, int v)
{
    int rear = *r;
    int len = 0;

    len = (f > rear)? rear+8 : rear;
    if ((len - f) == (MAX_QUEUE_SIZE-1)) {
        printf("Queue is full\n");
        return E_QUEUE_FULL;
    }
    q[rear] = v;
    (rear++) % MAX_QUEUE_SIZE;
    *r = rear;
}

int dequeue(int q[], int *f, int r, int *v)
{
    int front = *f;
    if (front == r) {
        printf("Queue is empty\n");
        return E_QUEUE_EMPTY;
    }
    *v = q[front];
    (front++) % MAX_QUEUE_SIZE;
    *f = front;
}

int printQ(int q[], int f, int r)
{
    for (int i = f; i != r; (i++)%MAX_QUEUE_SIZE) {
        printf("%d  ", q[i]);
    }
    printf("\n");
}