#include <stdio.h>

//#define Ex1
#define Ex2
// #define Ex3

int main(void)
{
#ifdef Ex1
    /* Example 1 : Relationship between pointer and array  */
    int arr[3] = {1, 2, 3};
    int *arr_ptr = arr;

    fprintf(stdout, "Access array elements by index of array :     %d %d %d\n", arr[0], arr[1], arr[2]);
    fprintf(stdout, "Access array elements by index of pointer :   %d %d %d\n", arr_ptr[0], arr_ptr[1], arr_ptr[2]);
    fprintf(stdout, "Access array elements by pointer :            %d %d %d\n", *(arr_ptr), *(arr_ptr+1), *(arr_ptr+2));
    fprintf(stdout, "Access array elements by name of array :      %d %d %d\n", *(arr), *(arr+1), *(arr+2));
    fprintf(stdout, "Size of array using name of array :           %d\n", sizeof(arr));
    fprintf(stdout, "Size of array using pointer? :                %d\n", sizeof(arr_ptr)); // size of ptr variable

#endif

#ifdef Ex2
    /* Example 2 : 2-Dimention array */
    int arr[2][3] = {{0, 1, 2}, {3, 4, 5}};

    fprintf(stdout, "Address of arr :      %p\n", arr);
    fprintf(stdout, "Address of &arr+1 :   %p\n", &arr+1);
    fprintf(stdout, "Address of arr+1 :    %p\n", arr+1);
    fprintf(stdout, "Address of *arr+1 :   %p\n", *arr+1);
    fprintf(stdout, "Element of arr :      %d\n", *(*arr));
    fprintf(stdout, "Element of *arr+1 :   %d\n", *(*arr+1));
    fprintf(stdout, "Element of arr+1 :    %d\n", *(*(arr+1)));
    fprintf(stdout, "Element of arr+1 :    %d\n", (*(arr+1))[1]);
    
    fprintf(stdout, "\n========== Array information ===========\n");
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            fprintf(stdout, "arr[%d][%d] : %d | Address : %p\n", i, j, *(*(arr+i)+j), *(arr+i)+j);
        }
    }
    fprintf(stdout, "========================================\n");    
    
#endif

#ifdef Ex3
    /* Example 3 : 3-Dimention array */
    int arr[2][3][2] = { {{0, 1},{2, 3},{4, 5}}, {{6, 7},{8, 9},{10, 11}} };
    
    fprintf(stdout, "Address of arr :      %p\n", arr);
    fprintf(stdout, "Address of &arr+1 :   %p\n", &arr+1);
    fprintf(stdout, "Address of arr+1 :    %p\n", arr+1);
    fprintf(stdout, "Address of *arr+1 :   %p\n", *arr+1);
    fprintf(stdout, "Address of **arr+1 :  %p\n", **arr+1);
    fprintf(stdout, "Element of arr+1 :    %d\n", *(*(*(arr+1))));
    fprintf(stdout, "Element of *arr+1 :   %d\n", *(*(*arr+1)));  
    fprintf(stdout, "Element of **arr+1 :  %d\n", *(**arr+1));

    fprintf(stdout, "\n========== Array information ===========\n");
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<2; k++)
            {
                fprintf(stdout, "arr[%d][%d][%d] : %2d | Address : %p\n", i, j, k, *(*(*(arr+i)+j)+k), (*(*(arr+i)+j)+k));
            }
        }
    }
    fprintf(stdout, "========================================\n");
#endif
    return 0;
}