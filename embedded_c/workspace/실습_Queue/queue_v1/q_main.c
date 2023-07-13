#include "queue.h"

int main()
{
    int data[MAX_QUEUE_SIZE];
    int front = 0, rear = 0, value = 10;

    dequeue(data, &front, rear, &value); // Empty
    enqueue(data, front, &rear, 10);
    enqueue(data, front, &rear, 20);
    enqueue(data, front, &rear, 30);
    enqueue(data, front, &rear, 40);
    enqueue(data, front, &rear, 50);
    enqueue(data, front, &rear, 60);
    enqueue(data, front, &rear, 70);
    enqueue(data, front, &rear, 80); // Full
    printQ(data, front, rear);
    dequeue(data, &front, rear, &value);
    dequeue(data, &front, rear, &value);
    printQ(data, front, rear);
}