#ifndef LLLISTS_H
#define LLLISTS_H

typedef struct {
    int id;
    char timestamp[30];
    char message[100];
} LLLog;

typedef struct LLNode {
    LLLog log;
    struct LLNode* next;
} LLNode;

// Core Functions
LLNode* LL_createNode(LLLog log);
int LL_length(LLNode* head);
void LL_insert_beg(LLNode** head, LLLog log);
void LL_insert_end(LLNode** head, LLLog log);
void LL_insert_pos(LLNode** head, LLLog log, int position);
void LL_delete_fir(LLNode** head);
void LL_delete_las(LLNode** head);
void LL_delete_id(LLNode** head, int id);
void delete_timestamp(LLNode** head, char* timestamp);
LLNode* search_by_id(LLNode* head, int id);
LLNode* search_by_timestamp(LLNode* head, char* timestamp);
LLNode* search_by_keyword(LLNode* head, char* keyword);
void sort_by_timestamp(LLNode* head);
void sort_by_id(LLNode* head);
LLNode* reverse_list(LLNode* head);

// Test
void test_LLLists();

#endif

