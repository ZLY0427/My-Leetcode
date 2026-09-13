/*
 * @lc app=leetcode.cn id=203 lang=c
 *
 * [203] 移除链表元素
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

struct ListNode* removeElements(struct ListNode* head, int val)
{
    struct ListNode* pre = NULL;
    struct ListNode* cur = head;

    while (cur)
    {
        if (cur -> val == val)
        {
            if (pre)
                pre -> next = cur -> next;
            else
                head = cur -> next;
            
            free(cur);
            cur = pre ? pre -> next : head;
        }
        else
        {
            pre = cur;
            cur = cur -> next;
        }
    }

    return head;
}
// @lc code=end

