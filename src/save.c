#include "bst.h"
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

void save_tree_to_text(FILE *file, node_t *root)
{
    if (root == NULL)
        return;
    save_tree_to_text(file, root->left);
    fprintf(file, "%s|%s\n", root->user.rgm, root->user.name); // delimiter: |
    save_tree_to_text(file, root->right);
}

node_t *load_tree_from_text(FILE *file)
{
    char line[100];
    node_t *root = NULL;

    while (fgets(line, sizeof(line), file))
    {
        user_t user;
        char *sep = strchr(line, '|');
        if (sep)
        {
            *sep = '\0';
            strncpy(user.rgm, line, USER_RGM_LENGTH);
            strncpy(user.name, sep + 1, USER_NAME_LENGTH);

            // Remove newline from name
            remove_newline(user.name);
            root = insert_user(root, user);
        }
    }

    return root;
}

void save_tree_to_binary(FILE *file, node_t *root)
{
    if (root == NULL)
        return;
    save_tree_to_binary(file, root->left);
    fwrite(&root->user, sizeof(user_t), 1, file);
    save_tree_to_binary(file, root->right);
}

node_t *load_tree_from_binary(FILE *file)
{
    user_t user;
    node_t *root = NULL;

    while (fread(&user, sizeof(user_t), 1, file) == 1)
    {
        root = insert_user(root, user);
    }

    return root;
}
