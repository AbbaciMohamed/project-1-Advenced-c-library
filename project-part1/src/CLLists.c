#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/CLLists.h"

// Create a new CLNode
CLNode* CL_createNode(CLLog log) {
    CLNode* newNode = (CLNode*)malloc(sizeof(CLNode));
    newNode->log = log;
    newNode->next = NULL;
    return newNode;
}

// Calculate CL_length
int CL_length(CLNode* head) {
    if (head == NULL) return 0;
    int len = 1;
    CLNode* current = head->next;
    while (current != head) {
        len++;
        current = current->next;
    }
    return len;
}

// Insert at beginning
void CL_insert_beg(CLNode** head, CLLog log) {
    CLNode* temp = CL_createNode(log);
    if (*head == NULL) {
        temp->next = temp;
        *head = temp;
        return;
    }
    CLNode* current = *head;
    while (current->next != *head)
        current = current->next;
    temp->next = *head;
    current->next = temp;
    *head = temp;
}

// Insert at end
void CL_insert_end(CLNode** head, CLLog log) {
    CLNode* temp = CL_createNode(log);
    if (*head == NULL) {
        temp->next = temp;
        *head = temp;
        return;
    }
    CLNode* current = *head;
    while (current->next != *head)
        current = current->next;
    current->next = temp;
    temp->next = *head;
}

// Insert at position
void CL_insert_pos(CLNode** head, CLLog log, int position) {
    if (position <= 0 || *head == NULL) {
        CL_insert_beg(head, log);
        return;
    }

    if (position >= CL_length(*head)) {
        CL_insert_end(head, log);
        return;
    }

    CLNode* current = *head;
    for (int i = 0; i < position - 1; i++)
        current = current->next;

    CLNode* temp = CL_createNode(log);
    temp->next = current->next;
    current->next = temp;
}

// Fixed-size buffer (overwrite old logs)
void insertFixedSize(CLNode** head, CLLog log, int maxSize) {
    if (*head == NULL) {
        CLNode* temp = CL_createNode(log);
        temp->next = temp;
        *head = temp;
        return;
    }
    if (CL_length(*head) < maxSize) {
        CL_insert_end(head, log);
    } else {
        (*head)->log = log;
        *head = (*head)->next;
    }
}

// Delete first CLNode
void CL_delete_fir(CLNode** head) {
    if (*head == NULL) return;
    CLNode* current = *head;
    if (current->next == current) {
        free(current);
        *head = NULL;
        return;
    }
    while (current->next != *head)
        current = current->next;
    CLNode* temp = *head;
    current->next = (*head)->next;
    *head = (*head)->next;
    free(temp);
}

// Delete last CLNode
void CL_delete_las(CLNode** head) {
    if (*head == NULL) return;
    CLNode* current = *head;
    if (current->next == current) {
        free(current);
        *head = NULL;
        return;
    }
    while (current->next->next != *head)
        current = current->next;
    CLNode* temp = current->next;
    current->next = *head;
    free(temp);
}

