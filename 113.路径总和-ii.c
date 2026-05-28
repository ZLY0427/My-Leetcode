/*
 * @lc app=leetcode.cn id=113 lang=c
 *
 * [113] Â·¾¶×ÜºÍ II
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

void dfs(struct TreeNode* node, int target, int* path, int pathLen,
         int** res, int* resSize, int* returnColumnSizes);

int** pathSum(struct TreeNode* root, int targetSum,
              int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (!root) return NULL;

    int maxSize = 4000;
    int** res = (int**)malloc(maxSize * sizeof(int*));
    int* colSizes = (int*)malloc(maxSize * sizeof(int));
    int* path = (int*)malloc(maxSize * sizeof(int));

    dfs(root, targetSum, path, 0, res, returnSize, colSizes);

    *returnColumnSizes = colSizes;
    return res;
}

void dfs(struct TreeNode* node, int target, int* path, int pathLen,
         int** res, int* resSize, int* returnColumnSizes)
{
    if (!node) return;

    path[pathLen++] = node -> val;
    target -= node -> val;

    if (!node -> left && !node -> right && target == 0)
    {
        res[*resSize] = (int*)malloc(pathLen * sizeof(int));
        for (int i = 0; i < pathLen; ++i)
            res[*resSize][i] = path[i];
        
        returnColumnSizes[*resSize] = pathLen;
        ++(*resSize);
        --pathLen;
        return;
    }

    dfs(node -> left, target, path, pathLen, res, resSize, returnColumnSizes);
    dfs(node -> right, target, path, pathLen, res, resSize, returnColumnSizes);

    --pathLen;
}
// @lc code=end

