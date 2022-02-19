#include<stdio.h>

#define EX1

int main(int argc, char *argv[])
{
#ifdef EX1
	/* Example 1 : byte ordering of data (little endian) */
	int a = 0x12345678;
	char *ch_ptr = (char *)&a;

	fprintf(stdout, "================== Test 1 ==================\n");
	fprintf(stdout, "Address of 'a' :		%p\n", &a);
	fprintf(stdout, "Data of 'a' :			0x%x\n", a);
	fprintf(stdout, "Data in address(%p) :	0x%x\n", ch_ptr, *(ch_ptr));
	fprintf(stdout, "Data in address(%p) :	0x%x\n", ch_ptr+1, *(ch_ptr+1));
	fprintf(stdout, "Data in address(%p) :	0x%x\n", ch_ptr+2, *(ch_ptr+2));
	fprintf(stdout, "Data in address(%p) :	0x%x\n", ch_ptr+3, *(ch_ptr+3));
#endif

	return 0;
}

