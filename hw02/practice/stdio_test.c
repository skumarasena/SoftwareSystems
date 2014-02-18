/*
Practicing with stdin and stdout, using fprintf
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <unistd.h>
// #include <ctype.h>


/*
Asks user for lucky numbers and a fortune, then prints them out.
*/
void fortune_cookie() {
	int num1;
	int num2;
	int random;

	char *answer1 = (char *) malloc(sizeof(char)*1);
	char *answer2 = (char *) malloc(sizeof(char)*1);

	char *cliche = (char *) malloc(sizeof(char)*80);
	char *file_name = (char *) malloc(sizeof(char)*80);
	FILE *out_file;

	char cliches[][80] = {
		"A journey of a thousand miles begins with a single step.",
		"What will be, will be.", 
		"Do unto others as you would have them do unto you.", 
		"Don't worry, be happy.", 
		"I'm running out of things to say.", 
		"Everything's going to be fine.",
		"We're all going to hell in a handbasket.",
		"DUCK!!!"
		};

	printf("Enter your two lucky numbers, separated by commas: ");
	scanf("%i, %i", &num1, &num2);



	printf("Do you want to enter your fortune? (y/n) ");
	scanf("%1s", answer1);

	switch(*answer1) {
		case 'y':
			// For some reason, this will not allow you to enter the cliche!
			// printf("Enter your favorite cliche: \n");
			// fgets(cliche, 80, stdin);
			printf("Enter your favorite cliche (no spaces!): ");
			scanf("%79s", cliche);
			break;

		case 'n':
			printf("Enter a number between 1 and 8: ");
			scanf("%i", &random);

			if((random < 1) || (random > 8)) {
				fprintf(stderr, "Sorry, I don't recognize that number. \n");
				exit(1);
			} else {
				cliche = cliches[random-1];
			}
			break;

		default:
			fprintf(stderr, "Sorry, I don't recognize that letter. \n");
			exit(1);
	}

	printf("Do you also want your fortune in a file? (y/n) ");
	scanf("%1s", answer2);

	switch(*answer2) {
		case 'y':
			printf("Awesome! Enter a file name: ");
			scanf("%79s", file_name);
			out_file = fopen(file_name, "w");
			fprintf(out_file, "Here is your fortune:\n Lucky numbers: %i, %i.\n Your fortune: %s\n", num1, num2, cliche);
			fclose(out_file);
			free(file_name);
			break;

		case 'n':
			printf("Aww. I'll just print your fortune below, then. \n\n");
			break;

		default:
			fprintf(stderr, "Sorry, I don't recognize that letter. \n");
			exit(1);
	}

	printf("Here is your fortune:\n Lucky numbers: %i, %i.\n Your fortune: %s\n", num1, num2, cliche);


	free(answer1);
	free(answer2);
}

/*
Reverses a character array in-place, and returns the reversed string.
*/

char *reverse_line(char *str) {
    char temp, *src, *dest;
    size_t len;
    if (str != NULL)
    {
        len = strlen (str);
        if (len > 1) {
            src = str;
            dest = src + len - 1;
            while (src < dest) {
                temp = *src;
                *src++ = *dest;
                *dest-- = temp;
            }
        }
    }
    return str;
}

/*
Reads from a file, reverses the text in each line, and puts the reversed text in another file.
*/

void reverse(FILE *in_file) {

	// Counts number of rows in file
	// Try functionalizing later

	char temp[80];
	int rows = 0;
	while(fgets(temp, sizeof(temp), in_file) != NULL) {
		++rows;
	}

	// moves the file-reading pointer back to the beginning of the file
	rewind(in_file);

	// Creating the output file
	FILE *out_file;
	char *file_name = (char *) malloc(sizeof(char)*80);
	printf("Enter the name of the output file: ");
	scanf("%79s", file_name);
	out_file = fopen(file_name, "w");

	// Writing each line to the output file
	char lines[rows][80];

	int i;
	for(i=0; i<rows; i++) {
		// getting each line from the input file
		fgets(lines[i], sizeof(lines[i]), in_file);

		// reversing each line and putting it in the output file
		char *rev_line = (char *) malloc(sizeof(char)*80);
		rev_line = reverse_line(lines[i]);
		fprintf(out_file, rev_line);

		// Prints the reversed text to the terminal
		printf("%s\n", rev_line);
	}
}


void main() {
	// fortune_cookie();
	FILE *i_file = fopen("fortune.txt", "r");
	reverse(i_file);

}
