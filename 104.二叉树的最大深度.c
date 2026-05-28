/*
 * @lc app=leetcode.cn id=104 lang=c
 *
 * [104] 二叉树的最大深度
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
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
#endif

int getMax(int val1, int val2);

int maxDepth(struct TreeNode* root)
{
    if (!root) return 0;
    return 1 + getMax(maxDepth(root -> left), maxDepth(root -> right));
}

int getMax(int val1, int val2)
{
    return val1 > val2 ? val1 : val2;
}
// @lc code=end

