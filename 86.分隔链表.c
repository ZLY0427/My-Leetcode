/*
 * @lc app=leetcode.cn id=86 lang=c
 *
 * [86] ∑÷∏Ó¡¥±Ì
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

struct ListNode* partition(struct ListNode* head, int x)
{
    if (!head) return NULL;
    struct ListNode* current = head;

    struct ListNode* dummyless = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* dummygreater = (struct ListNode*)malloc(sizeof(struct ListNode));

    if (!dummyless || !dummygreater)
    {
        free(dummyless);
        free(dummygreater);
        return NULL;
    }
    dummyless -> next = NULL;
    dummygreater -> next = NULL;

    struct ListNode* currentless = dummyless;
    struct ListNode* currentgreater = dummygreater;

    while (current)
    {
        struct ListNode* temp = current;
        current = current -> next;
        temp -> next = NULL;

        if (temp -> val < x)
        {
            currentless -> next = temp;
            currentless = currentless -> next;
        }
        else
        {
            currentgreater -> next = temp;
            currentgreater = currentgreater -> next;
        }
    }

    currentless -> next = dummygreater -> next;
    free(dummygreater);

    struct ListNode* result = dummyless -> next;
    free(dummyless);

    return result;
}
// @lc code=end

