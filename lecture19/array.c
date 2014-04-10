/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mutex.h"

#define SIZE 20000

typedef struct {
    int next_id;
    int array[SIZE];
    Lock *lock;
} Environment;

Environment *make_environment ()
{
    int i;

    Environment *env = (Environment *) malloc (sizeof (Environment));
    if (env == NULL) {
	perror ("malloc failed");
	exit (-1);
    }
    env->next_id = 0;

    for (i=0; i<SIZE; i++) {
	env->array[i] = 0;
    }

    env->lock = make_lock ();
    return env;
}

int get_next_id (Environment *env)
{
    int id = env->next_id;
    env->next_id++;
    return id;
}

/* Note: do not put a lock around the stuff inside the while loop!
    There is an access at id = get_next_id(env) and env->array[id]. 
    You need to fix both synchronization issues but putting a lock
    around the whole thing creates a deadlock.

    Deadlock: child thread gets the key, runs through the whole function. 
    It returns from this function, still holding the lock. And it dies,
    still holding the lock.
    The parent is still blocked at the beginning of the while-loop. And
    it will stay there, because it can't unlock itself.

    Solution? A "shrink-wrap" in which you fit the locks very tightly to 
    the synchronization problems (see below). In other words, a lock 
    around the access, and a lock around the increment. */ 

void loop_and_count (pthread_t self, Environment *env)
{
    int id;
    
    while (1) {
        acquire(env->lock);
    	id = get_next_id (env);
        release(env->lock);
    	
    	// printf ("%d got %d\n", self, id);
    	
    	if (id >= SIZE) return;
        acquire(env->lock);
    	env->array[id]++;
        release(env->lock);
    }
}

void check_array (Environment *env)
{
    int i;

    printf ("Checking...\n");
    
    for (i=0; i<SIZE; i++) {
	if (env->array[i] != 1) {
	    printf ("%d\t%d\n", i, env->array[i]);
	}
    }
}

/* The entry procedure is where the child thread will start executing. */

void *entry (void *arg)
{
    pthread_t self = pthread_self ();

    /* The entry procedure takes a single pointer as an argument.
       It is a pointer to the Environment structure that contains
       all the variables the parent and child will share. */

    Environment *env = (Environment *) arg;

    /* the child keeps getting ids and incrementing array
       elements until it gets an id that is bigger than the
       array; then it quits */

    loop_and_count (self, env);
    printf ("Child done looping.\n");

    pthread_exit (NULL);
}

int main()
{
    Environment *env;
    pthread_t self;
    pthread_t child;
    int ret;

    self = pthread_self ();

    env = make_environment ();

    /* the parent thread uses sproc to create the new thread, passing
       a pointer to card as an argument */

    ret = pthread_create (&child, NULL, entry, (void *) env);
    if (ret == -1) {
	perror ("pthread_create failed");
	exit (-1);
    }
    
    loop_and_count (self, env);

    printf ("Parent done looping.\n");
    
    ret = pthread_join (child, NULL);
    if (ret == -1) {
	perror ("pthread_join failed");
	exit (-1);
    }
  
    check_array (env);
    return 0;
}
