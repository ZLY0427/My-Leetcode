/*
 * @lc app=leetcode.cn id=100 lang=c
 *
 * [100] 相同的树
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
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif

bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
    if (!p && !q) return true;
    else if (!p || !q) return false;

    if (p -> val == q -> val)
        return isSameTree(p -> left, q -> left) && isSameTree(p -> right, q -> right);

    else return false;
}
// @lc code=end

