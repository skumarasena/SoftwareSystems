/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n, char fillchar)
{
    int len = strlen(s);
    int num_fill = n - len;

    //n+1 includes null terminator
    char *res = (char *) malloc ((n+1) * sizeof(char));
    res[0] = '\0';
    char *str = res;

    int i;
    for (i = 0; i < num_fill/2; i++) {
        str[i] = fillchar;
    }

    for(i = 0; i < strlen(s); i++) {
        str[i + num_fill/2] = s[i];
    }

    for(i = 0; i < n - (strlen(s) + num_fill/2); i++) {
        str[i + num_fill/2 + strlen(s)] = fillchar;
    }

    return res;

}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, '*');
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, '^');
    printf("%s\n", s4);

    char *s5 = center("allen", 10, '.');
    printf("%s\n", s5);

    return 0;
}
