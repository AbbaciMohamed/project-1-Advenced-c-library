#ifndef BLLISTS_H
#define BLLISTS_H

typedef struct {
    int id;
    char timestamp[30];
    char message[100];
} BLLog;

typedef struct BLNode {
    BLLog log;
    struct BLNode* next;
    struct BLNode* prev;
} BLNode;

// Core operations
BLNode* BL_createNode(BLLog log);
int BL_length(BLNode* head);
void BL_insert_beg(BLNode** head, BLLog log);
void BL_insert_end(BLNode** head, BLLog log);
void BL_insert_pos(BLNode** head, BLLog log, int pos);
void BL_delete_fir(BLNode** head);
void BL_delete_las(BLNode** head);
void BL_delete_id(BLNode** head, int id);
void BL_deleteByTimestamp(BLNode** head, char* timestamp);
void deleteAtPosition(BLNode** head, int position);
BLNode* reversing(BLNode* head);
BLNode* moveForward(BLNode* current);
BLNode* moveBackward(BLNode* current);
BLNode* mergeSortedLists(BLNode* l1, BLNode* l2);

// Testing
void test_BLLists();
#endif

