/*
 * @lc app=leetcode.cn id=129 lang=c
 *
 * [129] 求根节点到叶节点数字之和
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

void dfs(struct TreeNode* root, int nodesum, int* sum);

int sumNumbers(struct TreeNode* root)
{
    int result = 0;

    if (!root) return result;

    dfs(root, 0, &result);

    return result;
}

void dfs(struct TreeNode* root, int nodesum, int* sum)
{
    if (!root) return ;

    nodesum = nodesum * 10 + root -> val;
    if (!root -> left && !root -> right) (*sum) += nodesum;

    dfs(root -> left, nodesum, sum);
    dfs(root -> right, nodesum, sum);
}
// @lc code=end

