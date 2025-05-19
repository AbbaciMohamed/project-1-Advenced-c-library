#ifndef STACKS_H
#define STACKS_H

typedef struct {
    int id;
    char timestamp[30];
    char message[100];
} StackLog;

typedef struct StackNode {
    StackLog log;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} stack;

// Stack operations
void init_stack(stack* s);
void push(stack* s, StackLog value);
StackLog pop(stack* s);
StackLog Stack_peek(stack* s);
int is_empty(stack* s);
void insert_at_end(stack* s, StackLog log);
stack* reverse_rec(stack* s);
void display(stack* s);
// Test
void test_stacks();

#endif

