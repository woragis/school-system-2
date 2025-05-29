#ifndef BST_H
#define BST_H
#include "user.h"

typedef struct node
{
    user_t user;
    struct node *left;
    struct node *right;
} node_t;

node_t *insert_user(node_t *root, user_t new_user);
user_t *search_user(node_t *root, const char *rgm);
void free_tree(node_t *root);
node_t *remove_user(node_t *root, const char *rgm);
void show_inorder(node_t *root);

#endif
