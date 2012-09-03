#include <stdio.h>
#include <stdlib.h>
#include <breakpoint.h>


int main(void){

	printf("start using breakpoints\n");
	BREAKPOINTS;
	printf("end test\n");
	BREAKPOINTS;
	return EXIT_SUCCESS;
};

