#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "bignum.h"

int main() {
	
	struct timeval time_start;
	struct timeval time_end;
	gettimeofday(&time_start, 0);

	bignum array = intToBignum(23456);
	bignum new = intToBignum(100);
	bigExponent(&array, new);
	printBignum(array);
	free(array);
	free(new);

	gettimeofday(&time_end, 0);
	fprintf(stderr, "%10.6lf\n", time_end.tv_sec - time_start.tv_sec + ((time_end.tv_usec - time_start.tv_usec) / 1000000.0));


	return(0);
}
