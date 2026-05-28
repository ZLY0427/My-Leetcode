/*
 * @lc app=leetcode.cn id=110 lang=c
 *
 * [110] Æ½ºâ¶þ²æÊ÷
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

int getHeight(struct TreeNode* root);

bool isBalanced(struct TreeNode* root)
{
    if (!root) return true;

    int leftHeight = getHeight(root -> left);
    int rightHeight = getHeight(root -> right);

    return abs(leftHeight - rightHeight) <= 1 && isBalanced(root -> left) && isBalanced(root -> right);
}

int getHeight(struct TreeNode* root)
{
    if (!root) return 0;

    int leftHeight = getHeight(root -> left);
    int rightHeight = getHeight(root -> right);

    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}
// @lc code=end

