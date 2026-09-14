/*
 * @lc app=leetcode.cn id=206 lang=c
 *
 * [206] 反转链表
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

struct StackNode {
    struct ListNode* Lnode;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
    int count;
};

struct Stack* create_Stack();
void push_Stack(struct Stack* stack, struct ListNode* Lnode);
struct ListNode* pop_Stack(struct Stack* stack);
void free_Stack(struct Stack* stack);

struct ListNode* reverseList(struct ListNode* head)
{
    struct Stack* stack = create_Stack();
    if (!stack) return NULL;

    struct ListNode* cur = head;
    while (cur)
    {
        push_Stack(stack, cur);
        cur = cur -> next;
    }

    struct ListNode* new_head = pop_Stack(stack);
    if(new_head == NULL)
    {
        free_Stack(stack);
        return NULL;
    }

    cur = new_head;
    while (stack -> count > 0)
    {
        cur -> next = pop_Stack(stack);
        cur = cur -> next;
    }
    cur -> next = NULL;

    free_Stack(stack);

    return new_head;
}

struct Stack* create_Stack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    stack -> top = NULL;
    stack -> count = 0;

    return stack;
}

void push_Stack(struct Stack* stack, struct ListNode* Lnode)
{
    if (!stack || !Lnode) return ;

    struct StackNode* Snode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!Snode) return ;

    Snode -> Lnode = Lnode;
    Snode -> next = stack -> top;

    stack -> top = Snode;
    ++stack -> count;
}

struct ListNode* pop_Stack(struct Stack* stack)
{
    if (!stack || stack -> count <= 0) return NULL;

    struct StackNode* Snode = stack -> top;
    struct ListNode* Lnode = Snode -> Lnode;

    stack -> top = Snode -> next;
    --stack -> count;

    free(Snode);

    return Lnode;
}

void free_Stack(struct Stack* stack)
{
    if (!stack) return ;

    while (stack -> count > 0)
        pop_Stack(stack);

    free(stack);
}

// @lc code=end

