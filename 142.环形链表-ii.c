/*
 * @lc app=leetcode.cn id=142 lang=c
 *
 * [142] 环形链表 II
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
    struct ListNode *next;
};
#endif

struct Help {
    struct ListNode* val;
    struct Help* next;
};

void delete_help(struct Help* hhead);

struct ListNode *detectCycle(struct ListNode *head)
{
    struct ListNode* result = NULL;
    bool cycle = false;

    struct ListNode* sign = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!sign) return false;
    sign -> next = NULL;
    sign -> val = 0;

    struct Help* hhead = NULL;

    struct ListNode* cur = head;
    struct Help* hcur = NULL;
    while (cur && cur != sign)
    {
        struct Help* hnode = (struct Help*)malloc(sizeof(struct Help));
        if (!hnode) return false;
        hnode -> val = cur;
        hnode -> next = NULL;

        if (hhead == NULL) hhead = hcur = hnode;
        else 
        {
            hcur -> next = hnode;
            hcur = hcur -> next;
        }

        cycle = cur -> next == sign;
        if (cycle) result = cur;

        if (cur -> next == NULL) break;

        struct ListNode* temp = cur -> next;
        cur -> next = sign;
        cur = temp;
    }

    hcur = hhead;
    while (hcur && hcur -> next)
    {
        hcur -> val -> next = hcur -> next -> val;
        hcur = hcur -> next;
    }

    free(sign);
    delete_help(hhead);

    return cycle ? result : NULL;
}

void delete_help(struct Help* hhead)
{
    struct Help* cur = hhead;
    while (cur)
    {
        struct Help* temp = cur;
        cur = cur -> next;
        free(temp);
    }
}
// @lc code=end

