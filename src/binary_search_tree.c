#include "binary_search_tree.h"
#include <stdlib.h>  // malloc

// allocate and return a new node
static node_t* _aquire_node(int data);

// recursively build a tree out of data array 
node_t* build_tree(int data[], size_t len)
{
    node_t* head = NULL;

    for (int i=0; i<(int)len; i++)
        if ((head = attach_ordered(head, data[i])) == NULL)
            return NULL;

    return head;
}

// walk down the tree and attach `data` at the right place
node_t* attach_ordered(node_t* head, int data)
{
    // if this node is free, we take it
    if (head == NULL)
        return _aquire_node(data);

    // if not, dive one level deeper into the tree and
    // attach to either the left or right head instead
    if (data > head->data)
        head->right = attach_ordered(head->right, data);
    else
        head->left = attach_ordered(head->left, data);

    // a return value of NULL means that _aquire_node 
    // has failed, so we return the next best thing
    return head;
}

// return the first node with `data` under `head`
node_t* find_first(node_t* head, int data)
{
    // the default return value
    if (head == NULL)
        return NULL;

    // if this node is the desired one, return it
    else if (head->data == data)
        return head;

    // if not, dive one level deeper into the tree..
    else if (data > head->data)
        return find_first(head->right, data);
    else
        return find_first(head->left, data);
}

// return the parent of `child` under `head`
node_t* parent(node_t* head, node_t* child)
{
    // the default return value
    if (head == NULL || child == head)
        return NULL;

    // if this node is the desired one, return it
    else if (head->left == child || head->right == child)
        return head;

    // if not, dive one level deeper into the tree..
    node_t* rv;
    if ((rv = parent(head->left, child)) != NULL)
        return rv;
    if ((rv = parent(head->right, child)) != NULL)
        return rv;

    return NULL;
}

// recursive helper function that fills an array pointed
// to by `p` with the data underneath `head` 
static void _sort(int** p, node_t* head);

// return a sorted array of the data in `tree`
int* sorted_data(node_t* tree)
{
    // count the datapoints to allocate enough memory
    int* sorted = (int*) malloc(sizeof(int) * count(tree));
    if (sorted == NULL)
        return NULL;

    // we need to retain a copy of `sorted`,
    // because `_sort` modifies its arguments
    int* walk = sorted;
    _sort(&walk, tree);

    return sorted;
}

static void _sort(int** p, node_t* head)
{
    // insert everything from the left branch...
    if (head->left != NULL)
        _sort(p, head->left);

    // ...then insert the current head...
    **p = head->data;
    (*p)++;

    // ...then dive into the right branch
    if (head->right != NULL)
        _sort(p, head->right);
}

// return the count of children of `head`
int count(node_t* head)
{
    if (head == NULL)
        return 0;

    return 1 + count(head->left) + count(head->right);
}

static node_t* _aquire_node(int data)
{
    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;

    node->left = node->right = NULL;
    node->data = data;

    return node;
}

// delete the tree and free the allocated memory
void free_tree(node_t * tree)
{
   if (tree == NULL)
      return;
   free_tree(tree->left);
   free_tree(tree->right);
   free(tree);
}

