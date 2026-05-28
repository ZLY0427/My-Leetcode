/*
 * @lc app=leetcode.cn id=84 lang=c
 *
 * [84] 柱状图中最大的矩形
 */

// @lc code=start
#include <stdlib.h>

struct StackNode{
    int index;
    struct StackNode* next;
};

struct Stack{
    struct StackNode* top;
    int count;
};

struct Stack* stack_create();
void stack_push(struct Stack* Stack, int index);
int stack_pop(struct Stack* Stack);
int stack_top(struct Stack* Stack);
void stack_free(struct Stack* Stack);

int largestRectangleArea(int* heights, int heightsSize)
{
    if (heightsSize == 0) return 0;
    int maxarea = 0;

    int* left = (int*)malloc(sizeof(int) * heightsSize);
    int* right = (int*)malloc(sizeof(int) * heightsSize);
    if (!left || !right)
    {
        free(left);
        free(right);
        return -1;
    }

    struct Stack* stack = stack_create();
    if (!stack)
    {
        free(left);
        free(right);
        return -1;
    }

    for (int i = 0; i < heightsSize; i++)
    {
        while (stack -> count > 0 && heights[stack_top(stack)] >= heights[i])
            stack_pop(stack);
        left[i] = stack->count > 0 ? stack_top(stack) : -1;
        stack_push(stack, i);
    }

    while (stack -> count > 0) stack_pop(stack);

    for (int i = heightsSize - 1; i >= 0; i--)
    {
        while (stack -> count > 0 && heights[stack_top(stack)] >= heights[i])
            stack_pop(stack);
        right[i] = stack->count > 0 ? stack_top(stack) : heightsSize;
        stack_push(stack, i);
    }

    stack_free(stack);

    for (int i = 0; i < heightsSize; i++)
    {
        int width = right[i] - left[i] - 1;
        int area = heights[i] * width;
        maxarea = maxarea > area ? maxarea : area;
    }

    free(left);
    free(right);

    return maxarea;
}

struct Stack* stack_create()
{
    struct Stack* Stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!Stack) return NULL;

    Stack -> count = 0;
    Stack -> top = NULL;

    return Stack;
}

void stack_push(struct Stack* Stack, int index)
{
    if (!Stack) return ;
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) return ;
    newNode -> index = index;
    newNode -> next = NULL;

    newNode -> next = Stack -> top;
    Stack -> top = newNode;
    Stack -> count++;
}

int stack_pop(struct Stack* Stack)
{
    if (!Stack || !Stack -> top) return -1;

    struct StackNode* temp = Stack -> top;
    Stack -> top = temp -> next;

    int index = temp -> index;
    free(temp);
    Stack -> count--;
    return index;
}

int stack_top(struct Stack* Stack)
{
    if (!Stack || !Stack -> top) return -1;
    return Stack -> top -> index;
}

void stack_free(struct Stack* Stack)
{
    struct StackNode* current = Stack -> top;
    while (current)
    {
        struct StackNode* temp = current;
        current = current -> next;
        free(temp);
    }

    free(Stack);
}
// @lc code=end

