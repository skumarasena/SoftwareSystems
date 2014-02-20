#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

int main() {

	char *i = strchr("Samantha Kumarasena", 'a');
	printf("%p\n", i);
	char *j = strstr("Samantha Kumarasena", "Sam");
	printf("%p\n", j);

	int k = strcmp("Hi", "Hello");
	printf("%i\n", k);


	return 0;
}