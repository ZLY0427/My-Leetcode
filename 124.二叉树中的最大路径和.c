/*
 * @lc app=leetcode.cn id=124 lang=c
 *
 * [124] 二叉树中的最大路径和
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

int dfs(struct TreeNode* root, int* maxpathval);

int maxPathSum(struct TreeNode* root)
{
    int maxval = -1024;
    dfs(root, &maxval);

    return maxval;
}

int dfs(struct TreeNode* root, int* maxpathval)
{
    if (!root) return -1024;

    int leftval = dfs(root -> left, maxpathval);
    int rightval = dfs(root -> right, maxpathval);
    int rootval = root -> val;

    int nowpathval = rootval;
    if (leftval + rootval > nowpathval) nowpathval = leftval + rootval;
    if (rightval + rootval > nowpathval) nowpathval = rightval + rootval;
    
    int returnval = nowpathval;
    
    if (leftval > nowpathval) nowpathval = leftval;
    if (rightval > nowpathval) nowpathval = rightval;
    if (leftval + rightval + rootval > nowpathval) nowpathval = leftval + rightval + rootval;
    

    if (nowpathval > *maxpathval) *maxpathval = nowpathval;

    return returnval;
}
// @lc code=end

