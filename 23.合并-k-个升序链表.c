/*
 * @lc app=leetcode.cn id=23 lang=c
 *
 * [23] 合并 K 个升序链表
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

struct ListNode* MergeList(struct ListNode* list1, struct ListNode* list2);

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if (listsSize == 0)
    {
        return NULL;
    }

    struct ListNode* result = NULL;
    for (int i = 0; i < listsSize; i++)
    {
        if (lists[i] == NULL)
        {
            continue;
        }
        result = MergeList(result, lists[i]);
    }

    return result;
}

struct ListNode* MergeList(struct ListNode* list1, struct ListNode* list2)
{
    if (list1 == NULL)
    {
        return list2;
    }
    if (list2 == NULL)
    {
        return list1;
    }
    
    struct ListNode* temphead = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (temphead == NULL)
    {
        return NULL;
    }
    struct ListNode* p = temphead;
    while (list1 && list2)
    {
        if (list1 -> val <= list2 -> val)
        {
            p -> next = list1;
            list1 = list1 -> next;
        }
        else
        {
            p -> next = list2;
            list2 = list2 -> next;
        }
        p = p -> next;
    }
    if (list1)
    {
        p -> next = list1;
    }
    if (list2)
    {
        p -> next = list2;
    }

    struct ListNode* result = temphead -> next;
    free(temphead);
    return result;
}
// @lc code=end

