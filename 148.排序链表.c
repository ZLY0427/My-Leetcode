/*
 * @lc app=leetcode.cn id=148 lang=c
 *
 * [148] 鎺掑簭閾捐�?
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

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2);
struct ListNode* findMiddle(struct ListNode* head);

struct ListNode* sortList(struct ListNode* head)
{
    if (!head || !head -> next) return head;

    struct ListNode* mid = findMiddle(head);

    struct ListNode* left = sortList(head);
    struct ListNode* right = sortList(mid);

    return mergeTwoLists(left, right);
}

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (l1 && l2)
    {
        if (l1 -> val <= l2 -> val)
        {
            tail -> next = l1;
            l1 = l1 -> next;
        }
        else
        {
            tail -> next = l2;
            l2 = l2 -> next;
        }
        tail = tail -> next;
    }
    tail -> next = l1 ? l1 : l2;
    return dummy.next;
}

struct ListNode* findMiddle(struct ListNode* head)
{
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    struct ListNode* prev = NULL;

    while (fast && fast -> next)
    {
        prev = slow;
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    if (prev) prev -> next = NULL;
    return slow;
}
// @lc code=end

