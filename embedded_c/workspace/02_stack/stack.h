#ifndef _STACK_H_
#define _STACK_H_

#define MAX_STACK_SIZE 10

extern int test;

typedef int status_t;

#define E_OK            0
#define E_STACK_FULL    1
#define E_STACK_EMPTY   2

status_t push(int);
status_t pop(int*);
status_t init();

#endif