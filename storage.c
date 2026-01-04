#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Format:
// Q:Question Text
// A:Animal Name
// Recursive structure: Preorder traverse.
// Since it's a binary tree, we can just dump it recursively.
// If we encounter a Q, we know it has 2 children following.
// If we encounter an A, it has 0 children.

static void save_recursive(Node *node, FILE *fp) {
  if (!node)
    return;

  if (!node->yes && !node->no) {
    fprintf(fp, "A:%s\n", node->text);
  } else {
    fprintf(fp, "Q:%s\n", node->text);
    save_recursive(node->yes, fp);
    save_recursive(node->no, fp);
  }
}

void save_database(Node *root, const char *filename) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    perror("Failed to open database for writing");
    return;
  }
  save_recursive(root, fp);
  fclose(fp);
}

static Node *load_recursive(FILE *fp) {
  char buffer[256];
  if (!fgets(buffer, sizeof(buffer), fp)) {
    return NULL;
  }

  // Strip newline
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n')
    buffer[len - 1] = '\0';

  if (strncmp(buffer, "A:", 2) == 0) {
    return create_node(buffer + 2);
  } else if (strncmp(buffer, "Q:", 2) == 0) {
    Node *node = create_node(buffer + 2);
    node->yes = load_recursive(fp);
    node->no = load_recursive(fp);
    return node;
  }

  return NULL;
}

Node *load_database(const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp)
    return NULL;
  Node *root = load_recursive(fp);
  fclose(fp);
  return root;
}
