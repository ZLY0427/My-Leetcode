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

struct Node *cloneGraph(struct Node *s)
{
    if (!s) return NULL;
	bool* visited = calloc(101, sizeof(bool));
    if (!visited) return NULL;

    struct Node* copyNode = malloc(sizeof(struct Node));
    if (!copyNode)
    {
        free(visited);
        return NULL;
    }
    copyNode -> val = s -> val;
    copyNode -> numNeighbors = s -> numNeighbors;
    copyNode -> neighbors = malloc(sizeof(struct Node*) * copyNode -> numNeighbors);
    if (!copyNode -> neighbors)
    {
        free(copyNode);
        free(visited);
        return NULL;
    }
    for (int i = 0; i < copyNode -> numNeighbors; ++i)
        copyNode -> neighbors[i] = NULL;
    visited[s -> val] = true;
}
// @lc code=end

