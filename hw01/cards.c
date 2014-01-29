#include <stdio.h>
#include <stdlib.h>
/*
Prompts the user for a playing card name, then counts cards based
on user input.
Authors: Samantha Kumarasena, Head First C
*/


/*
Prints an error when the card value is invalid.
val: value of card provided by user
*/
int print_error(int val) {
	if((val<1) || (val>10)) {
	puts("I don't understand that value!");
	}
	return 0;
}

/*
Changes the card count depending on the value of the card.
val: value of card provided by user
*/
int change_count(int val) {
	int c = 0;
	if ((val>2) && (val<7)) {
		c++;
	} else if (val == 10) {
		c--;
	}
	return c;
}

int main() {
	char card_name[3];
	int count;
	do {
		int val;
		puts("Enter the card name: ");
		scanf("%2s", card_name);


		switch(card_name[0]) {
			case 'K':
			case 'Q':
			case 'J':
				val = 10;
				break;
			case 'A':
				val = 11;
				break;
			case 'X':
				continue;
			default:
				val = atoi(card_name);
				print_error(val);
				continue;
		}
		count = change_count(val);
		printf("Current count: %i\n", count);
	} while (card_name[0] != 'X');
	return 0;
}

