#include <stdio.h>  // Biblioteca padrão de entrada/saída (printf, etc.)
#include <stdlib.h> // Biblioteca padrão para funções como malloc, free, exit
#include "bst.h"    // Header da árvore binária de busca (definições e funções de insert, search, delete, etc.)
#include "menu.h"   // Header do menu (funções interativas do usuário)
#include "save.h"   // Header do save (funcoes para salvar os dados)

/*
 * Função principal do programa
 * Inicializa a árvore como vazia (NULL)
 * Chama o menu interativo para o usuário manipular a árvore
 */
int main()
{
    node_t *root = NULL; // Ponteiro para a raiz da árvore binária (inicialmente vazia)

    // Tentativa de carregar árvore do arquivo binário
    FILE *file = fopen("dados.bin", "rb");
    if (file)
    {
        root = load_tree_from_binary(file);
        fclose(file);
        printf("Árvore carregada de dados.bin\n");
    }

    // Executa o menu principal
    menu(&root); // Chama o menu que gerencia a árvore (inserção, busca, remoção, etc.)

    // Salva a árvore ao sair
    file = fopen("dados.bin", "wb");
    if (file)
    {
        save_tree_to_binary(file, root);
        fclose(file);
        printf("Árvore salva em dados.bin\n");
    }

    // Libera memória
    free_tree(root);

    return 0; // Retorno 0 indica que o programa terminou com sucesso
}
