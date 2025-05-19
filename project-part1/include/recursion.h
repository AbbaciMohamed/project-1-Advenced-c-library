#ifndef RECURSION_H
#define RECURSION_H

typedef struct {
    int id;
    char timestamp[30];
    char message[100];
} RecLog;

typedef struct RecNode {
    RecLog log;
    struct RecNode* next;
} RecNode;

// Recursive Algorithms
RecNode* reverseRec(RecNode* head);
int factorial(int n);
int fibonacci(int n);
int findmaxId(RecNode* head);

// Infix to Postfix
int precedence(char op);
void infixToPostfixRecursive(const char* infix, int i, char* postfix, int* j);
void infixToPostfix(const char* infix, char* postfix);

// Test + Helpers
void test_recursion();
void Rec_displayList(RecNode* head);

#endif

