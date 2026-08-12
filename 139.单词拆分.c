/*
 * @lc app=leetcode.cn id=139 lang=c
 *
 * [139] 单词拆分
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Queue {
    struct QueueNode* head;
    struct QueueNode* tail;
    int len;
};

struct QueueNode {
    int matching;
    struct QueueNode* next;
};

struct Queue* create_Queue();
void push_Queue(struct Queue* q, int matching);
int pop_Queue(struct Queue* q);
void delete_Queue(struct Queue* q);
bool isSame(char* s, int left, int right, char* word);

bool wordBreak(char* s, char** wordDict, int wordDictSize)
{
    int sSize = strlen(s);
    if (!s || sSize <= 0) return false;

    struct Queue* q = create_Queue();
    if (!q) return false;

    bool* visited = (bool*)calloc(sSize, sizeof(bool));

    push_Queue(q, 0);

    while (q -> len > 0)
    {
        int left = pop_Queue(q);
        for (int i = 0; i < wordDictSize; ++i)
        {
            int wordLen = strlen(wordDict[i]);
            if (isSame(s, left, left + wordLen - 1, wordDict[i]))
            {
                if (left + wordLen == sSize)
                    return true;
                
                if (!visited[left + wordLen])
                {
                    push_Queue(q, left + wordLen);
                    visited[left + wordLen] = true;
                }
            }
        }
    }

    delete_Queue(q);
    return false;
}

struct Queue* create_Queue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    if (!q) return NULL;

    q -> head = NULL;
    q -> tail = NULL;
    q -> len = 0;

    return q;
}

void push_Queue(struct Queue* q, int matching)
{
    if (!q) return ;

    struct QueueNode* Qnode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!Qnode) return;

    Qnode -> matching = matching;
    Qnode -> next = NULL;

    if (q -> len == 0)
        q -> head = Qnode;
    else
        q -> tail -> next = Qnode;

    q -> tail = Qnode;
    ++(q -> len);
}

int pop_Queue(struct Queue* q)
{
    if (!q || q -> len <= 0) return -1;

    struct QueueNode* node = q -> head;
    int matching = node -> matching;

    q -> head = node -> next;
    if (q -> len == 1) q -> tail = NULL;
    free(node);

    --(q -> len);

    return matching;
}

void delete_Queue(struct Queue* q)
{
    if (!q) return;

    while (q -> len > 0)
        pop_Queue(q);

    free(q);
}

bool isSame(char* s, int left, int right, char* word)
{
    int wordSize = strlen(word);
    if (wordSize != right - left + 1) return false;

    for (int i = left, j = 0; i <= right; ++i, ++j)
        if (s[i] != word[j])
            return false;

    return true;
}

// @lc code=end

