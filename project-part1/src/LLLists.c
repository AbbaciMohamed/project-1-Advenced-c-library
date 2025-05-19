#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/LLLists.h"

// LLNode creation
LLNode* LL_createNode(LLLog log) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->log = log;
    newNode->next = NULL;
    return newNode;
}

// Get LL_length of list
int LL_length(LLNode* head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

// Insert at beginning
void LL_insert_beg(LLNode** head, LLLog log) {
    LLNode* temp = LL_createNode(log);
    temp->next = *head;
    *head = temp;
}

// Insert at end
void LL_insert_end(LLNode** head, LLLog log) {
    LLNode* temp = LL_createNode(log);
    if (*head == NULL) {
        *head = temp;
        return;
    }
    LLNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = temp;
}

// Insert at specific position
void LL_insert_pos(LLNode** head, LLLog log, int position) {
    if (position < 0 || position > LL_length(*head)) {
        printf("Invalid position\n");
        return;
    }
    if (position == 0) {
        LL_insert_beg(head, log);
        return;
    }
    LLNode* current = *head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    LLNode* temp = LL_createNode(log);
    temp->next = current->next;
    current->next = temp;
}

// Delete first LLNode
void LL_delete_fir(LLNode** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    LLNode* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Delete last LLNode
void LL_delete_las(LLNode** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    LLNode* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

// Delete by ID
void LL_delete_id(LLNode** head, int id) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    LLNode* temp = NULL;
    if ((*head)->log.id == id) {
        LL_delete_fir(head);
        return;
    }
    LLNode* current = *head;
    while (current->next != NULL && current->next->log.id != id) {
        current = current->next;
    }
    if (current->next == NULL) {
        printf("ID not found\n");
        return;
    }
    temp = current->next;
    current->next = temp->next;
    free(temp);
}

// Delete by timestamp
void delete_timestamp(LLNode** head, char* timestamp) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (strcmp((*head)->log.timestamp, timestamp) == 0) {
        LL_delete_fir(head);
        return;
    }
    LLNode* current = *head;
    while (current->next != NULL && strcmp(current->next->log.timestamp, timestamp) != 0) {
        current = current->next;
    }
    if (current->next == NULL) {
        printf("Timestamp not found\n");
        return;
    }
    LLNode* temp = current->next;
    current->next = temp->next;
    free(temp);
}

// Swap logs (used for sorting)
void swapLogs(LLNode* a, LLNode* b) {
    LLLog temp = a->log;
    a->log = b->log;
    b->log = temp;
}

// Sort by timestamp
void sort_by_timestamp(LLNode* head) {
    int len = LL_length(head);
    LLNode* current;
    LLNode* next;
    for (int i = 0; i < len - 1; i++) {
        current = head;
        next = current->next;
        for (int j = 0; j < len - i - 1; j++) {
            if (strcmp(current->log.timestamp, next->log.timestamp) > 0) {
                swapLogs(current, next);
            }
            current = current->next;
            next = next->next;
        }
    }
}

// Sort by ID
void sort_by_id(LLNode* head) {
    int len = LL_length(head);
    LLNode* current;
    LLNode* next;
    for (int i = 0; i < len - 1; i++) {
        current = head;
        next = current->next;
        for (int j = 0; j < len - i - 1; j++) {
            if (current->log.id > next->log.id) {
                swapLogs(current, next);
            }
            current = current->next;
            next = next->next;
        }
    }
}

// Search functions
LLNode* search_by_id(LLNode* head, int id) {
    while (head != NULL) {
        if (head->log.id == id) return head;
        head = head->next;
    }
    return NULL;
}

LLNode* search_by_timestamp(LLNode* head, char* timestamp) {
    while (head != NULL) {
        if (strcmp(head->log.timestamp, timestamp) == 0) return head;
        head = head->next;
    }
    return NULL;
}

LLNode* search_by_keyword(LLNode* head, char* keyword) {
    while (head != NULL) {
        if (strcmp(head->log.message, keyword) == 0) return head;
        head = head->next;
    }
    return NULL;
}

// Reverse list
LLNode* reverse_list(LLNode* head) {
    LLNode *prev = NULL, *next = NULL;
    while (head != NULL) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

//the test requirments :

void LL_displayList(LLNode* head) {
    LLNode* current = head;
    printf("\n--- Current Linked List ---\n");
    while (current != NULL) {
        printf("ID: %d | Timestamp: %s | Message: %s\n",
               current->log.id,
               current->log.timestamp,
               current->log.message);
        current = current->next;
    }
}

void test_LLLists() {
    LLNode* list = NULL;
    int n;
    LLLog log;

    printf("Enter number of log entries to add initially: ");
    scanf("%d", &n);
    getchar(); // consume newline

    for (int i = 0; i < n; i++) {
        printf("Log %d - Enter ID, Timestamp, Message (space-separated): ", i + 1);
	scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
	getchar();  // flush newline
        LL_insert_end(&list, log);
    }
    int choice;
    do {
        printf("\n--- Singly Linked List Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete First\n");
        printf("5. Delete Last\n");
        printf("6. Delete by ID\n");
        printf("7. Delete by Timestamp\n");
        printf("8. Search by ID\n");
        printf("9. Search by Timestamp\n");
        printf("10. Search by Keyword\n");
        printf("11. Sort by Timestamp\n");
        printf("12. Sort by ID\n");
        printf("13. Reverse List\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        int id, pos;
        char ts[30], keyword[100];
        LLNode* result;

        switch (choice) {
            case 1:
                printf("Enter ID, Timestamp, Message: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                LL_insert_beg(&list, log);
                break;
            case 2:
                printf("Enter ID, Timestamp, Message: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                LL_insert_end(&list, log);
                break;
            case 3:
                printf("Enter ID, Timestamp, Message and Position: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                printf("Position: ");
                scanf("%d", &pos);
                LL_insert_pos(&list, log, pos);
                break;
            case 4:
                LL_delete_fir(&list);
                break;
            case 5:
                LL_delete_las(&list);
                break;
            case 6:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                LL_delete_id(&list, id);
                break;
            case 7:
                printf("Enter timestamp to delete: ");
                scanf("%s", ts);
                delete_timestamp(&list, ts);
                break;
            case 8:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                result = search_by_id(list, id);
                if (result) printf("Found: %s\n", result->log.message);
                else printf("Not found.\n");
                break;
            case 9:
                printf("Enter timestamp to search: ");
                scanf("%s", ts);
                result = search_by_timestamp(list, ts);
                if (result) printf("Found: %s\n", result->log.message);
                else printf("Not found.\n");
                break;
            case 10:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                result = search_by_keyword(list, keyword);
                if (result) printf("Found: %s\n", result->log.message);
                else printf("Not found.\n");
                break;
            case 11:
                sort_by_timestamp(list);
                break;
            case 12:
                sort_by_id(list);
                break;
            case 13:
                list = reverse_list(list);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }

        if (choice != 0) {
            LL_displayList(list);
        }

    } while (choice != 0);

    // Free memory
    while (list != NULL) {
        LL_delete_fir(&list);
    }
}

