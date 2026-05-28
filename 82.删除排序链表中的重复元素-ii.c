/*
 * @lc app=leetcode.cn id=82 lang=c
 *
 * [82] 删除排序链表中的重复元素 II
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
#include <stdbool.h>

#ifdef RUN_LOCATED_VSCODE
struct ListNode {
    int val;
    struct ListNode* next;
};
#endif

void FreeList(struct ListNode* head);

struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if (!head) return NULL;

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!dummy)
    {
        FreeList(head);
        return NULL;
    }
    dummy -> next = NULL;
    struct ListNode* current = dummy;

    struct ListNode* index = head;
    bool isRepeat = index && index -> next && index -> val == index -> next -> val;
    int repeatVal = isRepeat ? index -> val : -101;

    while (index)
    {
        if (isRepeat && index -> val == repeatVal)
        {
            index = index -> next;
        }
        else if (isRepeat && index -> val != repeatVal)
        {
            isRepeat = index && index -> next && index -> val == index -> next -> val;
            repeatVal = isRepeat ? index -> val : -101;
        }
        else
        {
            struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
            if (!newNode)
            {
                FreeList(head);
                FreeList(dummy);
                return NULL;
            }
            newNode -> val = index -> val;
            newNode -> next = NULL;
            current -> next = newNode;
            current = current -> next;

            index = index -> next;
            isRepeat = index && index -> next && (index -> val == index -> next -> val);
            repeatVal = isRepeat ? index -> val : -101;
        }
    }

    FreeList(head);
    struct ListNode* result = dummy -> next;
    free(dummy);
    return result;
}

void FreeList(struct ListNode* head)
{
    struct ListNode* current = head;
    while (current)
    {
        struct ListNode* temp = current;
        current = current -> next;
        free(temp);
    }
}
// @lc code=end

