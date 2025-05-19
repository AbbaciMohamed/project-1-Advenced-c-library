#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/trees.h"

// Display a single log node
void displayLog(TreeNode* node) {
    if (node) {
        printf("[ID: %d] %s | %s (Severity: %d)\n",
               node->id, node->keyWord, node->timeStamp, node->severity);
    }
}

// Access log node by position
LogEntry* accessPosition(LogEntry* head, int index) {
    int i = 0;
    LogEntry* current = head;
    while (current && i < index) {
        current = current->next;
        i++;
    }
    return current;
}

// Insert into BST sorted by timestamp
TreeNode* insertLogBST(TreeNode* root, TreeNode* newLog) {
    if (!root) {
        TreeNode* node = malloc(sizeof(TreeNode));
        *node = *newLog;
        node->left = node->right = NULL;
        return node;
    }

    int cmp = strcmp(newLog->timeStamp, root->timeStamp);
    if (cmp < 0)
        root->left = insertLogBST(root->left, newLog);
    else if (cmp > 0)
        root->right = insertLogBST(root->right, newLog);

    return root;
}

// Delete a log by ID
TreeNode* deleteLogBST(TreeNode* root, int id) {
    if (!root) return NULL;

    if (id < root->id)
        root->left = deleteLogBST(root->left, id);
    else if (id > root->id)
        root->right = deleteLogBST(root->right, id);
    else {
        // Node found
        if (!root->left) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        } else {
            // Find inorder successor
            TreeNode* successor = root->right;
            while (successor->left)
                successor = successor->left;

            *root = *successor;
            root->right = deleteLogBST(root->right, successor->id);
        }
    }
    return root;
}

// Search log by ID
TreeNode* searchLogBST(TreeNode* root, int id) {
    if (!root || root->id == id) return root;

    if (id < root->id)
        return searchLogBST(root->left, id);
    else
        return searchLogBST(root->right, id);
}

// Traversals
void inOrderTraversal(TreeNode* root) {
    if (root) {
        inOrderTraversal(root->left);
        displayLog(root);
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(TreeNode* root) {
    if (root) {
        displayLog(root);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void postOrderTraversal(TreeNode* root) {
    if (root) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        displayLog(root);
    }
}

// Convert sorted doubly linked list to BST
TreeNode* sortedListToBST(LogEntry* head, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    LogEntry* midLog = accessPosition(head, mid);

    TreeNode* node = malloc(sizeof(TreeNode));
    strcpy(node->keyWord, midLog->keyWord);
    strcpy(node->timeStamp, midLog->timeStamp);
    node->id = midLog->id;
    node->severity = midLog->severity;

    node->left = sortedListToBST(head, start, mid - 1);
    node->right = sortedListToBST(head, mid + 1, end);

    return node;
}

// Test interface
void test_trees() {
    TreeNode* root = NULL;
    TreeNode temp;
    int choice, id;
    TreeNode* result;

    do {
        printf("\n--- TREE (BST) MENU ---\n");
        printf("1. Insert Log\n");
        printf("2. Delete Log by ID\n");
        printf("3. Search by ID\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter ID, Timestamp, Keyword, Severity: ");
                scanf("%d %s %s %d", &temp.id, temp.timeStamp, temp.keyWord, &temp.severity);
                root = insertLogBST(root, &temp);
                break;

            case 2:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                root = deleteLogBST(root, id);
                break;

            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                result = searchLogBST(root, id);
                if (result) displayLog(result);
                else printf("Log not found.\n");
                break;

            case 4:
                printf("Inorder Traversal:\n");
                inOrderTraversal(root);
                break;

            case 5:
                printf("Preorder Traversal:\n");
                preOrderTraversal(root);
                break;

            case 6:
                printf("Postorder Traversal:\n");
                postOrderTraversal(root);
                break;
        }

    } while (choice != 0);
}

