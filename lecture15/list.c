/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(Node **head) {
    int retval;
    Node *next_node;
    Node *first = *head;

    if (first == NULL) {
        return -1;
    }

    next_node = (first)->next;
    retval = (first)->val;
    free(first);
    *head = next_node; //yup! affects the global variable
    // first = next_node; //nope! affects the local variable

    return retval;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {

    //this also works! 
    // Node *first;
    // first = malloc(sizeof(Node));

    // first->val = val;
    // first->next = *head;
    // *head = first;

    Node *new_node = make_node(val, *head);
    *head = new_node;
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    Node *current = *head;
    Node *victim;

    if (current == NULL) {
        return 0;
    }

    if(current->val == val) {
        pop(head);
        return 1;
    }

    while(current->next != NULL) {
        current = current->next;
        if (current->next->val == val) {
            victim = current->next;
            current->next = victim->next;
            free(victim);
            return 1;
        }
    }
    return 0;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    // FILL THIS IN!
}


int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(2, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(4, NULL);

    int retval = pop(&test_list);
    push(&test_list, retval+10);

    remove_by_value(&test_list, 3);
    //remove_by_value(&test_list, 7);   //segfaults

    reverse(&test_list);

    print_list(test_list);
}
