/*
 * @lc app=leetcode.cn id=95 lang=c
 *
 * [95] 不同的二叉搜索树 II
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

struct TreeNode** generate(int start, int end, int* subSize);

struct TreeNode** generateTrees(int n, int* returnSize)
{
    if (n == 0)
    {
        *returnSize = 0;
        return NULL;
    }
    
    return generate(1, n, returnSize);
}

struct TreeNode** generate(int start, int end, int* subSize)
{
    if (start > end)
    {
        *subSize = 1;
        struct TreeNode** res = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
        res[0] = NULL;
        return res;
    }

    *subSize = 0;
    struct TreeNode** res = NULL;

    // 遍历每个数作为根节点
    for (int i = start; i <= end; i++)
    {
        int leftSize, rightSize;
        // 递归生成左子树集合 [start, i-1]
        struct TreeNode** leftTrees = generate(start, i - 1, &leftSize);
        // 递归生成右子树集合 [i+1, end]
        struct TreeNode** rightTrees = generate(i + 1, end, &rightSize);

        // 组合左、右子树与当前根节点
        int newSize = *subSize + leftSize * rightSize;
        // 重新分配内存，容纳新的树
        res = (struct TreeNode**)realloc(res, newSize * sizeof(struct TreeNode*));
        if (!res)
        {
            // 内存分配失败，释放已申请资源
            for (int p = 0; p < leftSize; p++) free(leftTrees[p]);
            free(leftTrees);
            for (int p = 0; p < rightSize; p++) free(rightTrees[p]);
            free(rightTrees);
            *subSize = 0;
            return NULL;
        }

        // 遍历所有左、右子树组合
        for (int l = 0; l < leftSize; l++)
        {
            for (int r = 0; r < rightSize; r++)
            {
                // 创建当前根节点
                struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                root -> val = i;
                root -> left = leftTrees[l];   // 左子树（复用，无需深拷贝）
                root -> right = rightTrees[r]; // 右子树（复用，无需深拷贝）
                res[*subSize] = root;
                (*subSize)++;
            }
        }

        // 释放子树数组（节点已被复用，只需释放数组本身）
        free(leftTrees);
        free(rightTrees);
    }

    return res;
}
// @lc code=end

