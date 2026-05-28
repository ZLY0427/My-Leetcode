/*
 * @lc app=leetcode.cn id=83 lang=c
 *
 * [83] 删除排序链表中的重复元素
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

struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if (head == NULL)
    {
        return NULL;
    }
    struct ListNode* p = head;
    while(p -> next != NULL)
    {
        if (p -> val == p -> next -> val)
        {
            struct ListNode* temp = p -> next;
            p -> next = temp -> next;
            free(temp);
        }
        else
        {
            p = p -> next;
        }
    }

    return head;
}
// @lc code=end

