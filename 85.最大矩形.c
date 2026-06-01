/*
 * @lc app=leetcode.cn id=85 lang=c
 *
 * [85] ×î´ó¾ØÐÎ
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

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

int help_maximalRectangle(int* heights, int heightsSize);

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
    if (!matrix || !matrixColSize || matrixSize <= 0) return 0;
    
    int col = matrixColSize[0];
    int row = matrixSize;

    if (col <= 0 || row <= 0) return 0;

    int maxarea = 0;

    int* heights = (int*)calloc(col, sizeof(int));
    if (!heights) return 0;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
        
        int area = help_maximalRectangle(heights, col);
        maxarea = maxarea > area ? maxarea : area;
    }

    free(heights);
    return maxarea;
}

int help_maximalRectangle(int* heights, int heightsSize)
{
    if (!heights || heightsSize <= 0) return 0;
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

