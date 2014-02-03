/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    //local variables -- stack allocated
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
	array[i] = 17;
    }
    return array;
    //after the function ends, the local variable disappears, meaning
    //that the pointer refers to a variable that no longer exists!
}

void bar() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
	array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();
    //you will see what bar has assigned to array, not foo!
    for (i=0; i<SIZE; i++) {
	printf("%d\n", array[i]);
    }

    return 0;
}
