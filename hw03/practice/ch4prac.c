/*
DATA TYPES:
	char: 1 byte
	int: 4 bytes (on this machine)
	short: 1/2 the space of int
	long: >4 bytes (on this machine)
	float:
	double: more precise than float
*/

#include <stdio.h>
#include <stdlib.h>
//#include "header.h"

// Function declarations -- will put in header file!
float_fun();

/*
Casting and floats. Check out how they work.
*/
void float_fun() {
	float z1; 
	float z2; 
	float z3;	
	int x = 7;
	int y = 2;

	z1 = x/y
;	z2 = (float) x/y;
	z3 = (float)x/(float)y;

	printf("This is NOT what you want %i/%i to be: %2.2f\n", x, y, z1);
	printf("This IS what you want %i/%i to be: %2.2f\n", x, y, z2);
	printf("This IS what you want %i/%i to be: %2.2f\n", x, y, z3);
}



int main() {
	float_fun();

}