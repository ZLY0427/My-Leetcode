/*
 * @lc app=leetcode.cn id=160 lang=c
 *
 * [160] 相交链表
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

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    struct ListNode* curA = headA;
    struct ListNode* curB = headB;

    while (curA != curB)
    {
        curA = !curA ? headB : curA -> next;
        curB = !curB ? headA : curB -> next;
    }

    return curA;
}
// @lc code=end

