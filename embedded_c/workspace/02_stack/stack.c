#include "stack.h"

static int d[MAX_STACK_SIZE];
static int sp = 0;
int test;

status_t push(int data)
{
    if (sp > (MAX_STACK_SIZE-1)) return E_STACK_FULL;

    d[sp++] = data;

    return E_OK;
}

status_t pop(int *data)
{
    if (sp < 1) return E_STACK_EMPTY;

    *data = d[--sp];

    return E_OK;
}

status_t init()
{
    for (int i; i < MAX_STACK_SIZE; i++)
        d[i] = 0;

    return E_OK;
}
