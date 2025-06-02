#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "menu.h"
#include "utils.h"
#include "user.h"

// Solicita nome e RGM do usuário via terminal.
void menu_insert(node_t **root)
{
    user_t u;

    printf("Enter name: ");               // Printa um prompt para o usuario ler
    fgets(u.name, sizeof(u.name), stdin); // Recebe o input do usuario em uma variavel
    remove_newline(u.name);               // Remove \n com remove_newline.

    printf("Enter RGM: ");
    fgets(u.rgm, sizeof(u.rgm), stdin);
    remove_newline(u.rgm);

    // Insere o usuário na árvore usando insert_user.
    *root = insert_user(*root, u);
}

// Solicita o RGM do aluno a ser removido.
void menu_remove(node_t **root)
{
    char rgm[USER_RGM_LENGTH];
    printf("Enter RGM to remove: ");
    fgets(rgm, sizeof(rgm), stdin);
    remove_newline(rgm);

    // Remove o nó correspondente com remove_user.
    *root = remove_user(*root, rgm);
}

// Pede um RGM para busca.
void menu_search(node_t *root)
{
    char query[USER_RGM_LENGTH];
    printf("Search RGM: ");
    fgets(query, sizeof(query), stdin);
    remove_newline(query);

    // Usa search_user para procurar.
    user_t *found = search_user(root, query);

    // Exibe se o aluno foi encontrado ou não.
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
    // Libera a memória da árvore inteira usando free_tree.
    free_tree(*root);

    // Define o ponteiro da raiz como NULL.
    *root = NULL;
}

// Exibe os alunos da árvore em ordem crescente de RGM usando show_inorder.
void menu_show(node_t *root)
{
    // Caso a árvore esteja vazia, informa isso.
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    show_inorder(root);
}

// Funcao para printar o menu principal do programa
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

        // Usa fgets e atoi para ler a escolha do usuário com segurança.
        choice = atoi(input);

        // Usa clear_terminal() para limpar a tela após cada operação.
        clear_terminal();

        // Executa a opção correspondente usando switch-case.
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

void clear_terminal()
{
    // Código ANSI que:
    // \033[2J limpa a tela.
    // \033[H move o cursor para o topo da tela.
    printf("\033[2J\033[H");
}
