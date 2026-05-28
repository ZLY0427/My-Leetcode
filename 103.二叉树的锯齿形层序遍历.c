/*
 * @lc app=leetcode.cn id=103 lang=c
 *
 * [103] ¶þ²æÊ÷µÄ¾â³ÝÐÎ²ãÐò±éÀú
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
    struct TreeNode* left;
    struct TreeNode* right;
};
#endif

struct StackNode {
    struct TreeNode* node;
    int level;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
    struct StackNode* base;
    int size;
};

struct Stack* stack_create();
struct StackNode* stack_pop(struct Stack* stack);
void stack_push(struct Stack* stack, struct TreeNode* node, int level);
void stack_free(struct Stack* stack);
int** getResult(int* temp_result, int size, int* returnSize, int** returnColumnSizes);

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (!root) return NULL;

    int* temp_result = (int*)malloc(sizeof(int) * 4000);
    if (!temp_result) return NULL;

    struct Stack* stack_left = stack_create();
    struct Stack* stack_right = stack_create();

    if (!stack_left || !stack_right)
    {
        free(temp_result);
        free(stack_left);
        free(stack_right);
        return NULL;
    }

    stack_push(stack_left, root, 0);

    int index = 0;
    int now_level = 0;
    while (stack_left -> size + stack_right -> size > 0)
    {
        while (stack_left -> size > 0)
        {
            struct StackNode* Snode = stack_pop(stack_left);
            if (!Snode) continue;
            struct TreeNode* Tnode = Snode -> node;
            if (!Tnode)
            {
                free(Snode);
                continue;
            }
            int Level = Snode -> level;
            free(Snode);
            
            if (Level != now_level)
            {
                now_level = Level;
                temp_result[index++] = 1024;
            }
            temp_result[index++] = Tnode -> val;
        
            stack_push(stack_right, Tnode -> left, Level + 1);
            stack_push(stack_right, Tnode -> right, Level + 1);
        }

        while (stack_right -> size > 0)
        {
            struct StackNode* Snode = stack_pop(stack_right);
            if (!Snode) continue;
            struct TreeNode* Tnode = Snode -> node;
            if (!Tnode)
            {
                free(Snode);
                continue;
            }
            int Level = Snode -> level;
            free(Snode);

            if (Level != now_level)
            {
                now_level = Level;
                temp_result[index++] = 1024;
            }
            temp_result[index++] = Tnode -> val;
        
            stack_push(stack_left, Tnode -> right, Level + 1);
            stack_push(stack_left, Tnode -> left, Level + 1);
        }
    }
    stack_free(stack_left);
    stack_free(stack_right);

    return getResult(temp_result, index, returnSize, returnColumnSizes);
}

struct Stack* stack_create()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    struct StackNode* base = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!base)
    {
        free(stack);
        return NULL;
    }

    base -> node = NULL;
    base -> level = -1;
    base -> next = NULL;

    stack -> top = base;
    stack -> base = base;
    stack -> size = 0;

    return stack;
}


struct StackNode* stack_pop(struct Stack* stack)
{
    if (!stack || !stack -> size) return NULL;

    struct StackNode* node = stack -> top;
    stack -> top = stack -> top -> next;
    stack -> size --;
    
    return node;
}

void stack_push(struct Stack* stack, struct TreeNode* node, int level)
{
    if (!stack || !node) return ;
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) return ;

    newNode -> node = node;
    newNode -> level = level;
    newNode -> next = stack -> top;
    
    stack -> top = newNode;
    stack -> size ++;
}

void stack_free(struct Stack* stack)
{
    if (!stack) return ;
    while (stack ->  size > 0) free(stack_pop(stack));
    free(stack->base);
    free(stack);
}

int** getResult(int* temp_result, int size, int* returnSize, int** returnColumnSizes)
{
    int levels = 1;
    int* col_sizes = (int*)calloc(2000, sizeof(int));
    if (!col_sizes)
    {
        free(temp_result);
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        if (temp_result[i] == 1024)
        {
            levels++;
            continue;
        }
        col_sizes[levels - 1]++;
    }

    *returnSize = levels;

    *returnColumnSizes = (int*)malloc(levels * sizeof(int));
    if (!(*returnColumnSizes))
    {
        free(col_sizes);
        free(temp_result);
        return NULL;
    }
    for (int i = 0; i < levels; i++) (*returnColumnSizes)[i] = col_sizes[i];

    int** result = (int**)malloc(levels * sizeof(int*));
    if (!result)
    {
        free(col_sizes);
        free(*returnColumnSizes);
        free(temp_result);
        return NULL;
    }

    int current_level = 0;
    int current_index = 0;
    result[current_level] = (int*)malloc(col_sizes[current_level] * sizeof(int));
    if (!result[current_level])
    {
        for (int i = 0; i < current_level; i++)
            free(result[i]);
        free(result);
        free(col_sizes);
        free(*returnColumnSizes);
        free(temp_result);
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        if (temp_result[i] == 1024)
        {
            current_level++;
            result[current_level] = (int*)malloc(col_sizes[current_level] * sizeof(int));
            if (!result[current_level])
            {
                for (int j = 0; j <= current_level; j++)
                    free(result[j]);
                free(result);
                free(col_sizes);
                free(*returnColumnSizes);
                free(temp_result);
                return NULL;
            }
            current_index = 0;
            continue;
        }
        result[current_level][current_index++] = temp_result[i];
    }

    free(col_sizes);
    free(temp_result);
    return result;
}
// @lc code=end

