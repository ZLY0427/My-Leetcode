/*
 * @lc app=leetcode.cn id=92 lang=c
 *
 * [92] ·´×ªÁ´±í II
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

#ifdef RUN_LOCATED_VSCODE
 struct ListNode {
    int val;
    struct ListNode *next;
};
#endif

struct ListNode* reverseBetween(struct ListNode* head, int left, int right)
{
    if (!head || left > right || right <= 0) return head;


    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!dummy) return NULL;
    dummy -> next = head;

    struct ListNode* left_prev = dummy;
    for (int i = 1; i < left; i++)
    {
        left_prev = left_prev -> next;
        if (!left_prev) break;
    }

    struct ListNode* curr = left_prev -> next;
    struct ListNode* prev = NULL;
    for (int i = 0; i <= right - left; i++)
    {
        if (!curr) break;
        struct ListNode* next_node = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next_node;
    }

    left_prev->next->next = curr;
    left_prev->next = prev;

    struct ListNode* result = dummy->next;
    free(dummy);

    return result;
}
// @lc code=end

