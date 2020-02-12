#include "src/binary_search_tree.h"
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define CONVERT(node) (node != NULL ? '0' + (char) node->data : '?')

static void print_tree(node_t * tree)
{
   if (tree == NULL)
      return;

   puts("");
   printf("     %c\n", CONVERT(tree));
   printf("   /   \\\n");
   printf("  %c     %c\n", 
           CONVERT(tree->left), 
           CONVERT(tree->right));
   printf(" / \\   / \\\n");
   if (tree->left == NULL)
       printf("?  ?  "); 
   else
       printf("%c  %c  ", 
           CONVERT(tree->left->left), 
           CONVERT(tree->left->right));

   if (tree->right == NULL)
       printf("?   ?"); 
   else
       printf("%c   %c\n", 
           CONVERT(tree->right->left), 
           CONVERT(tree->right->right));
   puts("");
   puts("");
}

void iter(node_t* head)
{
    if (head->left != NULL)
        iter(head->left);

    printf("%d - ", head->data);

    if (head->right != NULL)
        iter(head->right);
}

static void remove_left_child(node_t* parent)
{
    node_t* child = parent->left;
    if (child == NULL)
        return;

    if (child->left == NULL && child->right == NULL)
    {
        parent->left = NULL;
        free(child);
    }
}

int main(void)
{
   int tree_data[] = { 5, 3, 1, 2, };
   node_t *tree = build_tree(tree_data, ARRAY_SIZE(tree_data));

   print_tree(tree);
   printf("count: %d\n", count(tree));

   attach_ordered(tree, 7);
   attach_ordered(tree, 6);

   print_tree(tree);
   printf("count: %d\n", count(tree));

   iter(tree);
   puts("");

   node_t* first = find_first(tree, 7);
   printf("3 @ %p w/ %d\n", (void*) first, first->data);

   node_t* parent_node = parent(tree, first);
   printf("%p -> %p\n", (void*) parent_node, (void*) first);
   printf("%d -> %d\n", parent_node->data, first->data);

   remove_left_child(first);
   print_tree(tree);

   // homework: how would one..
   // a) delete the '3' ?
   // b) delete the '7' ?
   // c) delete the '5' ?

   free_tree(tree);

   return 0;
}

