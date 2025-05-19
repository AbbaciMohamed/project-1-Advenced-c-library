#ifndef TREES_H
#define TREES_H

typedef struct TreeNode {
    char keyWord[100];
    char timeStamp[30];
    int id;
    int severity;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct LogEntry {
    char keyWord[100];
    char timeStamp[30];
    int id;
    int severity;
    struct LogEntry* next;
    struct LogEntry* prev;
} LogEntry;

// BST Operations (Sorted by timestamp)
TreeNode* insertLogBST(TreeNode* root, TreeNode* newLog);
TreeNode* deleteLogBST(TreeNode* root, int id);
TreeNode* searchLogBST(TreeNode* root, int id);

// Traversals
void inOrderTraversal(TreeNode* root);
void preOrderTraversal(TreeNode* root);
void postOrderTraversal(TreeNode* root);

// Linked List to Balanced BST
TreeNode* sortedListToBST(LogEntry* head, int start, int end);
LogEntry* accessPosition(LogEntry* head, int index);

// Utilities
void displayLog(TreeNode* node);
void test_trees();

#endif

