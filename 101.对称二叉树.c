/*
 * @lc app=leetcode.cn id=101 lang=c
 *
 * [101] 对称二叉�?
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
#include <stdbool.h>

#ifdef RUN_LOCATED_VSCODE
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
#endif

bool is_symmetric_tree(struct TreeNode* left, struct TreeNode* right);

bool isSymmetric(struct TreeNode* root)
{
    if (!root) return true;

    return is_symmetric_tree(root -> left, root -> right);
}

bool is_symmetric_tree(struct TreeNode* left, struct TreeNode* right)
{
    if (!left && !right) return true;
    if (!left || !right) return false;

    return left -> val == right -> val &&
           is_symmetric_tree(left -> left, right -> right) &&
           is_symmetric_tree(left -> right, right -> left);
}
// @lc code=end

