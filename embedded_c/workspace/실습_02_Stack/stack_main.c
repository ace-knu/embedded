#include <stdio.h>
#include "stack.h"

int main()
{
    status_t ret_value;

    ret_value = init();
    if (ret_value != E_OK) {
        printf("Error: init() - %d\n", ret_value);
    }

    push(10);
    push(5);
    push(7);
    push(8);

    int data = 0;
    pop(&data);
    printf("data = %d\n", data);
    pop(&data);
    printf("data = %d\n", data);
    pop(&data);
    printf("data = %d\n", data);
    pop(&data);
    printf("data = %d\n", data);

}