/*
 * @lc app=leetcode.cn id=98 lang=c
 *
 * [98] ÑéÖ¤¶þ²æËÑË÷Ê÷
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
#include <limits.h>
#include <stdbool.h>

#ifdef RUN_LOCATED_VSCODE
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif

bool is_valid_BST(struct TreeNode* root, long long max_val, long long min_val);

bool isValidBST(struct TreeNode* root)
{
    return is_valid_BST(root, LLONG_MAX, LLONG_MIN);
}

bool is_valid_BST(struct TreeNode* root, long long max_val, long long min_val)
{
    if (!root) return true;
    if (root -> val <= min_val || root -> val >= max_val) return false;

    return is_valid_BST(root -> left, root -> val, min_val) &&
           is_valid_BST(root -> right, max_val, root -> val);
}
// @lc code=end

