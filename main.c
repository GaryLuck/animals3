#include "game.h"
#include "storage.h"
#include <stdbool.h>
#include <stdio.h>

#define DATABASE_FILE "database.dat"

int main() {
  printf("Welcome to the Animal Guessing Game!\n");

  Node *root = load_database(DATABASE_FILE);
  if (!root) {
    // Initial default tree: "Is it a human?" -> Yes: Computer Wins, No: (We'll
    // handle the initial logic or just start simple) Actually, typically the
    // leaf is the animal. So root question: "Is it a human?" (Wait, the prompt
    // says: "The data structure should start with the question is it a human?
    // (yes or no)?") No wait, usually the question differentiates. Let's assume
    // the root is a QUESTION "Is it a human?". If Yes -> "human". Wait,
    // normally leaves are answers (animals) and internal nodes are questions.
    // Prompt says: "The data structure should start with the question is it a
    // human? (yes or no)?" "If the user say yes, the computer wins." This
    // suggests the leaf is effectively "human". But if the user says no, it
    // asks what they were thinking of. Let's make the initial tree just a leaf:
    // "human". The game logic will check if it's a leaf node. If so, it
    // guesses.

    // Wait, "Is it a human?" is a specific start.
    // Let's create an initial node that is a LEAF "human".
    // When we play, if it's a leaf, we ask "Is it a %s?" (human).
    // If yes -> win.
    // If no -> split.
    root = create_node("human");
  }

  char input[10];
  while (true) {
    play_game(root, &root); // Pass address of root in case the root changes
                            // (though usually it splits lower down, but if root
                            // was a single leaf and we split it, root changes)
    // Wait, if root is a leaf "human", and we split it, the new root becomes a
    // Question node. So yes, we need to handle root updates.

    printf("Play again? (y/n): ");
    if (fgets(input, sizeof(input), stdin)) {
      if (input[0] == 'n' || input[0] == 'N') {
        break;
      }
    }
  }

  save_database(root, DATABASE_FILE);
  free_tree(root);
  printf("Goodbye!\n");
  return 0;
}
