/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;

void print_loc() {
	int x;
	printf("Address of x is %p\n", &x);
}

int main ()
{
    int local = 5;
    void *p = malloc(128);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    printf ("Address of p is %p\n", p);

    print_loc();

    void *q = malloc(16);
    void *r = malloc(16);

    int *i;
    i = (int *) malloc(sizeof(int));
    *i = *i + 5;
    printf("Value of i: %i\n", *i);

    printf("Address of q is %p\n", q);
    printf("Address of r is %p\n", r);
    
    return 0;
}
