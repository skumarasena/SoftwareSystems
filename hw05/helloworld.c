
// compile as follows
// gcc `pkg-config --libs --cflags glib-2.0` helloworld.c -o helloworld                                  //NOPE!
// gcc `pkg-config --cflags glib-2.0` helloworld.c -o helloworld `pkg-config --libs glib-2.0`

#include <glib.h>
#include <stdio.h>

//basic "Hello World!" compilation test
void hello_world() {
	printf("Hello World!\n");

}

/*testing creation and modification of hashtable*/

void table_test() {
	char* key = "Hi!";
	int* val = 1;
	int i;
	int j;


	GHashTable* hash = g_hash_table_new(NULL, g_int_equal);
	g_hash_table_insert(hash, key, val);

	//getting value
	i = (int) g_hash_table_lookup(hash, key);
	printf("%i\n", i);

	//incrementing value
	i += 1;
	g_hash_table_insert(hash, key, i);

	//testing increment
	j = (int) g_hash_table_lookup(hash, key);
	printf("%i\n", j);
}


/*file-reading test*/
void file_test1() {
	FILE *f = fopen("test.txt", "r");
	char* temp = malloc(sizeof(char)*100);

	while(1) {
		if(fscanf(f, "%s", temp) != 1) {
			break;
		}
		printf("%s\n", temp);
	}
	rewind(f);
}

void read_file(GHashTable* hash) {
	FILE *f = fopen("test.txt", "r");
	char* temp = malloc(sizeof(char)*100);

	while(1) {
		if(fscanf(f, "%s", temp) != 1) {
			break;
		}
		//add_word(hash, temp);
		printf("%s\n", temp);
	}
	rewind(f);
}

// void add_word(GHashTable* hash, char* word) {
// 	int i = 0;
// 	int start = 1;
	
// 	//getting value
// 	i = (int) g_hash_table_lookup(hash, word);
// 	printf("%i\n", i);

// 	if(i==NULL) {
// 		printf("Key not found. Adding...\n");
// 		g_hash_table_insert(hash, word, start);
// 	} else {
// 		printf("Key found. Incrementing value.\n");
// 		i +=1;
// 		g_hash_table_insert(hash, word, i);
// 	}

// }


int main() {
	table_test();

	return 0;
}
