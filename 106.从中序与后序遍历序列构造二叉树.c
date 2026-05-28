/*
 * @lc app=leetcode.cn id=106 lang=c
 *
 * [106] 从中序与后序遍历序列构造二叉树
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

 struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize)
{
    if (!postorder || !inorder || postorderSize <= 0 ||
        inorderSize <= 0 || postorderSize != inorderSize)
        return NULL;

    int rootVal = postorder[postorderSize - 1];
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    if (!root) return NULL;

    root -> val = rootVal;

    int mid = 0;
    while (mid < inorderSize && inorder[mid] != rootVal) mid++;

    root -> left = buildTree(inorder,
                             mid,
                             postorder,
                             mid);
    root -> right = buildTree(inorder + mid + 1,
                              inorderSize - mid - 1,
                              postorder + mid,
                              postorderSize - mid - 1);
    return root;
}
// @lc code=end

