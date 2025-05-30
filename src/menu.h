#ifndef MENU_H
#define MENU_H
#include "bst.h"

void menu(node_t **root);
void menu_insert(node_t **root);
void menu_remove(node_t **root); // renamed to avoid conflict
void menu_search(node_t *root);
void menu_delete(node_t **root);
void menu_show(node_t *root);
void clear_terminal();

#endif