#include "bst.h"
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

// Salva a árvore em um arquivo de texto em ordem (in-order traversal)
void save_tree_to_text(FILE *file, node_t *root)
{
    if (root == NULL)
        return;

    save_tree_to_text(file, root->left);

    // Salva os dados do usuário com separador '|'
    fprintf(file, "%s|%s\n", root->user.rgm, root->user.name);

    save_tree_to_text(file, root->right);
}

// Carrega uma árvore de um arquivo de texto (espera o formato RGM|Nome)
node_t *load_tree_from_text(FILE *file)
{
    char line[100];
    node_t *root = NULL;

    while (fgets(line, sizeof(line), file))
    {
        user_t user;
        char *sep = strchr(line, '|'); // Encontra o separador
        if (sep)
        {
            *sep = '\0'; // Termina a string do RGM
            strncpy(user.rgm, line, USER_RGM_LENGTH);
            strncpy(user.name, sep + 1, USER_NAME_LENGTH);

            // Remove o \n do nome, se existir
            remove_newline(user.name);

            // Insere o usuário na árvore
            root = insert_user(root, user);
        }
    }

    return root;
}

// Salva a árvore em um arquivo binário (in-order traversal)
void save_tree_to_binary(FILE *file, node_t *root)
{
    if (root == NULL)
        return;

    save_tree_to_binary(file, root->left);
    fwrite(&root->user, sizeof(user_t), 1, file); // Grava diretamente a struct user_t
    save_tree_to_binary(file, root->right);
}

// Carrega uma árvore de um arquivo binário
node_t *load_tree_from_binary(FILE *file)
{
    user_t user;
    node_t *root = NULL;

    // Lê cada usuário e insere na árvore
    while (fread(&user, sizeof(user_t), 1, file) == 1)
    {
        root = insert_user(root, user);
    }

    return root;
}