// Delete by ID
void CL_delete_id(CLNode** head, int id) {
    if (*head == NULL) return;

    CLNode* current = *head;
    if (current->log.id == id) {
        CL_delete_fir(head);
        return;
    }

    while (current->next != *head && current->next->log.id != id)
        current = current->next;

    if (current->next->log.id == id) {
        CLNode* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

// Delete by timestamp
void CL_deleteByTimestamp(CLNode** head, char* timestamp) {
    if (*head == NULL) return;
    CLNode* current = *head;
    if (strcmp(current->log.timestamp, timestamp) == 0) {
        CL_delete_fir(head);
        return;
    }

    while (current->next != *head &&
           strcmp(current->next->log.timestamp, timestamp) != 0)
        current = current->next;

    if (current->next != *head) {
        CLNode* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

// Search by ID
CLNode* searchById(CLNode* head, int id) {
    if (head == NULL) return NULL;
    CLNode* current = head;
    do {
        if (current->log.id == id) return current;
        current = current->next;
    } while (current != head);
    return NULL;
}

// Search by timestamp
CLNode* searchByTimestamp(CLNode* head, char* timestamp) {
    if (head == NULL) return NULL;
    CLNode* current = head;
    do {
        if (strcmp(current->log.timestamp, timestamp) == 0) return current;
        current = current->next;
    } while (current != head);
    return NULL;
}

// Search by keyword
CLNode* searchByKeyword(CLNode* head, char* keyword) {
    if (head == NULL) return NULL;
    CLNode* current = head;
    do {
        if (strcmp(current->log.message, keyword) == 0) return current;
        current = current->next;
    } while (current != head);
    return NULL;
}

// Reverse circular list
CLNode* reverse(CLNode* head) {
    if (head == NULL || head->next == head) return head;

    CLNode *prev = NULL, *current = head, *next = NULL;
    CLNode* tail = head;
    do {
        tail = tail->next;
    } while (tail->next != head);

    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != head);

    head->next = prev;
    head = prev;

    return head;
}

// Detect cycle
void detect_cycle(CLNode* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    CLNode* slow = head;
    CLNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            printf("Cycle detected. List is circular.\n");
            return;
        }
    }
    printf("No cycle detected. List is not circular.\n");
}

// Display circular list
void CL_displayList(CLNode* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    CLNode* current = head;
    printf("\n--- Current Circular Linked List ---\n");
    do {
        printf("ID: %d | Timestamp: %s | Message: %s\n",
               current->log.id, current->log.timestamp, current->log.message);
        current = current->next;
    } while (current != head);
}

// Interactive test suite
void test_CLLists() {
    CLNode* list = NULL;
    int n;
    CLLog log;

    printf("Enter number of log entries to add initially: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Log %d - Enter ID, Timestamp, Message: ", i + 1);
        scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
        getchar();
        CL_insert_end(&list, log);
    }

    int choice;
    do {
        printf("\n--- Circular Linked List Menu ---\n");
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
        printf("11. Reverse List\n");
        printf("12. Detect Cycle\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        int id, pos;
        char ts[30], keyword[100];
        CLNode* result;

        switch (choice) {
            case 1:
                printf("Enter ID, Timestamp, Message: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                getchar();
                CL_insert_beg(&list, log);
                break;
            case 2:
                printf("Enter ID, Timestamp, Message: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                getchar();
                CL_insert_end(&list, log);
                break;
            case 3:
                printf("Enter ID, Timestamp, Message and Position: ");
                scanf("%d %s %[^\n]", &log.id, log.timestamp, log.message);
                printf("Enter position: ");
                scanf("%d", &pos);
                getchar();
                CL_insert_pos(&list, log, pos);
                break;
            case 4:
                CL_delete_fir(&list);
                break;
            case 5:
                CL_delete_las(&list);
                break;
            case 6:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                CL_delete_id(&list, id);
                break;
            case 7:
                printf("Enter timestamp to delete: ");
                scanf("%s", ts);
                CL_deleteByTimestamp(&list, ts);
                break;
            case 8:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                result = searchById(list, id);
                if (result) printf("Found: %s\n", result->log.message);
                else printf("Not found.\n");
                break;
            case 9:
                printf("Enter timestamp to search: ");
                scanf("%s", ts);
                result = searchByTimestamp(list, ts);
                if (result) printf("Found: %s\n", result->log.message);
                else printf("Not found.\n");
                break;
            case 10:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                result = searchByKeyword(list, keyword);
                if (result) printf("Found: %s\n", result->log.message);
                else printf("Not found.\n");
                break;
            case 11:
                list = reverse(list);
                break;
            case 12:
                detect_cycle(list);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }

        if (choice != 0)
            CL_displayList(list);

    } while (choice != 0);

    while (list != NULL && CL_length(list) > 0)
        CL_delete_fir(&list);
}

