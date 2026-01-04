#ifdef _MSC_VER
#define strdup _strdup
#endif

#include "game.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper to Safely read a line
static void read_line(char *buffer, int size) {
  if (fgets(buffer, size, stdin)) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    }
  }
}

// Helper to get yes/no answer
static int get_yes_no(const char *prompt) {
  char buffer[10];
  while (1) {
    printf("%s (y/n): ", prompt);
    read_line(buffer, sizeof(buffer));
    if (tolower(buffer[0]) == 'y')
      return 1;
    if (tolower(buffer[0]) == 'n')
      return 0;
  }
}

Node *create_node(const char *text) {
  Node *node = malloc(sizeof(Node));
  if (!node) {
    perror("Failed to allocate node");
    exit(EXIT_FAILURE);
  }
  node->text = strdup(text);
  node->yes = NULL;
  node->no = NULL;
  return node;
}

void free_tree(Node *root) {
  if (!root)
    return;
  free_tree(root->yes);
  free_tree(root->no);
  free(root->text);
  free(root);
}

void play_game(Node *current, Node **parent_ptr) {
  (void)parent_ptr; // Unused parameter

  // Logic:
  // If leaf (both children null) -> Guess
  // If internal -> Ask Question

  if (!current->yes && !current->no) {
    // Leaf node - Attempt guess
    printf("Is it a %s? ", current->text);
    if (get_yes_no("")) {
      printf("I win!\n");
    } else {
      // Learn
      char new_animal[100];
      char question[256];
      int answer_for_new;

      printf("I give up. What animal were you thinking of?\n");
      read_line(new_animal, sizeof(new_animal));

      printf("What question differentiates a %s from a %s?\n", new_animal,
             current->text);
      read_line(question, sizeof(question));

      printf("For a %s, is the answer to \"%s\" yes or no? ", new_animal,
             question);
      answer_for_new = get_yes_no("");

      // Create new nodes
      // The current node needs to be replaced by the new Question node
      // The Question node will have the old animal and the new animal as
      // children

      Node *new_animal_node = create_node(new_animal);

      // Create a copy of the current node (which is the "old animal")
      // to be a child of the new question node.
      Node *old_node = create_node(current->text);

      // Update current node to become the Question node
      free(current->text);
      current->text = strdup(question);

      if (answer_for_new) {
        current->yes = new_animal_node;
        current->no = old_node;
      } else {
        current->yes = old_node;
        current->no = new_animal_node;
      }
    }
  } else {
    // Question node
    if (get_yes_no(current->text)) {
      play_game(current->yes, NULL); // Recursion
    } else {
      play_game(current->no, NULL);
    }
  }
}
