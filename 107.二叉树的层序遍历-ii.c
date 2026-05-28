/*
 * @lc app=leetcode.cn id=107 lang=c
 *
 * [107] 二叉树的层次遍历 II
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

#ifdef RUN_LOCATED_VSCODE
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif

struct QueueNode {
    struct TreeNode* node;
    struct QueueNode* next;
    int level;
};

struct Queue {
    struct QueueNode* front;  // 队头
    struct QueueNode* rear;   // 队尾
    int size;
};

struct StackNode {
    struct TreeNode* node;
    struct StackNode* next;
    int level;
};

struct Stack {
    struct StackNode* top;   // 栈顶
    struct StackNode* base;  // 栈底
    int size;
};

struct Queue* queue_create();
struct Stack* stack_create();
void queue_push(struct Queue* queue, struct TreeNode* node, int level);
void stack_push(struct Stack* stack, struct TreeNode* node, int level);
struct QueueNode* queue_pop(struct Queue* queue);
struct StackNode* stack_pop(struct Stack* stack);
void queue_free(struct Queue* queue);
void stack_free(struct Stack* stack);
int** getResult(int* temp_result, int size, int* returnSize, int** returnColumnSizes);

int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (!root) return NULL;
    
    struct Queue* queue = queue_create();
    struct Stack* stack = stack_create();
    if (!queue || !stack)
    {
        queue_free(queue);
        stack_free(stack);
        return NULL;
    }

    queue_push(queue, root, 1);

    while (queue -> size > 0)
    {
        struct QueueNode* Qnode = queue_pop(queue);
        int level = Qnode -> level;
        struct TreeNode* Tnode = Qnode -> node;
        free(Qnode);

        if (Tnode -> right) queue_push(queue, Tnode -> right, level + 1);
        if (Tnode -> left) queue_push(queue, Tnode -> left, level + 1);

        stack_push(stack, Tnode, level);
    }
    queue_free(queue);
    
    int* temp_result = (int*)calloc(4000, sizeof(int));
    if (!temp_result)
    {
        stack_free(stack);
        return NULL;
    }

    int index = 0;
    int now_level = 0;

    while (stack -> size > 0)
    {
        struct StackNode* Snode = stack_pop(stack);
        int level = Snode -> level;
        struct TreeNode* Tnode = Snode -> node;
        free(Snode);
        if (level != now_level)
        {
            temp_result[index++] = 1024;
            now_level = level;
        }

        temp_result[index++] = Tnode -> val;
    }

    stack_free(stack);

    return getResult(temp_result, index, returnSize, returnColumnSizes);
}

struct Queue* queue_create()
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) return NULL;

    queue -> front = NULL;
    queue -> rear = NULL;
    queue -> size = 0;

    return queue;
}

struct Stack* stack_create()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    stack -> top = NULL;
    stack -> base = NULL;
    stack -> size = 0;

    return stack;
}

void queue_push(struct Queue* queue, struct TreeNode* node, int level)
{
    if (!queue || !node) return ;

    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!newNode) return ;
    newNode -> node = node;
    newNode -> next = NULL;
    newNode -> level = level;

    if (!queue -> size)
    {
        queue -> front = newNode;
        queue -> rear = newNode;
        queue -> size = 1;
    }
    else
    {
        queue -> rear -> next = newNode;
        queue -> rear = newNode;
        ++queue -> size;
    }
}

void stack_push(struct Stack* stack, struct TreeNode* node, int level)
{
    if (!stack || !node) return ;

    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) return ;
    newNode -> node = node;
    newNode -> next = NULL;
    newNode -> level = level;

    if (!stack -> size)
    {
        stack -> top = newNode;
        stack -> base = newNode;
        stack -> size = 1;
    }
    else
    {
        newNode -> next = stack -> top;
        stack -> top = newNode;
        ++stack -> size;
    }
}

struct QueueNode* queue_pop(struct Queue* queue)
{
    if (!queue || queue -> size <= 0) return NULL;

    struct QueueNode* Qnode = queue -> front;
    queue -> front = Qnode -> next;
    --queue -> size;

    return Qnode;
}

struct StackNode* stack_pop(struct Stack* stack)
{
    if (!stack || stack -> size <= 0) return NULL;

    struct StackNode* Snode = stack -> top;
    stack -> top = Snode -> next;
    --stack -> size;

    return Snode;
}

void queue_free(struct Queue* queue)
{
    if (!queue) return ;
    while (queue -> size) free(queue_pop(queue));

    free(queue);
}

void stack_free(struct Stack* stack)
{
    if (!stack) return ;
    while (stack -> size) free(stack_pop(stack));

    free(stack);
}

int** getResult(int* temp_result, int size, int* returnSize, int** returnColumnSizes)
{
    int levels = 0;
    int* col_sizes = (int*)calloc(2000, sizeof(int));
    if (!col_sizes)
    {
        free(temp_result);
        return NULL;
    }

    for (int i = 0; i < size; ++i)
    {
        if (temp_result[i] == 1024)
        {
            levels++;
            continue;
        }
        ++col_sizes[levels - 1];
    }

    *returnSize = levels;

    *returnColumnSizes = (int*)malloc(levels * sizeof(int));
    if (!(*returnColumnSizes))
    {
        free(col_sizes);
        free(temp_result);
        return NULL;
    }
    for (int i = 0; i < levels; ++i) (*returnColumnSizes)[i] = col_sizes[i];

    int** result = (int**)malloc(levels * sizeof(int*));
    if (!result)
    {
        free(col_sizes);
        free(*returnColumnSizes);
        free(temp_result);
        return NULL;
    }

    for(int i = 0; i < levels; ++i)
        result[i] = (int*)malloc(col_sizes[i] * sizeof(int));

    int current_level = 0;
    int current_index = 0;
    
    for (int i = 0; i < size; ++i)
    {
        if (temp_result[i] == 1024)
        {
            ++current_level;
            current_index = 0;
            continue;
        }
        result[current_level - 1][current_index++] = temp_result[i];
    }

    free(col_sizes);
    free(temp_result);
    return result;
}
// @lc code=end

