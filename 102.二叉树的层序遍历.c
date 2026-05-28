/*
 * @lc app=leetcode.cn id=102 lang=c
 *
 * [102] 二叉树的层次遍历
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
    struct TreeNode* treeNode;
    int level;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
    int size;
};

struct Queue* queue_create();
void queue_push(struct Queue* queue, int level, struct TreeNode* node);
struct QueueNode* queue_pop(struct Queue* queue);
void queue_free(struct Queue* queue);
int** getResult(int* temp_result, int size, int* returnSize, int** returnColumnSizes);

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (!root) return NULL;

    struct Queue* queue = queue_create();
    if (!queue) return NULL;

    int* temp_result = (int*)calloc(4000, sizeof(int));
    if (!temp_result)
    {
        queue_free(queue);
        return NULL;
    }

    queue_push(queue, 0, root);

    int now_level = 0;
    int index = 0;
    while (queue -> size > 0)
    {
        struct QueueNode* Qnode = queue_pop(queue);
        if (!Qnode) continue;
        struct TreeNode* Tnode = Qnode -> treeNode;
        if (!Tnode) continue;
        int Level = Qnode -> level;
        free(Qnode);

        if (Level != now_level)
        {
            now_level = Level;
            temp_result[index++] = 1024;
        }
        temp_result[index++] = Tnode -> val;

        queue_push(queue, Level + 1, Tnode -> left);
        queue_push(queue, Level + 1, Tnode -> right);
    }

    queue_free(queue);

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

void queue_push(struct Queue* queue, int level, struct TreeNode* node)
{
    if (!queue || !node) return;
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!newNode) return;

    newNode -> treeNode = node;
    newNode -> level = level;
    newNode -> next = NULL;

    if (queue -> size == 0)
    {
        queue -> front = newNode;
        queue -> rear = newNode;
    }
    else
    {
        queue -> rear -> next = newNode;
        queue -> rear = newNode;
    }
    queue -> size++;
}

struct QueueNode* queue_pop(struct Queue* queue)
{
    if (!queue || queue -> size == 0) return NULL;
    struct QueueNode* temp = queue -> front;
    queue -> front = queue -> front -> next;
    queue -> size--;
    if (queue -> size == 0) queue -> rear = NULL;
    return temp;
}

void queue_free(struct Queue* queue)
{
    if (!queue) return;
    while (queue -> size > 0)
    {
        struct QueueNode* temp = queue_pop(queue);
        free(temp);
    }
    free(queue);
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

