#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>  // Biblioteca padrão de entrada/saída (printf, etc.)
#include <stdlib.h> // Biblioteca padrão para funções como malloc, free, exit
#include <string.h>

#define USER_NAME_LENGTH 50
#define USER_RGM_LENGTH 10

typedef struct user
{
    char name[USER_NAME_LENGTH];
    char rgm[USER_RGM_LENGTH];
} user_t;

typedef struct node
{
    user_t user;
    struct node *left;
    struct node *right;
} node_t;

void remove_newline(char *str);
node_t *insert_user(node_t *root, user_t new_user);
user_t *search_user(node_t *root, const char *rgm);
void free_tree(node_t *root);
node_t *remove_user(node_t *root, const char *rgm);
void show_inorder(node_t *root);
void save_tree_to_text(FILE *file, node_t *root);
node_t *load_tree_from_text(FILE *file);
void save_tree_to_binary(FILE *file, node_t *root);
node_t *load_tree_from_binary(FILE *file);
void menu(node_t **root);
void menu_insert(node_t **root);
void menu_remove(node_t **root);
void menu_search(node_t *root);
void menu_delete(node_t **root);
void menu_show(node_t *root);
void clear_terminal();

#endif
