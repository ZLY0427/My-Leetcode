/*
 * @lc app=leetcode.cn id=143 lang=c
 *
 * [143] 重排链表
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

struct StackNode {
    struct ListNode* node;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
    int count;
};

struct Stack* create_Stack();
void push_Stack(struct Stack* stack, struct ListNode* node);
struct ListNode* pop_Stack(struct Stack* stack);
void delete_Stack(struct Stack* stack);

void reorderList(struct ListNode* head)
{
    if(head == NULL || head -> next == NULL) return ;

    struct Stack* stack = create_Stack();
    if (stack == NULL) return ;

    struct ListNode* cur;
    for (cur = head; cur != NULL; cur = cur -> next)
        push_Stack(stack, cur);

    cur = head;
    while (stack -> count > 0)
    {
        struct ListNode* node = pop_Stack(stack);
        if (cur == node || cur -> next == node)
        {
            node -> next = NULL;
            break;
        }

        struct ListNode* cur_next = cur -> next;
        cur -> next = node;
        node -> next = cur_next;

        cur = cur_next;
    }

    delete_Stack(stack);
    return ;
}

struct Stack* create_Stack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) return NULL;
    stack -> top = NULL;
    stack -> count = 0;
    return stack;
}

void push_Stack(struct Stack* stack, struct ListNode* node)
{
    if (stack == NULL || node == NULL) return ;

    struct StackNode* stack_node = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (stack_node == NULL) return;
    
    stack_node -> node = node;
    stack_node -> next = stack -> top;
    
    stack -> top = stack_node;
    ++(stack -> count);
}

struct ListNode* pop_Stack(struct Stack* stack)
{
    if (stack == NULL || stack -> count <= 0) return NULL;

    struct StackNode* stack_node = stack -> top;
    stack -> top = stack_node -> next;
    --(stack -> count);

    struct ListNode* node = stack_node -> node;

    free(stack_node);
    return node;
}

void delete_Stack(struct Stack* stack)
{
    if (stack == NULL) return;

    while (stack -> count > 0)
        pop_Stack(stack);
    free(stack);
}

// @lc code=end

