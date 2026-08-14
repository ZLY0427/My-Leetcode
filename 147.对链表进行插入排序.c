/*
 * @lc app=leetcode.cn id=147 lang=c
 *
 * [147] 对链表进行插入排�?
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
    struct ListNode* next;
};
#endif

struct ListNode* insertionSortList(struct ListNode* head)
{
    if (!head || !head -> next) return head;

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy -> next = head;

    struct ListNode* cur = head -> next;
    head -> next = NULL;
    while (cur)
    {
        struct ListNode* temp = cur;
        cur = cur -> next;

        struct ListNode* pre = dummy;
        while (pre -> next && pre -> next -> val < temp -> val)
            pre = pre -> next;

        temp -> next = pre -> next;
        pre -> next = temp;
    }

    struct ListNode* ret = dummy -> next;
    free(dummy);

    return ret;
}
// @lc code=end

