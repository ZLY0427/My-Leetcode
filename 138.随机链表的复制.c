/*
 * @lc app=leetcode.cn id=138 lang=c
 *
 * [138] 随机链表的复�?
 */

// @lc code=start
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */
#include <stdlib.h>

#ifdef RUN_LOCATED_VSCODE
struct Node {
    int val;
    struct Node* next;
    struct Node* random;
};
#endif

struct Node* copyRandomList(struct Node* head)
{
	if (!head) return NULL;

    struct Node* cur = head;

    while (cur)
    {
        struct Node* copyCur = (struct Node*)malloc(sizeof(struct Node));
        copyCur -> val = cur -> val;
        copyCur -> next = cur -> next;
        copyCur -> random = cur -> random;
        cur -> next = copyCur;

        cur = copyCur -> next;
    }

    cur = head;
    while (cur)
    {
        struct Node* copy = cur -> next;
        if (cur -> random)
            copy -> random = cur -> random -> next;
        cur = copy->next;
    }

    cur = head;
    struct Node* copyHead = head -> next;
    struct Node* copyCur = copyHead;
    while (cur)
    {
        cur -> next = copyCur -> next;
        cur = cur -> next;
        if (cur)
        {
            copyCur -> next = cur -> next;
            copyCur = copyCur -> next;
        }
    }

    return copyHead;
}
// @lc code=end

