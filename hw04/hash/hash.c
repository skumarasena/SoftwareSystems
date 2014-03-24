/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// VALUE: represents a value in a key-value pair

/* Here's one way of making a polymorphic object in C */

typedef struct {
    enum Type {INT, STRING} type;
    union {
	int i;
	char *s;
    };
} Value;


/* Makes a Value object that contains an int. */
Value *make_int_value(int i) 
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = INT;
    value->i = i;
    return value;
}


/* Makes a Value object that contains a string. */
Value *make_string_value(char *s) 
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = STRING;
    value->s = s;
    return value;
}


/* Prints a value object. */
void print_value (Value *value) 
{
    if (value == NULL) {
        printf ("Value: %p", value);
	return;
    }
    switch (value->type) {
    case INT:
	printf ("INT: %d", value->i);
	break;
    case STRING:
	printf ("STRING: %s", value->s);
	break;
    }
}

// HASHABLE: Represents a key in a key-value pair.

/* Here's another way to make a polymorphic object.

The key can be any pointer type.  It's stored as a (void *), so
when you extract it, you have to cast it back to whatever it is.

hash is a pointer to a function that knows how to hash the key.
equal is a pointer to a function that knows how to compare keys.

 */

typedef struct {
    void *key;
    int (*hash) (void *);
    int (*equal) (void *, void *);
} Hashable;


/* Makes a Hashable object. */
Hashable *make_hashable(void *key, 
			int (*hash) (void *),
			int (*equal) (void *, void *)
			)
{
    Hashable *hashable = (Hashable *) malloc (sizeof (Hashable));
    hashable->key = key;
    hashable->hash = hash;
    hashable->equal = equal;
    return hashable;
}


/* Prints a Hashable object. */
void print_hashable(Hashable *hashable)
{
    printf ("key %p\n", hashable->key);
    printf ("hash %p\n", hashable->hash);
}


/* Hashes an integer. */
int hash_int(void *p)
{
    return *(int *)p;
}


/* Hashes a string. */
int hash_string(void *p)
{
    char *s = (char *) p;
    int total = 0;
    int i = 0;

    while (s[i] != 0) {
	total += s[i];
	i++;
    }
    return total;
}


/* Hashes any Hashable. */
int hash_hashable(Hashable *hashable)
{
    return hashable->hash (hashable->key);
}


/* Compares integers. */
int equal_int (void *ip, void *jp)
{
    int i_hash;
    int j_hash;

    i_hash = hash_int(ip);
    j_hash = hash_int(jp);

    // printf("%i\n", i_hash);
    // printf("%i\n", j_hash);

    return i_hash == j_hash;
}


/* Compares strings. */
int equal_string (void *s1, void *s2)
{
    int s1_hash;
    int s2_hash;

    s1_hash = hash_string(s1);
    s2_hash = hash_string(s2);

    return s1_hash == s2_hash;

}


/* Compares Hashables. */
int equal_hashable(Hashable *h1, Hashable *h2)
{
    int h1_hash;
    int h2_hash;

    h1_hash = hash_hashable(h1);
    h2_hash = hash_hashable(h2);

    return h1_hash == h2_hash;

}


/* Makes a Hashable int. 

Allocates space and copies the int.
*/
Hashable *make_hashable_int (int x)
{
    int *p = (int *) malloc (sizeof (int));
    *p = x;
    return make_hashable((void *) p, hash_int, equal_int);
}


/* Makes a Hashable string. 

Stores a reference to the string (not a copy).
*/
Hashable *make_hashable_string (char *s)
{
    return make_hashable((void *) s, hash_string, equal_string);
}



// NODE: a node in a list of key-value pairs

typedef struct node {
    Hashable *key;
    Value *value;
    struct node *next;
} Node;



/* Makes a Node. */
Node *make_node(Hashable *key, Value *value, Node *next)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = next;
    return node;
}



/* Prints a Node. */
void print_node(Node *node)
{
    print_hashable(node->key);
    printf ("value %p\n", node->value);
    printf ("next %p\n", node->next);
}


/* Prints all the Nodes in a list. */
void print_list(Node *node)
{
    Node *n = node->next;
    
    print_node(node);
    while(n != NULL) {
        print_node(n);
        n = n->next;
    }
}


/* Prepends a new key-value pair onto a list.

This is actually a synonym for make_node.
 */
Node *prepend(Hashable *key, Value *value, Node *rest)
{
    return make_node(key, value, rest);
}


/* Looks up a key and returns the corresponding value, or NULL */
Value *list_lookup(Node *list, Hashable *key)
{
    // Node *n = list->next;
    // Value *res = NULL;

    // while(n != NULL) {
    //     if(n->key == key) {
    //         res = n->value;
    //     }
    //     n = n->next;
    // }
    // return res;


    Node *n = list->next;

    if (list->key == key) {
        return list->value;
    } else {
        while(n) {
            if(n->key == key) {
                return n->value;
            }
            n = n->next;
        }
        return NULL;
    }
    
}


// MAP: a map is a list of key-value pairs

typedef struct map {
    int n;
    Node **lists;
} Map;


/* Makes a Map with n lists. */
Map *make_map(int n)
{
    Map *map = (Map *) malloc(sizeof(Map));// FIX ME!
    map->n = n;
    map->lists = (Node **) malloc(sizeof(Node *) * n);
    return map;
}


/* Prints a Map. */
void print_map(Map *map)
{
    int i;

    for (i=0; i<map->n; i++) {
	if (map->lists[i] != NULL) {
	    printf ("%d\n", i);
	    print_list (map->lists[i]);
	}
    }
}


/* Adds a key-value pair to a map. */
void map_add(Map *map, Hashable *key, Value *value)
{
    int i = hash_hashable(key) % map->n;

    //instead of make_node, prepend
    map->lists[i] = make_node(key, value, map->lists[i]);
}


/* Looks up a key and returns the corresponding value, or NULL. */
Value *map_lookup(Map *map, Hashable *key)
{
    int i = hash_hashable(key) % map->n;
    return list_lookup(map->lists[i], key);
}


/* Prints the results of a test lookup. */
void print_lookup(Value *value)
{
    printf ("Lookup returned ");
    print_value (value);
    printf ("\n");
}


int main ()
{
    Hashable *hashable1 = make_hashable_int (1);
    Hashable *hashable2 = make_hashable_string ("Allen");
    Hashable *hashable3 = make_hashable_int (2);

    // make a list by hand
    Value *value1 = make_int_value (17);
    Node *node1 = make_node(hashable1, value1, NULL);
    // print_node (node1);

    Value *value2 = make_string_value ("Downey");
    Node *list = prepend(hashable2, value2, node1);
    print_list (list);

    // run some test lookups
    Value *value = list_lookup (list, hashable1);   // This works (returns 17)
    print_lookup(value);

    value = list_lookup (list, hashable2);          // This works (returns Downey)
    print_lookup(value);

    value = list_lookup (list, hashable3);          // This works (returns NULL)
    print_lookup(value); 

    // make a map
    Map *map = make_map(10);
    map_add(map, hashable1, value1);
    map_add(map, hashable2, value2);

    printf ("Map\n");
    print_map(map); 

    // run some test lookups
     value = map_lookup(map, hashable1);
    print_lookup(value);

    value = map_lookup(map, hashable2);
    print_lookup(value);

    value = map_lookup(map, hashable3);
    print_lookup(value); 

    return 0;
}
