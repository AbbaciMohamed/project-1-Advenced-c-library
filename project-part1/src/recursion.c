#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/recursion.h"

// Reverse a singly linked list using recursion
RecNode* reverseRec(RecNode* head) {
    if (head == NULL || head->next == NULL)
        return head;

    RecNode* temp = reverseRec(head->next);
    head->next->next = head;
    head->next = NULL;

    return temp;
}

// Factorial recursively
int factorial(int n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}

// Fibonacci recursively
int fibonacci(int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return fibonacci(n - 1) + fibonacci(n - 2);
}

// Find max ID in linked list using recursion
int findmaxId(RecNode* head) {
    if (head == NULL)
        return 0;
    int max = findmaxId(head->next);
    return (head->log.id > max) ? head->log.id : max;
}

// Infix to Postfix using recursion
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfixRecursive(const char* infix, int i, char* postfix, int* j) {
    static char stack[100];
    static int top = -1;

    if (infix[i] == '\0') {
        while (top != -1)
            postfix[(*j)++] = stack[top--];
        postfix[*j] = '\0';
        return;
    }

    char ch = infix[i];

    if (isalnum(ch)) {
        postfix[(*j)++] = ch;
    } else if (ch == '(') {
        stack[++top] = ch;
    } else if (ch == ')') {
        while (top != -1 && stack[top] != '(')
            postfix[(*j)++] = stack[top--];
        if (top != -1) top--; // Pop '('
    } else {
        while (top != -1 && precedence(stack[top]) >= precedence(ch))
            postfix[(*j)++] = stack[top--];
        stack[++top] = ch;
    }

    infixToPostfixRecursive(infix, i + 1, postfix, j);
}

void infixToPostfix(const char* infix, char* postfix) {
    int j = 0;
    infixToPostfixRecursive(infix, 0, postfix, &j);
}

// Display linked list (for testing reverse)
void Rec_displayList(RecNode* head) {
    printf("\n--- List Content ---\n");
    while (head != NULL) {
        printf("ID: %d | Timestamp: %s | Message: %s\n", head->log.id, head->log.timestamp, head->log.message);
        head = head->next;
    }
}

// Test menu
void test_recursion() {
    int choice, n;
    char infix[100], postfix[100];

    RecNode *list = NULL, *tail = NULL, *temp = NULL;
    RecLog log;

    do {
        printf("\n--- Recursion Menu ---\n");
        printf("1. Reverse Linked List (Recursive)\n");
        printf("2. Factorial\n");
        printf("3. Fibonacci\n");
        printf("4. Find Max ID in List\n");
        printf("5. Infix to Postfix (Recursive)\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                list = tail = NULL;
                printf("How many nodes in the list? ");
                scanf("%d", &n);
                getchar();

                for (int i = 0; i < n; i++) {
                    printf("Log %d - Enter ID, Timestamp, Message: ", i + 1);
                    scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                    getchar();

                    temp = malloc(sizeof(RecNode));
                    temp->log = log;
                    temp->next = NULL;

                    if (list == NULL) {
                        list = tail = temp;
                    } else {
                        tail->next = temp;
                        tail = temp;
                    }
                }

                printf("Original list:\n");
                Rec_displayList(list);

                list = reverseRec(list);  // important: reassign the returned head

                printf("Reversed list:\n");
                Rec_displayList(list);

                // Free memory
                while (list != NULL) {
                    temp = list;
                    list = list->next;
                    free(temp);
                }
                break;

            case 2:
                printf("Enter number: ");
                scanf("%d", &n);
                printf("Factorial of %d is %d\n", n, factorial(n));
                break;

            case 3:
                printf("Enter number: ");
                scanf("%d", &n);
                printf("Fibonacci(%d) = %d\n", n, fibonacci(n));
                break;

            case 4:
                list = tail = NULL;
                printf("How many nodes in the list? ");
                scanf("%d", &n);
                getchar();

                for (int i = 0; i < n; i++) {
                    printf("Log %d - Enter ID, Timestamp, Message: ", i + 1);
                    scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                    getchar();

                    temp = malloc(sizeof(RecNode));
                    temp->log = log;
                    temp->next = NULL;

                    if (list == NULL) {
                        list = tail = temp;
                    } else {
                        tail->next = temp;
                        tail = temp;
                    }
                }

                printf("Max ID: %d\n", findmaxId(list));

                // Free memory
                while (list != NULL) {
                    temp = list;
                    list = list->next;
                    free(temp);
                }
                break;

            case 5:
                printf("Enter infix expression (no spaces): ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix: %s\n", postfix);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
}
