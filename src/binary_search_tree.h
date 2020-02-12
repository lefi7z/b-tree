#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stddef.h>  // size_t

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node_t;

// walk down the tree and attach `data` at the right place
node_t* attach_ordered(node_t* head, int data);

// recursively build a tree out of data array 
node_t* build_tree(int tree_data[], size_t len);

// return the count of children of `head`
int count(node_t* tree);

// return a sorted array of the data in `tree`
int* sorted_data(node_t* tree);

// return the first node with `data` under `head`
node_t* find_first(node_t* head, int data);

// return the parent of `child` under `head`
node_t* parent(node_t* head, node_t* child);

// delete the tree and free the allocated memory
void free_tree(node_t * tree);

#endif // guard
