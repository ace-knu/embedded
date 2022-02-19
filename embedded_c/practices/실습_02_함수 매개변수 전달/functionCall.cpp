#include<stdio.h>

#define EX1
#define EX2

int increment_num1(int);
int increment_num2(int *);
void test_function(const int data1, const int *data2, int * const data3, const int * const data4);

int main(int argc, char *argv[])
{
#ifdef EX1
	/* Example 1 : function call by value/reference */
	int a = 5;
	int b = 5;

	fprintf(stdout, "========================= Test 1 =========================\n");
	fprintf(stdout, "Address of 'a' in 'main' :			%p\n", &a);
	fprintf(stdout, "Value of 'a' in 'main' (before function call) :	%d\n", a);
	increment_num1(a);
	fprintf(stdout, "Value of 'a' in 'main' (after function call) :	%d\n", a);

	fprintf(stdout, "\n========================= Test 2 =========================\n");
	fprintf(stdout, "Address of 'b' in 'main' :			%p\n", &b);
	fprintf(stdout, "Value of 'b' in 'main' (before function call) :	%d\n", b);
	increment_num2(&b);
	fprintf(stdout, "Value of 'b' in 'main' (after function call) :	%d\n", b);
#endif

#ifdef EX2
	/* Example 2 : function call with const keyword */
	int w = 1;
	int x = 2;
	int y = 3;
	int z = 4;

	test_function(w, &x, &y, &z);
#endif

	return 0;
}

int increment_num1(int num)
{
	num++;

	fprintf(stdout, "Address of 'num' in 'increment_num1' :		%p\n", &num);
	fprintf(stdout, "Value of 'num' in 'increment_num1' :		%d\n", num);

	return 0;
}

int increment_num2(int *num)
{
	(*num)++;

	fprintf(stdout, "Address of 'num' in 'increment_num2' :		%p\n", num);
	fprintf(stdout, "Value of 'num' in 'increment_num2' :		%d\n", *num);

	return 0;
}

void test_function(const int data1, const int *data2, int * const data3, const int * const data4)
{
	/* Modify data1 */
	data1 = 5;			// Error

	/* Modify data2 */
	data2 = &data1;
	*data2 = data1;		// Error

	/* Modify data3 */
	data3 = &data1;		// Error
	*data3 = data1;

	/* Modify data4 */
	data4 = &data1;		// Error
	*data4 = data1;		// Error
}
