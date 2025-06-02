#include <stdio.h>  // Biblioteca padrão de entrada/saída (printf, etc.)
#include <stdlib.h> // Biblioteca padrão para funções como malloc, free, exit
#include "bst.h"    // Header da árvore binária de busca (definições e funções de insert, search, delete, etc.)
#include "menu.h"   // Header do menu (funções interativas do usuário)

/*
 * Função principal do programa
 * Inicializa a árvore como vazia (NULL)
 * Chama o menu interativo para o usuário manipular a árvore
 */
int main()
{
    node_t *root = NULL; // Ponteiro para a raiz da árvore binária (inicialmente vazia)

    menu(&root); // Chama o menu que gerencia a árvore (inserção, busca, remoção, etc.)

    return 0; // Retorno 0 indica que o programa terminou com sucesso
}
