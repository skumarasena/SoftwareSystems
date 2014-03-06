#include <stdio.h>
#include <stdlib.h>

void feed_me();
void feeding_time();

void marry_me();
void wedding();

typedef union {
	float weight;
	float volume;
} Fish_size;

typedef struct {
	const char *firstname;
	const char *lastname;
} Name;

typedef struct {
	Name name;
	const char *species;
	int teeth;
	int age;
	int food;
	Fish_size size;
} Fish;

void feed_me(Fish *f) {
	// (*f).food += 1;		//Equivalent to next line
	f->food += 1;
	f->size.weight += 1;
}

void marry_me(Fish *a, Fish *b) {
	const char* aname;
	const char* bname;

	// aname = (*a).name.lastname;
	// bname = (*b).name.lastname;
	aname = a->name.lastname;
	bname = b->name.lastname;

	(*a).name.lastname = bname;
	(*b).name.lastname = aname;

}

void feeding_time() {
	Fish a = {{"Alice", "Fishy"}, "Pirahna", 70, 2, 0, .size.weight = 43.5};
	Fish b = {{"Bob", "Fisher"}, "Pirahna", 65, 2, 3, .size.weight = 39.0};

	feed_me(&a);
	feed_me(&b);

	printf("%s is now THIIIIS big: %2.2f\n", a.name.firstname, a.size.weight);
	printf("%s is now THIIIIS big: %2.2f\n", b.name.firstname, b.size.weight);

/*  DOES NOT WORK. Do you see why?

	Fish *b = {"Bob", "Pirahna", 70, 2, 0};
	feed_me(b);
	printf("%s now has THIIIIS much food: %i\n", (*b).name, (*b).food);
*/

}

void wedding() {
	Fish a = {{"Alice", "Fishy"}, "Pirahna", 70, 2, 0};
	Fish b = {{"Bob", "Fisher"}, "Pirahna", 65, 2, 3};

	marry_me(&a, &b);

	printf("Congratulations, %s %s and %s %s! You're now married. \n", a.name.firstname, a.name.lastname, b.name.firstname, b.name.lastname);
}


int main() {
	feeding_time();
	wedding();
}