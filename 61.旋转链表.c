/*
 * @lc app=leetcode.cn id=61 lang=c
 *
 * [61] Ðý×ªÁ´±í
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdlib.h>

# ifdef RUN_LOCATED_VSCODE
struct ListNode{
    int val;
    struct ListNode* next;
}; 
# endif

int getListSize(struct ListNode* head);

struct ListNode* rotateRight(struct ListNode* head, int k)
{
    if (!head) return NULL;

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!dummy) return NULL;

    dummy -> val = 0;
    dummy -> next = head;
    int len = getListSize(head);

    int times = k % len;
    if (!times)
    {
        free(dummy);
        return head;
    }

    struct ListNode* current = head;
    int idx = 1;
    while (current && idx < len - times)
    {
        current = current -> next;
        idx++;
    }

    struct ListNode* temp = current -> next;
    current -> next = NULL;

    dummy -> next = temp;
    while (temp -> next)
    {
        temp = temp -> next;
    }
    temp -> next = head;

    struct ListNode* result = dummy -> next;
    free(dummy);

    return result;
}

int getListSize(struct ListNode* head)
{
    int len = 0;
    struct ListNode* current = head;

    while (current)
    {
        len++;
        current = current -> next;
    }

    return len;
}
// @lc code=end

