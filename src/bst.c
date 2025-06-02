#include "bst.h"
#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Insere um novo usuário na árvore binária de busca
node_t *insert_user(node_t *root, user_t new_user)
{
    // Se a árvore está vazia, aloca e retorna um novo nó com o usuário
    if (root == NULL)
    {
        node_t *new_node = malloc(sizeof(node_t));
        if (!new_node)
        {
            perror("Falha ao alocar memória");
            exit(EXIT_FAILURE);
        }

        new_node->user = new_user;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    // Evita inserção de RGM duplicado
    if (strcmp(new_user.rgm, root->user.rgm) == 0)
    {
        printf("RGM já existe. Ignorando inserção.\n");
        return root;
    }

    // Inserção à esquerda se o RGM for menor
    if (strcmp(new_user.rgm, root->user.rgm) < 0)
    {
        root->left = insert_user(root->left, new_user);
    }
    // Inserção à direita se o RGM for maior
    else
    {
        root->right = insert_user(root->right, new_user);
    }
    return root;
}

// Busca um usuário na árvore pelo RGM
user_t *search_user(node_t *root, const char *rgm)
{
    if (root == NULL)
        return NULL; // RGM não encontrado

    int cmp = strcmp(rgm, root->user.rgm);
    if (cmp == 0)
        return &root->user; // Encontrou o usuário
    else if (cmp < 0)
        return search_user(root->left, rgm); // Busca na subárvore esquerda
    else
        return search_user(root->right, rgm); // Busca na subárvore direita
}

// Libera toda a memória alocada da árvore
void free_tree(node_t *root)
{
    if (root == NULL)
        return;
    free_tree(root->left);  // Libera subárvore esquerda
    free_tree(root->right); // Libera subárvore direita
    free(root);             // Libera o nó atual
}

// Função auxiliar para encontrar o nó com o menor RGM em uma subárvore
static node_t *find_min(node_t *node)
{
    while (node && node->left != NULL)
        node = node->left; // O menor valor está no canto mais à esquerda
    return node;
}

// Remove um usuário da árvore com base no RGM
node_t *remove_user(node_t *root, const char *rgm)
{
    if (root == NULL)
        return NULL; // RGM não encontrado

    int cmp = strcmp(rgm, root->user.rgm);

    if (cmp < 0)
    {
        root->left = remove_user(root->left, rgm); // Busca e remove na esquerda
    }
    else if (cmp > 0)
    {
        root->right = remove_user(root->right, rgm); // Busca e remove na direita
    }
    else
    {
        // Nó encontrado

        // Caso com um filho à direita ou nenhum filho
        if (root->left == NULL)
        {
            node_t *temp = root->right;
            free(root);
            return temp;
        }
        // Caso com um filho à esquerda
        else if (root->right == NULL)
        {
            node_t *temp = root->left;
            free(root);
            return temp;
        }

        // Caso com dois filhos:
        // Encontra o menor nó da subárvore direita (sucessor)
        node_t *min_node = find_min(root->right);
        // Copia os dados do sucessor para o nó atual
        root->user = min_node->user;
        // Remove o sucessor da subárvore direita
        root->right = remove_user(root->right, min_node->user.rgm);
    }

    return root;
}

// Exibe todos os usuários da árvore em ordem crescente de RGM (in-order traversal)
void show_inorder(node_t *root)
{
    if (root == NULL)
        return;

    show_inorder(root->left);                                        // Visita esquerda
    printf("RGM: %s | Name: %s\n", root->user.rgm, root->user.name); // Imprime usuário
    show_inorder(root->right);                                       // Visita direita
}
