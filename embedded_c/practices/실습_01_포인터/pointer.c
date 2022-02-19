#include <stdio.h>

// #define Ex1 
#define Ex2 

int main(int argc, char* argv[])
{
#ifdef Ex1
    /* Example 1 : size of data & ptr data type */
    fprintf(stdout, "===== Size of data type =====\n");
    fprintf(stdout, "Size of char : %d\n", sizeof(char));
    fprintf(stdout, "Size of short : %d\n", sizeof(short));
    fprintf(stdout, "Size of int : %d\n", sizeof(int));
    fprintf(stdout, "Size of double : %d\n", sizeof(double));
    fprintf(stdout, "Size of float : %d\n", sizeof(float));
    fprintf(stdout, "Size of long : %d\n", sizeof(long));
    fprintf(stdout, "Size of long long : %d\n", sizeof(long long));

    fprintf(stdout, "\n===== Size of pointer data type ======\n");
    fprintf(stdout, "Size of char * : %d\n", sizeof(char *));
    fprintf(stdout, "Size of short * : %d\n", sizeof(short *));
    fprintf(stdout, "Size of int * : %d\n", sizeof(int *));
    fprintf(stdout, "Size of double * : %d\n", sizeof(double *));
    fprintf(stdout, "Size of float * : %d\n", sizeof(float *));
    fprintf(stdout, "Size of long * : %d\n", sizeof(long *));
    fprintf(stdout, "Size of long long * : %d\n", sizeof(long long *));
#endif

#ifdef Ex2
    /* Example 2 : Calculating address and value with ptr  */
    int a = 0x12345678;
    int *a_ptr = &a;

    fprintf(stdout, "========== Test 1 ==========\n");
    fprintf(stdout, "Address of a :                %p\n", &a);
    fprintf(stdout, "Address of *a_ptr :           %p\n", &a_ptr);
    fprintf(stdout, "Stored address in *a_ptr :    %p\n", a_ptr);
    fprintf(stdout, "Data pointed by a_ptr :       0x%x\n", *a_ptr);

    fprintf(stdout, "\n========== Test 2 ==========\n");
    fprintf(stdout, "Data pointed by int ptr :      0x%x\n", *a_ptr);
    fprintf(stdout, "Data pointed by short ptr :    0x%x\n", *(short *)a_ptr);
    fprintf(stdout, "Data pointed by char ptr :     0x%x\n", *(char *)a_ptr);

    char *ch_ptr = (char *)a_ptr;

    fprintf(stdout, "\n========== Test 3 ==========\n");
    fprintf(stdout, "data(0) : 0x%x\n", *(ch_ptr++));
    fprintf(stdout, "data(1) : 0x%x\n", *(ch_ptr++));
    fprintf(stdout, "data(2) : 0x%x\n", *(ch_ptr++));
    fprintf(stdout, "data(3) : 0x%x\n", *(ch_ptr));
#endif
    return 0;
}
