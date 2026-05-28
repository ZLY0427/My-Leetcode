/*
 * @lc app=leetcode.cn id=19 lang=c
 *
 * [19] 删除链表的倒数第 N 个结点
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

struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
    // 创建虚拟头节点
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;
    
    struct ListNode* fast = dummy;
    struct ListNode* slow = dummy;

    for (int i = 0; i < n; i++)
    {
        fast = fast -> next;
    }

    while (fast -> next != NULL)
    {
        fast = fast -> next;
        slow = slow -> next;
    }

    struct ListNode* temp = slow -> next;
    slow -> next = temp -> next;
    free(temp);
    struct ListNode* result = dummy -> next;
    free(dummy);

    return result;
}
// @lc code=end
