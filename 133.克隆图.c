/*
 * @lc app=leetcode.cn id=133 lang=c
 *
 * [133] ¿ËÂ¡Í¼
 */

// @lc code=start
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */
#include <stdlib.h>
#include <stdbool.h>

#ifdef RUN_LOCATED_VSCODE
struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};
#endif

struct QueueNode {
    struct Node* node;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* head;
    struct QueueNode* real;
    int length;
};

struct Queue* Create_Queue();
void Push_Queue(struct Queue* queue, struct Node* node);
struct QueueNode* Pop_Queue(struct Queue* queue);
void Delete_Queue(struct Queue* queue);

struct Node *cloneGraph(struct Node *s)
{
    if (!s) return NULL;

    struct Node** cloneMap = (struct Node**)calloc(101, sizeof(struct Node*));
    struct Queue* queue = Create_Queue();
    if (!cloneMap || !queue)
    {
        free(cloneMap);
        Delete_Queue(queue);
        return NULL;
    }

    struct Node* copyS = (struct Node*)malloc(sizeof(struct Node));
    copyS -> val = s -> val;
    cloneMap[s -> val] = copyS;
    Push_Queue(queue, s);

    while (queue -> length > 0)
    {
        struct QueueNode* qNode = Pop_Queue(queue);
        struct Node* cur = qNode -> node;
        free(qNode);

        struct Node* copyCur = cloneMap[cur -> val];
        
        copyCur -> numNeighbors = cur -> numNeighbors;
        copyCur -> neighbors = (struct Node**)malloc(sizeof(struct Node*) * cur -> numNeighbors);

        for (int i = 0; i < cur -> numNeighbors; ++i)
        {
            struct Node* oriNei = cur -> neighbors[i];
            if (!cloneMap[oriNei -> val])
            {
                struct Node* copyNei = (struct Node*)malloc(sizeof(struct Node));
                copyNei -> val = oriNei -> val;
                cloneMap[oriNei -> val] = copyNei;
                Push_Queue(queue, oriNei);
            }
            copyCur -> neighbors[i] = cloneMap[oriNei -> val];
        }
    }

    Delete_Queue(queue);
    free(cloneMap);
    return copyS;
}

struct Queue* Create_Queue()
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) return NULL;

    queue -> head = NULL;
    queue -> real = NULL;
    queue -> length = 0;

    return queue;
}

void Push_Queue(struct Queue* queue, struct Node* node)
{
    if (!queue || !node) return ;
    
    struct QueueNode* queueNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!queueNode) return ;
    
    queueNode -> node = node;
    queueNode -> next = NULL;

    if (queue -> length == 0)
        queue -> head = queue -> real = queueNode;
    else
    {
        queue -> real -> next = queueNode;
        queue -> real = queueNode;
    }
    ++(queue -> length);
}

struct QueueNode* Pop_Queue(struct Queue* queue)
{
    if (!queue || queue -> length <= 0) return NULL;

    struct QueueNode* queueNode = queue -> head;
    if (queue -> length == 1)
        queue -> head = queue -> real = NULL;
    else
        queue -> head = queueNode -> next;

    --(queue -> length);

    return queueNode;
}

void Delete_Queue(struct Queue* queue)
{
    if (!queue) return ;

    while (queue -> length > 0) free(Pop_Queue(queue));

    free(queue);
}
// @lc code=end

