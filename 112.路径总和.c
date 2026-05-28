/*
 * @lc app=leetcode.cn id=112 lang=c
 *
 * [112] Â·¾¶×ÜºÍ
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
#include <stdbool.h>

#ifdef RUN_LOCATED_VSCODE
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
#endif

bool has_path_sum(struct TreeNode* current, int nowSum, int targetSum);

bool hasPathSum(struct TreeNode* root, int targetSum)
{
    return has_path_sum(root, 0, targetSum);
}

bool has_path_sum(struct TreeNode* current, int nowSum, int targetSum)
{
    if (!current) return false;

    nowSum += current -> val;

    if (nowSum == targetSum && !current -> left && !current -> right)
        return true;

    return has_path_sum(current -> left, nowSum, targetSum) ||
           has_path_sum(current -> right, nowSum, targetSum);
}
// @lc code=end

