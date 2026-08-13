/*
 * @lc app=leetcode.cn id=145 lang=c
 *
 * [145] 二叉树的后序遍历
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

#ifdef RUN_LOCATED_VSCODE
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif

struct StackNode {
    struct TreeNode* node;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
    int count;
};

struct Stack* create_Stack();
void push_Stack(struct Stack* stack, struct TreeNode* node);
struct TreeNode* pop_Stack(struct Stack* stack);
void delete_Stack(struct Stack* stack);
void reverseArray(int* array, int size);
void swap(int* num1, int* num2);

int* postorderTraversal(struct TreeNode* root, int* returnSize)
{
    *returnSize = 0;
    if (!root) return NULL;

    int* buffer = (int*)malloc(sizeof(int) * 100);
    if (!buffer) return NULL;

    struct Stack* stack = create_Stack();
    if (!stack) return NULL;

    push_Stack(stack, root);
    while(stack->count > 0)
    {
        struct TreeNode* cur = pop_Stack(stack);
        buffer[(*returnSize)++] = cur -> val;

        if(cur -> left != NULL) push_Stack(stack, cur -> left);
        if(cur -> right != NULL) push_Stack(stack, cur -> right);
    }

    reverseArray(buffer, *returnSize);

    delete_Stack(stack);

    int* result = (int*)realloc(buffer, sizeof(int) * (*returnSize));
    
    return result;
}

struct Stack* create_Stack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    stack -> top = NULL;
    stack -> count = 0;

    return stack;
}

void push_Stack(struct Stack* stack, struct TreeNode* node)
{
    if (!stack) return ;
    struct StackNode* stack_node = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!stack_node) return ;

    stack_node -> node = node;
    stack_node -> next = stack -> top;
    
    stack -> top = stack_node;
    ++(stack -> count);
}

struct TreeNode* pop_Stack(struct Stack* stack)
{
    if (!stack) return NULL;
    if (stack -> count <= 0) return NULL;

    struct StackNode* stack_node = stack -> top;
    struct TreeNode* node = stack_node -> node;

    stack -> top = stack_node -> next;
    --(stack -> count);

    free(stack_node);

    return node;
}

void delete_Stack(struct Stack* stack)
{
    if (!stack) return ;

    while (stack -> count > 0)
        pop_Stack(stack);

    free(stack);
}

void reverseArray(int* array, int size)
{
    for (int i = 0, j = size - 1; i < j; ++i, --j)
        swap(&array[i], &array[j]);
}

void swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
// @lc code=end

