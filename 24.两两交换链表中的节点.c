/*
 * @lc app=leetcode.cn id=24 lang=c
 *
 * [24] 24.两两交换链表中的节点
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

struct ListNode* swapPairs(struct ListNode* head)
{
    if (head == NULL || head -> next == NULL)
    {
        return head;
    }
    
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy -> next = head;
    struct ListNode* p = dummy;
    
    while (p -> next && p -> next -> next)
    {
        struct ListNode* node1 = p -> next;
        struct ListNode* node2 = p -> next -> next;
        
        node1 -> next = node2 -> next;
        node2 -> next = node1;
        p -> next = node2;
        
        p = node1;
    }
    
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}
// @lc code=end

