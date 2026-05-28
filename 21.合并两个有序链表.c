/*
 * @lc app=leetcode.cn id=21 lang=c
 *
 * [21] 合并两个有序链表
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


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
    struct ListNode* temphead = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (temphead == NULL)
    {
        return NULL;
    }
    struct ListNode* p = temphead;
    
    while (list1 != NULL && list2 != NULL)
    {
        if (list1 -> val < list2 -> val)
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
    
    if (list1 != NULL)
    {
        p -> next = list1;
    }
    else
    {
        p -> next = list2;
    }
    
    struct ListNode* result = temphead -> next;
    free(temphead);
    
    return result;
}
// @lc code=end
