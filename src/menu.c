#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "utils.h"
#include "user.h"

void menu_insert(node_t **root)
{
    user_t u;

    printf("Enter name: ");
    fgets(u.name, sizeof(u.name), stdin);
    remove_newline(u.name);

    printf("Enter RGM: ");
    fgets(u.rgm, sizeof(u.rgm), stdin);
    remove_newline(u.rgm);

    *root = insert_user(*root, u);
}

void menu_remove(node_t **root)
{
    char rgm[USER_RGM_LENGTH];
    printf("Enter RGM to remove: ");
    fgets(rgm, sizeof(rgm), stdin);
    remove_newline(rgm);

    *root = remove_user(*root, rgm);
}

void menu_search(node_t *root)
{
    char query[USER_RGM_LENGTH];
    printf("Search RGM: ");
    fgets(query, sizeof(query), stdin);
    remove_newline(query);

    user_t *found = search_user(root, query);
    if (found)
    {
        printf("Found %s: (%s)\n", found->name, found->rgm);
    }
    else
    {
        printf("RGM not found.\n");
    }
}

void menu_delete(node_t **root)
{
    free_tree(*root);
    *root = NULL;
}

void menu_show(node_t *root)
{
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    show_inorder(root);
}

void menu(node_t **root)
{
    int choice = 0;
    char input[10];

    do
    {
        printf("==========================\n");
        printf("Sistema de Escola em C\n");
        printf("==========================\n");
        printf("[1] - Inserir aluno\n");
        printf("[2] - Remover aluno\n");
        printf("[3] - Pesquisar aluno\n");
        printf("[4] - Esvaziar árvore\n");
        printf("[5] - Exibir árvore\n");
        printf("[0] - Sair do Programa\n");
        printf("==========================\n");
        printf("Escolha: ");
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice)
        {
        case 1:
            menu_insert(root);
            break;
        case 2:
            menu_remove(root);
            break;
        case 3:
            menu_search(*root);
            break;
        case 4:
            menu_delete(root);
            break;
        case 5:
            menu_show(*root);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (choice != 0);
}