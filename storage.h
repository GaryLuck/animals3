#ifndef STORAGE_H
#define STORAGE_H

#include "game.h"

// Save the tree to a file
void save_database(Node *root, const char *filename);

// Load the tree from a file. Returns the root of the tree.
Node* load_database(const char *filename);

#endif
