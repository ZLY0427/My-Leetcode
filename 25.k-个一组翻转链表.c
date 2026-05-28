/*
 * @lc app=leetcode.cn id=25 lang=c
 *
 * [25] K 个一组翻转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdbool.h>
#include <stdlib.h>

#ifdef RUN_LOCATED_VSCODE
struct ListNode {
    int val;
    struct ListNode *next;
};
#endif

struct Stack {
    int size;
    int top;
    struct ListNode** node;
};

struct Stack* InitStack(int k);   // 初始化栈
bool is_emptyStack(struct Stack* stack);   // 判断栈空
bool is_fullStack(struct Stack* stack);   // 判断栈满
bool push(struct Stack* stack, struct ListNode* val);   // 入栈
bool pop(struct Stack* stack, struct ListNode** result);   // 出栈

struct ListNode* reverseKGroup(struct ListNode* head, int k)
{
    if (k <= 1 || head == NULL) return head;

    struct Stack* stack = InitStack(k);
    if (!stack) return NULL;

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!dummy) 
    {
        free(stack -> node);
        free(stack);
        return NULL;
    }
    dummy -> next = NULL;

    struct ListNode* index = dummy;
    struct ListNode* p = head;

    while (p)
    {
        int count = 0;
        while (p && count < k)
        {
            if (!push(stack, p))
            {
                free(dummy);
                free(stack -> node);
                free(stack);
                return NULL;
            }
            p = p -> next;
            count++;
        }

        if (count == k)
        {
            while (!is_emptyStack(stack))
            {
                struct ListNode* tempnode;
                if (!pop(stack, &tempnode))
                {
                    free(dummy);
                    free(stack -> node);
                    free(stack);
                    return NULL;
                }
                index -> next = tempnode;
                index = index -> next;
            }
            index -> next = p;
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                struct ListNode* temp = stack -> node[i];
                index -> next = temp;
                index = index -> next;
            }
            index -> next = NULL;
        }
        stack -> top = 0;
    }
    

    struct ListNode* result = dummy -> next;
    free(dummy);
    free(stack -> node);
    free(stack);
    return result;
}

struct Stack* InitStack(int k)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;
    stack -> size = k;
    stack -> top = 0;
    stack -> node = (struct ListNode**)malloc(sizeof(struct ListNode*) * k);
    if (!stack -> node)
    {
        free(stack);
        return NULL;
    }

    return stack;
}

bool is_emptyStack(struct Stack* stack)
{
    return stack -> top == 0;
}

bool is_fullStack(struct Stack* stack)
{
    return stack -> top == stack -> size;
}

bool push(struct Stack* stack, struct ListNode* val)
{
    if (is_fullStack(stack)) return false;
    stack -> node[stack -> top] = val;
    stack -> top++;

    return true;
}

bool pop(struct Stack* stack, struct ListNode** result)
{
    if (is_emptyStack(stack)) return false;

    *result = stack -> node[stack -> top - 1];
    stack -> top--;
    
    return true;
}
// @lc code=end