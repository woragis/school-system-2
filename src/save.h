#ifndef SAVE_H
#define SAVE_H
#include <stdio.h>
#include "bst.h"

void save_tree_to_text(FILE *file, node_t *root);
node_t *load_tree_from_text(FILE *file);
void save_tree_to_binary(FILE *file, node_t *root);
node_t *load_tree_from_binary(FILE *file);

#endif