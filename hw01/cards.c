#include <stdio.h>
#include <stdlib.h>

int main() {
	char card_name[3];
	int count = 0;
	do {
		puts("Enter the card name: ");
		scanf("%2s", card_name);
		int val = 0;

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

int print_error(int val) {
	if((val<1) || (val>10)) {
	puts("I don't understand that value!");
	}
	return 0;
}

int change_count(int val) {
	int c = 0;
	if ((val>2) && (val<7)) {
		c++;
	} else if (val == 10) {
		c--;
	}
	return c;
}