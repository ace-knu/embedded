#include <stdio.h>
#include <time.h>

void fixed_cal(int a, int b, float* result){
	// add
	for(int i=0; i<500000; i++){ a += b; }
	result[0] = a;
	// sub
	for(int i=0; i<500000; i++){ a -= b; }
	result[1] = a;
}

void floating_cal(float a, float b, float* result){
	// add
	for(int i=0; i<500000; i++){ a += b; }
	result[0] = a;
	// sub
	for(int i=0; i<500000; i++){ a -= b; }
	result[1] = a;
}

int main(int argc, char* argv[]){
	clock_t start, end;
	float a = 3.141;
	float b = 2.178;
	float result[2]= {0};


	// fixed point calculation
	int a_int = a*1000;
	int b_int = b*1000;
	start = clock();
	fixed_cal(a_int, b_int, result);
	end = clock();
	printf("fixed-point calculation time : %fms\n", (double)(end-start));
	for(int i=0; i<2; i++){
		printf("fixed-point calculation result[%d] : %f\n",i, result[i]/1000);
	}

	 //floating point calculation
	start = clock();
	floating_cal(a, b, result);
	end = clock();
	printf("floating-point calculation time : %fms\n", (double)(end-start));
	for(int i=0; i<2; i++){
		printf("floating-point calculation result[%d] : %f\n",i, result[i]);
	}

}
