/*
 * @lc app=leetcode.cn id=173 lang=c
 *
 * [173] 二叉搜索树迭代器
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
#include <stdlib.h>
#include <stdbool.h>

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

typedef struct {
    struct TreeNode* node;
    struct Stack* stack;
} BSTIterator;

struct Stack* create_Stack();
void push_Stack(struct Stack* stack, struct TreeNode* node);
struct TreeNode* pop_Stack(struct Stack* stack);
void free_Stack(struct Stack* stack);

BSTIterator* bSTIteratorCreate(struct TreeNode* root)
{
    BSTIterator* obj = (BSTIterator*)malloc(sizeof(BSTIterator));
    if (!obj) return NULL;

    obj -> node = root;
    obj -> stack = create_Stack();
    if (!obj -> stack)
    {
        free(obj);
        return NULL;
    }

    return obj;
}

int bSTIteratorNext(BSTIterator* obj)
{
    while (obj -> node != NULL)
    {
        push_Stack(obj -> stack, obj -> node);
        obj -> node = obj -> node -> left;
    }
    struct TreeNode* cur = pop_Stack(obj -> stack);
    int res = cur -> val;
    obj -> node = cur -> right;
    return res;
}

bool bSTIteratorHasNext(BSTIterator* obj)
{
    return obj -> node || obj -> stack -> count > 0;
}

void bSTIteratorFree(BSTIterator* obj)
{
    if (!obj) return;

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

void push_Stack(struct Stack* stack, struct TreeNode* node)
{
    if (!stack || !node) return ;

    struct StackNode* Snode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!Snode) return;

    Snode -> node = node;
    Snode -> next = stack -> top;
    
    stack -> top = Snode;
    ++stack -> count;
}

struct TreeNode* pop_Stack(struct Stack* stack)
{
    if (!stack || stack -> count <= 0) return NULL;

    struct StackNode* Snode = stack -> top;
    struct TreeNode* node = Snode -> node;

    stack -> top = Snode -> next;
    --stack -> count;

    free(Snode);

    return node;
}

void free_Stack(struct Stack* stack)
{
    if (!stack) return;

    while (stack -> count > 0)
        pop_Stack(stack);

    free(stack);
}

/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);
 
 * bool param_2 = bSTIteratorHasNext(obj);
 
 * bSTIteratorFree(obj);
*/
// @lc code=end

