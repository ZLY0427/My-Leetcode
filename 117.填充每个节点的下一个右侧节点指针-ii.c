/*
 * @lc app=leetcode.cn id=117 lang=c
 *
 * [117] 填充每个节节点的下一个右侧节点指针 II
 */

// @lc code=start
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */
#include <stdlib.h>

#ifdef RUN_LOCATED_VSCODE
struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    struct Node* next;
};
#endif

struct QueueNode {
    struct Node* tnode;
    int deep;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* head;
    struct QueueNode* tail;
    int number;
};

struct Queue* current_queue();
void push_queue(struct Queue* queue, struct Node* node, int deep);
struct QueueNode* pop_queue(struct Queue* queue);
void free_queue(struct Queue* queue);

struct Node* connect(struct Node* root)
{
	if (!root) return NULL;

    struct Queue* queue = current_queue();
    if (!queue) return NULL;

    push_queue(queue, root, 1);
    while (queue -> number > 0)
    {
        struct QueueNode* qnode = pop_queue(queue);
        struct Node* tnode = qnode -> tnode;
        int nowdeep = qnode -> deep;
        int nextdeep = 2;
        if (queue -> number > 0)
        {
            nextdeep = queue -> head -> deep;
        }

        if (nowdeep != nextdeep)
        {
            tnode -> next = NULL;
        }
        else if (queue -> number > 0)
        {
            tnode -> next = queue -> head -> tnode;
        }
        else
        {
            tnode -> next = NULL;
        }

        push_queue(queue, tnode -> left, nowdeep + 1);
        push_queue(queue, tnode -> right, nowdeep + 1);

        free(qnode);
    }

    free_queue(queue);
    return root;
}

struct Queue* current_queue()
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) return NULL;

    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> number = 0;

    return queue;
}

void push_queue(struct Queue* queue, struct Node* node, int deep)
{
    if (!queue || !node) return ;
    struct QueueNode* qnode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!qnode) return ;

    qnode -> tnode = node;
    qnode -> deep = deep;
    qnode -> next = NULL;

    if (queue -> number <= 0)
    {
        queue -> head = qnode;
        queue -> tail = qnode;
    }
    else
    {
        queue -> tail -> next = qnode;
        queue -> tail = qnode;
    }

    queue -> number++;
}

struct QueueNode* pop_queue(struct Queue* queue)
{
    if (!queue || queue -> number <= 0) return NULL;

    struct QueueNode* qnode = queue -> head;
    queue -> head = qnode -> next;
    queue -> number--;

    if (queue -> number <= 0) queue -> tail = NULL;

    return qnode;
}

void free_queue(struct Queue* queue)
{
    if (!queue) return ;

    struct QueueNode* qnode = queue -> head;
    while (qnode)
    {
        struct QueueNode* next = qnode -> next;
        free(qnode);
        qnode = next;
    }

    free(queue);
}
// @lc code=end

