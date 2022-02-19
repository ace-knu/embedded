#include <stdio.h>

#define EX1
//#define EX2
//#define EX3

#ifdef EX1

//declaration
struct mydata{
	int a;
	int b;
};

//declaration & initialization
struct mydata2{
	int a;
	char b;
	short c;
}object2;

//declaration with typedef
typedef struct {
	char c;
	int a;
	short b;
} mydata3;

int main(int argc, char* argv[])
{
	struct mydata object1;
	// object2;
	struct mydata2 object3;
	mydata3 object4;

	fprintf(stdout, "mydata struct size : %d\n", sizeof(object1));
	fprintf(stdout, "mydata2 struct size : %d\n", sizeof(object2));
	fprintf(stdout, "mydata2 struct size : %d\n", sizeof(object3));
	fprintf(stdout, "mydata3 struct size : %d\n", sizeof(object4));

}

#endif


#ifdef EX2

//declaration & initialization
struct mydata2{
	int a;
	char b;
	short c;
}object2;

//declaration with typedef
typedef struct {
	char c;
	int a;
	short b;
} mydata3;

typedef struct {
	short b;
	double d;
}mydata4;

int main(int argc, char* argv[])
{
	mydata3 object4;
	mydata4 object5;

	fprintf(stdout, "mydata2 size : %d\n", sizeof(object2));
	fprintf(stdout, "mydata2 int size   : %d\n", sizeof(object2.a));
	fprintf(stdout, "mydata2 char size  : %d\n", sizeof(object2.b));
	fprintf(stdout, "mydata2 short size : %d\n", sizeof(object2.c));
	fprintf(stdout, "==========================\n");
	fprintf(stdout, "mydata3 size : %d\n", sizeof(object4));
	fprintf(stdout, "mydata3 char size  : %d\n", sizeof(object4.c));
	fprintf(stdout, "mydata3 int size   : %d\n", sizeof(object4.a));
	fprintf(stdout, "mydata3 short size : %d\n", sizeof(object4.b));
	fprintf(stdout, "==========================\n");
	fprintf(stdout, "mydata4 size : %d\n", sizeof(object5));
	fprintf(stdout, "mydata4 short size  : %d\n", sizeof(object5.b));
	fprintf(stdout, "mydata4 double size : %d\n", sizeof(object5.d));
	fprintf(stdout, "==========================\n");
	fprintf(stdout, "mydata2 address : %p\n", &object2);
	fprintf(stdout, "mydata2 int address   : %p\n", &(object2.a));
	fprintf(stdout, "mydata2 char address  : %p\n", &(object2.b));
	fprintf(stdout, "mydata2 short address : %p\n", &(object2.c));
	fprintf(stdout, "==========================\n");
	fprintf(stdout, "mydata3 address : %p\n", &object4);
	fprintf(stdout, "mydata3 char address  : %p\n", &(object4.c));
	fprintf(stdout, "mydata3 int address   : %p\n", &(object4.a));
	fprintf(stdout, "mydata3 short address : %p\n", &(object4.b));
	fprintf(stdout, "==========================\n");
	fprintf(stdout, "mydata4 address : %p\n", &object5);
	fprintf(stdout, "mydata4 short address  : %p\n", &(object5.b));
	fprintf(stdout, "mydata4 double address : %p\n", &(object5.d));
}


#endif

#ifdef EX3

struct bit_field {
	unsigned int a : 1;
	unsigned int b : 3;
	unsigned int c : 7;
}flag;

int main(int argc, char* argv[])
{
	flag.a = 1;		// 1bit (1)
	flag.b = 15;	// 4bit (1111)
	flag.c = 255;	// 8bit (1111 1111)

	fprintf(stdout, "flag.a : %u\n", flag.a);
	fprintf(stdout, "flag.b : %u\n", flag.b);	// only 3bit
	fprintf(stdout, "flag.c : %u\n", flag.c);	// only 7bit

	// can't make bit-field pointer
//	fprintf(stdout, "flag.a address : %p\n", &(flag.a));
//	fprintf(stdout, "flag.b address : %p\n", &(flag.b));
//	fprintf(stdout, "flag.c address : %p\n", &(flag.c));
}
#endif
