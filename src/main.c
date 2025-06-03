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
    printf("GRUPO:\n");
    printf("\tVictor Gabriel\n");
    printf("\tGustavo Theymos #polimata\n");
    printf("\tHumberto #hum Betinho #benca\n");
    printf("\tJezreel de Andrade\n");
    printf("DISCIPLINA: ESTRUTURA DE DADOS I\n");
    printf("PROFESSOR: WALLACE BONFIM\n");
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
    printf("\n\n\n\n\n\n\n\n\n\n");
}

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

void remove_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}
