#include "main.h"

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
    FILE *file_text = fopen("dados.txt", "r");
    if (file_text)
    {
        // root = load_tree_from_text(file_text);
        // printf("Árvore carregada de dados.bin\n");
        fclose(file_text);
    }

    // Executa o menu principal
    menu(&root); // Chama o menu que gerencia a árvore (inserção, busca, remoção, etc.)

    // Salva a árvore ao sair (em binario)
    file = fopen("dados.bin", "wb");
    if (file)
    {
        save_tree_to_binary(file, root);
        fclose(file);
        printf("Árvore salva em dados.bin\n");
    }

    // Salva a árvore ao sair (em texto)
    file_text = fopen("dados.txt", "w");
    if (file_text)
    {
        save_tree_to_text(file_text, root);
        fclose(file_text);
        printf("Árvore salva em dados.txt\n");
    }

    // Libera memória
    free_tree(root);

    return 0; // Retorno 0 indica que o programa terminou com sucesso
}
