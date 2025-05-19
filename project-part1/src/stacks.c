#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stacks.h"

// Initialize
void init_stack(stack* s) {
    s->top = NULL;
}

// Is empty
int is_empty(stack* s) {
    return s->top == NULL;
}

// Push
void push(stack* s, StackLog value) {
    StackNode* temp = malloc(sizeof(StackNode));
    temp->log = value;
    temp->next = s->top;
    s->top = temp;
}

// Pop
StackLog pop(stack* s) {
    StackLog empty = {-1, "", ""};
    if (is_empty(s)) {
        printf("Stack is empty.\n");
        return empty;
    }
    StackNode* temp = s->top;
    s->top = temp->next;
    StackLog val = temp->log;
    free(temp);
    return val;
}

// Peek
StackLog Stack_peek(stack* s) {
    StackLog empty = {-1, "", ""};
    if (is_empty(s)) {
        printf("Stack is empty.\n");
        return empty;
    }
    return s->top->log;
}

// Insert at end using temp stack
void insert_at_end(stack* s, StackLog log) {
    stack temp;
    init_stack(&temp);
    while (!is_empty(s)) {
        push(&temp, pop(s));
    }
    push(s, log);
    while (!is_empty(&temp)) {
        push(s, pop(&temp));
    }
}

// Reverse using recursion
stack* reverse_rec(stack* s) {
    if (is_empty(s)) return s;
    StackLog temp = pop(s);
    reverse_rec(s);
    insert_at_end(s, temp);
    return s;
}

// Display stack
void display(stack* s) {
    printf("\n--- Stack Content ---\n");
    stack temp;
    init_stack(&temp);
    while (!is_empty(s)) {
        StackLog log = pop(s);
        printf("ID: %d | Timestamp: %s | Message: %s\n", log.id, log.timestamp, log.message);
        push(&temp, log);
    }
    while (!is_empty(&temp)) {
        push(s, pop(&temp));
    }
}

// Test Suite
void test_stacks() {
    stack s;
    init_stack(&s);
    StackLog log;
    int choice;

    do {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Reverse (Recursively)\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter ID, Timestamp, Message: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                getchar();
                push(&s, log);
                break;
            case 2:
                log = pop(&s);
                if (log.id != -1)
                    printf("Popped: %d | %s | %s\n", log.id, log.timestamp, log.message);
                break;
            case 3:
                log = Stack_peek(&s);
                if (log.id != -1)
                    printf("Top: %d | %s | %s\n", log.id, log.timestamp, log.message);
                break;
            case 4:
                reverse_rec(&s);
                printf("Stack reversed.\n");
                break;
        }

        if (choice != 0)
            display(&s);

    } while (choice != 0);

    while (!is_empty(&s)) pop(&s);
}

