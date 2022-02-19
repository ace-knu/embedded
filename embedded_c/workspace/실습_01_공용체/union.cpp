#include <stdio.h>

#define EX1
//#define EX2

#ifdef EX1

union Box{
	int a;
	short b;
	char c;
};

int main(int argc, char* argv[]){
	union Box b1;

	fprintf(stdout, "Box union size : %d\n", sizeof(b1));

	b1.a = 0x12345678;
	fprintf(stdout, "Box.a data: 0x%x\n", b1.a);
	fprintf(stdout, "Box.b data: 0x%x\n", b1.b);
	fprintf(stdout, "Box.c data: 0x%x\n", b1.c);
	fprintf(stdout, "====================\n");
	fprintf(stdout, "Box.a address: %p\n", &(b1.a));
	fprintf(stdout, "Box.b address: %p\n", &(b1.b));
	fprintf(stdout, "Box.c address: %p\n", &(b1.c));

}


#endif


#ifdef EX2

union IP_addr{
	unsigned int ipv4;
	struct {
		unsigned int addr4 : 8;
		unsigned int addr3 : 8;
		unsigned int addr2 : 8;
		unsigned int addr1 : 8;
	};
};

int main(int argc, char* argv[]){
	union IP_addr host;
	host.addr4 = 127;
	host.addr3 = 0;
	host.addr2 = 0;
	host.addr1 = 1;

	fprintf(stdout, "host ipv4 : 0x%x\n", host.ipv4); // little-endian
	fprintf(stdout, "host ipv4 : %u.%u.%u.%u\n", host.addr4, host.addr3,host.addr2,host.addr1);

}

#endif
