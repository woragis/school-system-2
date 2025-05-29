#include "bst.h"
#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

node_t *insert_user(node_t *root, user_t new_user)
{
    if (root == NULL)
    {
        node_t *new_node = malloc(sizeof(node_t));
        if (!new_node)
        {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }

        new_node->user = new_user;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    if (strcmp(new_user.rgm, root->user.rgm) == 0)
    {
        printf("RGM already exists. Skipping insert.\n");
        return root;
    }

    if (strcmp(new_user.rgm, root->user.rgm) < 0)
    {
        root->left = insert_user(root->left, new_user);
    }
    else
    {
        root->right = insert_user(root->right, new_user);
    }
    return root;
}

user_t *search_user(node_t *root, const char *rgm)
{
    if (root == NULL)
        return NULL;

    int cmp = strcmp(rgm, root->user.rgm);
    if (cmp == 0)
        return &root->user;
    else if (cmp < 0)
        return search_user(root->left, rgm);
    else
        return search_user(root->right, rgm);
}

void free_tree(node_t *root)
{
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
