#ifndef CLLISTS_H
#define CLLISTS_H

typedef struct {
    int id;
    int severity;
    char timestamp[30];
    char message[100];
} CLLog;

typedef struct CLNode {
    CLLog log;
    struct CLNode* next;
} CLNode;

// Core Functions
CLNode* CL_createNode(CLLog log);
int CL_length(CLNode* head);
void CL_insert_beg(CLNode** head, CLLog log);
void CL_insert_end(CLNode** head, CLLog log);
void CL_insert_pos(CLNode** head, CLLog log, int position);
void insertFixedSize(CLNode** head, CLLog log, int maxSize);
void CL_delete_fir(CLNode** head);
void CL_delete_las(CLNode** head);
void CL_delete_id(CLNode** head, int id);
void CL_deleteByTimestamp(CLNode** head, char* timestamp);
CLNode* searchById(CLNode* head, int id);
CLNode* searchByTimestamp(CLNode* head, char* timestamp);
CLNode* searchByKeyword(CLNode* head, char* keyword);
CLNode* reverse(CLNode* head);
void detect_cycle(CLNode* head);
void CL_displayList(CLNode* head);
void test_CLLists();

#endif

