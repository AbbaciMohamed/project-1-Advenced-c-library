#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/BLLists.h"

// Create a new BLNode
BLNode* BL_createNode(BLLog log) {
    BLNode* newNode = (BLNode*)malloc(sizeof(BLNode));
    newNode->log = log;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Calculate BL_length
int BL_length(BLNode* head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

// Insert at beginning
void BL_insert_beg(BLNode** head, BLLog log) {
    BLNode* temp = BL_createNode(log);
    temp->next = *head;
    if (*head != NULL) {
        (*head)->prev = temp;
    }
    *head = temp;
}

// Insert at end
void BL_insert_end(BLNode** head, BLLog log) {
    BLNode* temp = BL_createNode(log);
    if (*head == NULL) {
        *head = temp;
        return;
    }
    BLNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = temp;
    temp->prev = current;
}

// Insert at position
void BL_insert_pos(BLNode** head, BLLog log, int position) {
    if (position < 0 || position > BL_length(*head)) {
        return;
    }
    if (position == 0) {
        BL_insert_beg(head, log);
        return;
    }
    BLNode* current = *head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    BLNode* temp = BL_createNode(log);
    temp->next = current->next;
    temp->prev = current;
    if (current->next != NULL) {
        current->next->prev = temp;
    }
    current->next = temp;
}

// Delete first
void BL_delete_fir(BLNode** head) {
    if (*head == NULL) return;
    BLNode* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

// Delete last
void BL_delete_las(BLNode** head) {
    if (*head == NULL) return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    BLNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->prev->next = NULL;
    free(current);
}

// Delete by ID
void BL_delete_id(BLNode** head, int id) {
    if (*head == NULL) return;
    BLNode* current = *head;

    if (current->log.id == id) {
        *head = current->next;
        if (*head != NULL) (*head)->prev = NULL;
        free(current);
        return;
    }

    while (current != NULL && current->log.id != id) {
        current = current->next;
    }

    if (current == NULL) return;

    if (current->prev != NULL) current->prev->next = current->next;
    if (current->next != NULL) current->next->prev = current->prev;

    free(current);
}

// Delete by timestamp
void BL_deleteByTimestamp(BLNode** head, char* timestamp) {
    if (*head == NULL) return;
    BLNode* current = *head;

    if (strcmp(current->log.timestamp, timestamp) == 0) {
        *head = current->next;
        if (*head != NULL) (*head)->prev = NULL;
        free(current);
        return;
    }

    while (current != NULL && strcmp(current->log.timestamp, timestamp) != 0) {
        current = current->next;
    }

    if (current == NULL) return;

    if (current->prev != NULL) current->prev->next = current->next;
    if (current->next != NULL) current->next->prev = current->prev;

    free(current);
}

// Delete at position
void deleteAtPosition(BLNode** head, int position) {
    if (*head == NULL || position < 0) return;

    BLNode* current = *head;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) return;

    if (current == *head) {
        *head = current->next;
        if (*head != NULL) (*head)->prev = NULL;
    } else {
        if (current->prev != NULL) current->prev->next = current->next;
        if (current->next != NULL) current->next->prev = current->prev;
    }

    free(current);
}

// Reverse the list
BLNode* reversing(BLNode* head) {
    BLNode* temp = NULL;
    BLNode* current = head;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        head = current;
        current = current->prev;
    }

    return head;
}

// Move forward
BLNode* moveForward(BLNode* current) {
    return current ? current->next : NULL;
}

// Move backward
BLNode* moveBackward(BLNode* current) {
    return current ? current->prev : NULL;
}

// Merge sorted lists by log.id
BLNode* mergeSortedLists(BLNode* l1, BLNode* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    BLNode* head = NULL;

    if (l1->log.id <= l2->log.id) {
        head = l1;
        l1 = l1->next;
    } else {
        head = l2;
        l2 = l2->next;
    }

    BLNode* tail = head;

    while (l1 != NULL && l2 != NULL) {
        if (l1->log.id <= l2->log.id) {
            tail->next = l1;
            l1->prev = tail;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2->prev = tail;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    if (l1 != NULL) tail->next = l1;
    else tail->next = l2;

    return head;
}

// Display list
void BL_displayList(BLNode* head) {
    printf("\n--- Current Doubly Linked List ---\n");
    BLNode* current = head;
    while (current != NULL) {
        printf("ID: %d | Timestamp: %s | Message: %s\n",
               current->log.id, current->log.timestamp, current->log.message);
        current = current->next;
    }
}

// Interactive test suite
void test_BLLists() {
    BLNode* list = NULL;
    int n;
    BLLog log;

    printf("Enter number of log entries to add initially: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Log %d - Enter ID, Timestamp, Message: ", i + 1);
        scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
        getchar();
        BL_insert_end(&list, log);
    }

    int choice;
    do {
        printf("\n--- Bidirectional Linked List Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete First\n");
        printf("5. Delete Last\n");
        printf("6. Delete by ID\n");
        printf("7. Delete by Timestamp\n");
        printf("8. Delete at Position\n");
        printf("9. Reverse List\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        int id, pos;
        char ts[30];

        switch (choice) {
            case 1:
                printf("Enter ID, Timestamp, Message: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                getchar();
                BL_insert_beg(&list, log);
                break;
            case 2:
                printf("Enter ID, Timestamp, Message: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                getchar();
                BL_insert_end(&list, log);
                break;
            case 3:
                printf("Enter ID, Timestamp, Message and Position: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                printf("Enter position: ");
                scanf("%d", &pos);
                getchar();
                BL_insert_pos(&list, log, pos);
                break;
            case 4:
                BL_delete_fir(&list);
                break;
            case 5:
                BL_delete_las(&list);
                break;
            case 6:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                BL_delete_id(&list, id);
                break;
            case 7:
                printf("Enter timestamp to delete: ");
                scanf("%s", ts);
                BL_deleteByTimestamp(&list, ts);
                break;
            case 8:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deleteAtPosition(&list, pos);
                break;
            case 9:
                list = reversing(list);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }

        if (choice != 0) {
            BL_displayList(list);
        }

    } while (choice != 0);

    while (list != NULL) {
        BL_delete_fir(&list);
    }
}

