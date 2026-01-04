#ifndef GAME_H
#define GAME_H

typedef struct Node {
    char *text;
    struct Node *yes;
    struct Node *no;
} Node;

// Core game functions
Node* create_node(const char *text);
void play_game(Node *current_node, Node **root);
void free_tree(Node *root);

#endif
