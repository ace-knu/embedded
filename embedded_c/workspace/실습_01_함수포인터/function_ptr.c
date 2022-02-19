#include <stdio.h>

// #define Ex1
#define Ex2

int add(int num1, int num2);
int sub(int num1, int num2);
int mul(int num1, int num2);

int main(void)
{
#ifdef Ex1
    int (*func)(int, int);

    func = add;
	fprintf(stdout, "add(3, 5) : %d\n", func(3, 5));

	func = sub;
	fprintf(stdout, "sub(3, 5) : %d\n", func(3, 5));

	func = mul;
	fprintf(stdout, "mul(3, 5) : %d\n", func(3, 5));
#endif

#ifdef Ex2
    int (*func_ptr[3])(int, int) = {add, sub, mul};

    for(int i=0; i<3; i++)
    {
        fprintf(stdout, "Result of func_ptr[%d] : %d\n", i, func_ptr[i](3, 5));
    }

#endif
    return 0;
}

int add(int num1, int num2){
	return num1 + num2;
}

int sub(int num1, int num2){
	return num1 - num2;
}

int mul(int num1, int num2){
	return num1 * num2;
}
