#ifndef QUEUES_H
#define QUEUES_H

typedef struct {
    int id;
    char timestamp[30];
    char message[100];
} QueueLog;

typedef struct QueueNode {
    QueueLog log;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

typedef struct {
    QueueLog* array;
    int size;
    int front;
    int rear;
    int count;
} CircularQueue;

// Normal Queue
void initQueue(Queue* q);
void enqueue(QueueLog log, Queue* q);
void dequeue(Queue* q);
QueueLog Queue_peek(Queue* q);
int isEmpty(Queue* q);

// Circular Queue
CircularQueue* createCircularQueue(int size);
void enqueueCircular(CircularQueue* cq, QueueLog log);
QueueLog dequeueCircular(CircularQueue* cq);
QueueLog peekCircular(CircularQueue* cq);
int isEmptyCircular(CircularQueue* cq);
int isFullCircular(CircularQueue* cq);
void freeCircularQueue(CircularQueue* cq);

// Test
void test_queues();

#endif

