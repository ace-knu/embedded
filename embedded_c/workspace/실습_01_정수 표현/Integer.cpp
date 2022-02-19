#include<stdio.h>

#define EX1

int main(int argc, char *argv[])
{
#ifdef EX1
	/* Example 1 : signed & unsigned integer */
	int sint;
	unsigned int uint;

	sint = 0x12345678;
	uint = 0x12345678;
	fprintf(stdout, "================== Test 1 ==================\n");
	fprintf(stdout, "Value of the signed integer :	%d\n", sint);
	fprintf(stdout, "Value of the unsigned integer :	%u\n", uint);

	sint = 0x87654321;
	uint = 0x87654321;
	fprintf(stdout, "\n================== Test 2 ==================\n");
	fprintf(stdout, "Value of the signed integer :	%d\n", sint);
	fprintf(stdout, "Value of the unsigned integer :	%u\n", uint);
#endif

	return 0;
}

