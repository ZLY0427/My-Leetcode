/*
 * @lc app=leetcode.cn id=155 lang=c
 *
 * [155] 最小栈
 */

// @lc code=start
#include <stdlib.h>

struct StackNode {
    int val;
    struct StackNode* next;
};

struct Stack{
    struct StackNode* top;
    int count;
};

typedef struct {
    struct Stack* stack;
    struct StackNode* minNode;
} MinStack;

struct Stack* create_Stack();
void push_Stack(struct Stack* stack, int val);
void pop_Stack(struct Stack* stack);
int top_Stack(struct Stack* stack);
void free_Stack(struct Stack* stack);

MinStack* minStackCreate();
void minStackPush(MinStack* obj, int value);
void minStackPop(MinStack* obj);
int minStackTop(MinStack* obj);
int minStackGetMin(MinStack* obj);
void minStackFree(MinStack* obj);

MinStack* minStackCreate()
{
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    if (!obj) return NULL;

    obj -> stack = create_Stack();
    obj -> minNode = NULL;

    return obj;
}

void minStackPush(MinStack* obj, int value)
{
    push_Stack(obj -> stack, value);
    if (minStackGetMin(obj) > value)
        obj -> minNode = obj -> stack -> top;
}

void minStackPop(MinStack* obj)
{
    if (minStackGetMin(obj) == top_Stack(obj -> stack))
        obj -> minNode = NULL;
    pop_Stack(obj -> stack);
}

int minStackTop(MinStack* obj)
{
    return top_Stack(obj -> stack);
}

int minStackGetMin(MinStack* obj)
{
    if (obj -> minNode) return obj -> minNode -> val;
    
    struct StackNode* cur = obj -> stack -> top;
    obj -> minNode = cur;
    while (cur)
    {
        obj -> minNode = obj -> minNode -> val < cur -> val ?
                         obj -> minNode : cur;
        cur = cur -> next;
    }
    return obj -> minNode -> val;
}

void minStackFree(MinStack* obj)
{
    free_Stack(obj -> stack);
    free(obj);
}

struct Stack* create_Stack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    stack -> top = NULL;
    stack -> count = 0;

    return stack;
}

void push_Stack(struct Stack* stack, int val)
{
    if (!stack) return ;

    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!node) return ;
    
    node -> val = val;
    node -> next = stack -> top;

    stack -> top = node;
    ++(stack -> count);
}

void pop_Stack(struct Stack* stack)
{
    if (!stack || stack -> count < 1) return;

    struct StackNode* node = stack -> top;
    
    stack -> top = node -> next;
    --(stack -> count);

    free(node);
}

int top_Stack(struct Stack* stack)
{
    if (!stack || stack -> count < 1) return 0;

    return stack -> top -> val;
}

void free_Stack(struct Stack* stack)
{
    if (!stack) return;

    while (stack -> count > 0)
        pop_Stack(stack);

    free(stack);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, value);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
// @lc code=end

