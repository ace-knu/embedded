#ifndef _QUEUE_H_
#define _QUEUE_H_

#define MAX_QUEUE_SIZE 8

#define E_OK            0
#define E_QUEUE_FULL    1
#define E_QUEUE_EMPTY   2

int enqueue(int[], int, int*, int);
int dequeue(int[], int*, int, int*);
int printQ(int[], int, int);

#endif