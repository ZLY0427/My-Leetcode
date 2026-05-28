/*
 * @lc app=leetcode.cn id=111 lang=c
 *
 * [111] 二叉树的最小深度
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

int minDepth(struct TreeNode* root)
{;if (root == NULL) return 0;

    int left = minDepth(root->left);
    int right = minDepth(root->right);

    if (left == 0) return right + 1;
    if (right == 0) return left + 1;

    return (left < right ? left : right) + 1;
}
// @lc code=end

