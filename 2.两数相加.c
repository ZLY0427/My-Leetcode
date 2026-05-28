/*
 * @lc app=leetcode.cn id=2 lang=c
 *
 * [2] 两数相加
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
struct ListNode{
   int val;
   struct ListNode* next;
};
#endif

void Free(struct ListNode* list);

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{   
    // 初始化结果
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!head)
        return NULL;
    head -> next = NULL;
    
    // 创建指针变量
    struct ListNode* hCur = head;
    struct ListNode* l1Cur = l1;
    struct ListNode* l2Cur = l2;

    // 创建进位的变量
    int carry = 0;

    // 函数主体
    while (l1Cur || l2Cur)
    {
        int sum = carry;
        if (l1Cur)
            sum += l1Cur -> val;
        if (l2Cur)
            sum += l2Cur -> val;

        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (!newNode)
        {
            Free(head);
            return NULL;
        }
        newNode -> next = NULL;

        newNode -> val = sum % 10;
        carry = sum / 10;

        hCur -> next = newNode;
        hCur = hCur -> next;

        if (l1Cur)
            l1Cur = l1Cur -> next;
        if (l2Cur)
            l2Cur = l2Cur -> next;
    }

    if (carry)
    {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (!newNode)
        {
            Free(head);
            return NULL;
        }
        newNode -> next = NULL;
        newNode -> val = carry;

        hCur -> next = newNode;
        hCur = hCur -> next;
    }

    // 去除头节点, 并返回
    struct ListNode* result = head -> next;
    free(head);
    return result;
}

void Free(struct ListNode* list)
{
    struct ListNode* lCur = list;
    while (lCur)
    {
        struct ListNode* temp = lCur;
        lCur = lCur -> next;
        free(temp);
    }
}
// @lc code=end

