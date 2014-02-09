/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <regex.h>
#include <sys/types.h>


#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.

// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	if (strstr(tracks[i], search_for)) {
	    printf("Track %i: '%s'\n", i, tracks[i]);
	}
    }
}


// Finds all tracks that match the given pattern.
//
// Prints track number and title.
//
// Modified version of Per-Olof Pettersson's "Example of POSIX regex in C"
// Example: http://www.peope.net/old/regex.html

void find_track_regex(char pattern[])
{
    int i;
    int count = 0;
    char msgbuff[100];
    
    for (i = 0; i < NUM_TRACKS; i++) {
        regex_t regex;
        int reti;

        //Checks whether regex compiles. If not, prints an error.
        reti = regcomp(&regex, pattern, 0);

        if(reti) {  //regcomp returns 0 when unsuccessful
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }

        //Executes the regex, prints the result
        reti = regexec(&regex, tracks[i], 0, NULL, 0);
        if(!reti) {
            printf("Matches track %i: '%s'\n", i, tracks[i]);
            count++;
        }
        regfree(&regex);
    }

    //If no tracks match the pattern, print an error
    if (!count) {
        fprintf(stderr, "Regex match failed\n", msgbuff);
    }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    //find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
