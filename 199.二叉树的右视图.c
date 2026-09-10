/*
 * @lc app=leetcode.cn id=199 lang=c
 *
 * [199] 二叉树的右视�?
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
    struct TreeNode* left;
    struct TreeNode* right;
};
#endif

struct QueueNode {
    struct TreeNode* node;
    struct QueueNode* next;
    int node_deepth;
};

struct Queue {
    struct QueueNode* head;
    struct QueueNode* tail;
    int count;
};

struct Queue* create_Queue();
void push_Queue(struct Queue* queue, struct TreeNode* node, int node_deepth);
struct TreeNode* pop_Queue(struct Queue* queue, int* node_deepth);
void free_Queue(struct Queue* queue);

int* rightSideView(struct TreeNode* root, int* returnSize)
{
    if (!root)
    {
        *returnSize = 0;
        return NULL;
    }
    int* buffer = (int*)malloc(sizeof(int) * 100);
    if (!buffer)
    {
        *returnSize = 0;
        return NULL;
    }
    int index = 0;

    struct Queue* queue = create_Queue();
    if (!queue)
    {
        *returnSize = 0;
        free(buffer);
        return NULL;
    }
    int index_deepth = 0;

    push_Queue(queue, root, 1);
    while (queue -> count > 0)
    {
        int node_deepth;
        struct TreeNode* node = pop_Queue(queue, &node_deepth);
        if (node -> right) push_Queue(queue, node -> right, node_deepth + 1);
        if (node -> left) push_Queue(queue, node -> left, node_deepth + 1);

        if (node_deepth > index_deepth)
        {
            buffer[index] = node -> val;
            index_deepth = node_deepth;
            ++index;
        }
    }

    *returnSize = index;
    free_Queue(queue);

    int* result = (int*)realloc(buffer, sizeof(int) * index);
    return result;
}

struct Queue* create_Queue()
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) return NULL;

    queue -> head = queue -> tail = NULL;
    queue -> count = 0;

    return queue;
}

void push_Queue(struct Queue* queue, struct TreeNode* node, int node_deepth)
{
    if (!queue || !node) return ;
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!newNode) return ;

    newNode -> node = node;
    newNode -> next = NULL;
    newNode -> node_deepth = node_deepth;

    if (queue -> count <= 0)
    {
        queue -> head = queue -> tail = newNode;
        queue -> count = 1;
    }
    else
    {
        queue -> tail -> next = newNode;
        queue -> tail = newNode;
        ++queue -> count;
    }
}

struct TreeNode* pop_Queue(struct Queue* queue, int* node_deepth)
{
    if (!queue || !queue -> head || queue -> count <= 0) return NULL;

    struct QueueNode* Qnode = queue -> head;
    struct TreeNode* result = Qnode -> node;
    *node_deepth = Qnode -> node_deepth;

    queue -> head = Qnode -> next;
    free(Qnode);
    --queue -> count;

    return result;
}

void free_Queue(struct Queue* queue)
{
    if (!queue) return ;

    struct QueueNode* Qnode = queue -> head;
    while (Qnode)
    {
        struct QueueNode* temp = Qnode;
        Qnode = Qnode -> next;
        free(temp);
    }

    free(queue);
}

// @lc code=end

