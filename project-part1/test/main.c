#include <stdio.h>

// Include headers for all modules
#include "LLLists.h"
#include "BLLists.h"
#include "CLLists.h"
#include "stacks.h"
#include "queues.h"
#include "recursion.h"
#include "trees.h"

int main() {
    int choice;

    do {
        printf("\n========== DATA STRUCTURES - PART 1 ==========\n");
        printf("1. Singly Linked List (LLLists)\n");
        printf("2. Doubly Linked List (BLLists)\n");
        printf("3. Circular Linked List (CLLists)\n");
        printf("4. Stacks\n");
        printf("5. Queues\n");
        printf("6. Recursion\n");
        printf("7. Trees (BST Log Search)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                test_LLLists();
                break;
            case 2:
                test_BLLists();
                break;
            case 3:
                test_CLLists();
                break;
            case 4:
                test_stacks();
                break;
            case 5:
                test_queues();
                break;
            case 6:
                test_recursion();
                break;
            case 7:
                test_trees();
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

