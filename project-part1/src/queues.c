#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/queues.h"

// NORMAL QUEUE IMPLEMENTATION :

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(QueueLog log, Queue* q) {
    QueueNode* temp = malloc(sizeof(QueueNode));
    temp->log = log;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

void dequeue(Queue* q) {
    if (q->front == NULL) return;

    QueueNode* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}

QueueLog Queue_peek(Queue* q) {
    QueueLog empty = {-1, "", ""};
    if (q->front == NULL) return empty;
    return q->front->log;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

// CIRCULAR QUEUE IMPLEMENTATION :

CircularQueue* createCircularQueue(int size) {
    CircularQueue* cq = malloc(sizeof(CircularQueue));
    cq->array = malloc(sizeof(QueueLog) * size);
    cq->size = size;
    cq->front = 0;
    cq->rear = -1;
    cq->count = 0;
    return cq;
}

void enqueueCircular(CircularQueue* cq, QueueLog log) {
    if (cq->count == cq->size) {
        printf("Circular queue is full.\n");
        return;
    }
    cq->rear = (cq->rear + 1) % cq->size;
    cq->array[cq->rear] = log;
    cq->count++;
}

QueueLog dequeueCircular(CircularQueue* cq) {
    QueueLog empty = {-1, "", ""};
    if (cq->count == 0) {
        printf("Circular queue is empty.\n");
        return empty;
    }
    QueueLog log = cq->array[cq->front];
    cq->front = (cq->front + 1) % cq->size;
    cq->count--;
    return log;
}

QueueLog peekCircular(CircularQueue* cq) {
    QueueLog empty = {-1, "", ""};
    if (cq->count == 0) return empty;
    return cq->array[cq->front];
}

int isEmptyCircular(CircularQueue* cq) {
    return cq->count == 0;
}

int isFullCircular(CircularQueue* cq) {
    return cq->count == cq->size;
}

void freeCircularQueue(CircularQueue* cq) {
    free(cq->array);
    free(cq);
}

// TEST FUNCTION :

void test_queues() {
    Queue q;
    initQueue(&q);
    QueueLog log;
    int choice;

    do {
        printf("\n--- Queue Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Check if Empty\n");
        printf("5. Test Circular Queue\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter ID, Timestamp, Message: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                getchar();
                enqueue(log, &q);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                log = Queue_peek(&q);
                if (log.id != -1)
                    printf("Peeked: %d | %s | %s\n", log.id, log.timestamp, log.message);
                else
                    printf("Queue is empty.\n");
                break;
            case 4:
                if (isEmpty(&q)) printf("Queue is empty.\n");
                else printf("Queue is not empty.\n");
                break;
            case 5: {
                int size;
                printf("Enter circular queue size: ");
                scanf("%d", &size);
                CircularQueue* cq = createCircularQueue(size);
                int op;
                do {
                    printf("\n--- Circular Queue ---\n");
                    printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. IsEmpty\n5. IsFull\n0. Back\n");
                    printf("Choice: ");
                    scanf("%d", &op);
                    getchar();

                    switch (op) {
                        case 1:
                            printf("Enter ID, Timestamp, Message: ");
                            scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                            getchar();
                            enqueueCircular(cq, log);
                            break;
                        case 2:
                            log = dequeueCircular(cq);
                            if (log.id != -1)
                                printf("Dequeued: %d | %s | %s\n", log.id, log.timestamp, log.message);
                            break;
                        case 3:
                            log = peekCircular(cq);
                            if (log.id != -1)
                                printf("Peeked: %d | %s | %s\n", log.id, log.timestamp, log.message);
                            break;
                        case 4:
                            printf(isEmptyCircular(cq) ? "Empty\n" : "Not empty\n");
                            break;
                        case 5:
                            printf(isFullCircular(cq) ? "Full\n" : "Not full\n");
                            break;
                    }
                } while (op != 0);
                freeCircularQueue(cq);
                break;
            }
        }
    } while (choice != 0);

    while (!isEmpty(&q)) dequeue(&q);
}

