/*
 * @lc app=leetcode.cn id=114 lang=c
 *
 * [114] 二叉树展开为链表
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

#ifdef RUN_LOCATED_VSCODE
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
#endif

struct QueueNode{
    struct TreeNode* valnode;
    struct QueueNode* next;
};

struct Queue{
    struct QueueNode* head;
    struct QueueNode* tail;
    int count;
};

struct Queue* create_queue();
void push_queue(struct Queue* queue, struct TreeNode* node);
struct TreeNode* pop_queue(struct Queue* queue);
void Flatten(struct TreeNode* root, struct Queue* queue);

void flatten(struct TreeNode* root)
{
    if (!root) return ;

    struct Queue* queue = create_queue();
    if (!queue) return ;

    Flatten(root, queue);

    struct TreeNode* buffer = NULL;

    while (queue -> count > 0)
    {
        struct TreeNode* current = pop_queue(queue);
        current -> left = NULL;
        current -> right = NULL;

        if (buffer != NULL) buffer -> right = current;
        buffer = current;
    }
    
    free(queue);
}

void Flatten(struct TreeNode* root, struct Queue* queue)
{
    if (!root) return ;

    push_queue(queue, root);

    Flatten(root -> left, queue);
    Flatten(root -> right, queue);
}

struct Queue* create_queue()
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) return NULL;

    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> count = 0;

    return queue;
}

void push_queue(struct Queue* queue, struct TreeNode* node)
{
    if (!queue) return ;
    
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!newNode) return ;

    newNode -> valnode = node;
    newNode -> next = NULL;

    if (queue -> count == 0)
    {
        queue -> head = newNode;
        queue -> tail = newNode;
    }
    else
    {
        queue -> tail -> next = newNode;
        queue -> tail = newNode;
    }
    queue -> count++;
}

struct TreeNode* pop_queue(struct Queue* queue)
{
    if (!queue || queue -> count == 0) return NULL;
    
    struct QueueNode* qNode = queue -> head;
    queue -> head = queue -> head -> next;
    queue -> count--;

    struct TreeNode* tNode = qNode -> valnode;
    free(qNode);
    
    return tNode;
}
// @lc code=end

