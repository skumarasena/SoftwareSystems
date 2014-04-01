
// compile as follows
// gcc `pkg-config --libs --cflags glib-2.0` helloworld.c -o helloworld                                  //NOPE!
// gcc `pkg-config --cflags glib-2.0` helloworld.c -o helloworld `pkg-config --libs glib-2.0`

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>


/*Prints a single key-value pair in the hash table. For use with print_hash_table.*/

static void print_row(gpointer key, gpointer val, gpointer userdata) {
    GString* realKey = (GString*)key;
    printf("Key: %s, Value: %i\n", realKey->str, *(int*)val);

}



/*Prints a hash table.*/ 

void print_hash_table(GHashTable* hash) {
    g_hash_table_foreach(hash, print_row, NULL);
}



/*Adds a word to a hash table. If it is not yet present in the hash table, it is added.
If it is present, the value (word count) is incremented.*/

void hash_append(GHashTable* hash, GString* word)
{
  int *val = g_hash_table_lookup(hash, (gpointer)word);
 int *i = malloc(sizeof(int));

  if(val==NULL) {
    *i = 1;
    g_hash_table_insert(hash, (gpointer)word, (gpointer)i);  
  }
  else {
    *i = *val+1;
    g_hash_table_insert(hash, (gpointer)word, (gpointer)i);
  }
	
}

/*Reads a file and adds key-value pairs to a hash table of the form (word, word count).*/

void fill_table(GHashTable* hash, FILE* file) {
    char* temp = malloc(sizeof(char)*100);
    while(1) {
        if(fscanf(file, "%s", temp)!=1) {
            break;
        }
        hash_append(hash, g_string_new(temp));
    }

}

/*Prompts a user for a file name, and prepares the file to be read.*/

FILE* make_file() {
    char* filename = malloc(sizeof(char)*80);
    printf("Enter the name of your text file: ");
    scanf("%79s", filename);
    FILE* file = fopen(filename, "r");
    return file;
}


int main()
{
    FILE* file = make_file();

    GHashTable *hash = g_hash_table_new ((GHashFunc)g_string_hash, (GEqualFunc)g_string_equal);

    fill_table(hash, file);

    print_hash_table(hash);

    return 0;
}