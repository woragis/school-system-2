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

// Helper function to find the minimum value node in a subtree
static node_t *find_min(node_t *node)
{
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

node_t *remove_user(node_t *root, const char *rgm)
{
    if (root == NULL)
        return NULL;

    int cmp = strcmp(rgm, root->user.rgm);

    if (cmp < 0)
    {
        root->left = remove_user(root->left, rgm);
    }
    else if (cmp > 0)
    {
        root->right = remove_user(root->right, rgm);
    }
    else
    {
        // Node found
        if (root->left == NULL)
        {
            node_t *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node_t *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        node_t *min_node = find_min(root->right);
        root->user = min_node->user;
        root->right = remove_user(root->right, min_node->user.rgm);
    }

    return root;
}

void show_inorder(node_t *root)
{
    if (root == NULL)
        return;

    show_inorder(root->left);
    printf("RGM: %s | Name: %s\n", root->user.rgm, root->user.name);
    show_inorder(root->right);
}
