#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

void arguments(int ac, char *av[]) {
	int i;
	for(i = 0; i< ac; i++) {
		printf("%s\n", av[i]);
	}
}

void flags(int ac, char *av[]) {
	char *str = (char *) malloc(sizeof(char) * 80);
	char ch;
	while((ch = getopt(ac, av, "sp:")) != EOF) {
		switch(ch) {
			case 'p':
				str = optarg;
				printf("%s\n", str);
				break;
			case 's':
				printf("This is the -s flag. Whee! \n");
				break;
			default:
				fprintf(stderr, "Sorry, I don't recognize that flag.\n");
				exit(1);
		}

		ac -= optind;
		av += optind;
	}

}


int main(int argc, char *argv[]) {
	// arguments(argc, argv);

	// flags(argc, argv);

	return 0;


}