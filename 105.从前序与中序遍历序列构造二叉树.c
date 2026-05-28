/*
 * @lc app=leetcode.cn id=105 lang=c
 *
 * [105] 从前序与中序遍历序列构造二叉树
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

struct TreeNode* buildTree(int* preorder, int preorderSize,
                           int* inorder, int inorderSize)
{
    if (!preorder || !inorder || preorderSize <= 0 ||
        inorderSize <= 0 || preorderSize != inorderSize)
        return NULL;

    int rootVal = preorder[0];
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    if (!root) return NULL;

    root -> val = rootVal;

    int mid = 0;
    while (mid < inorderSize && inorder[mid] != rootVal) mid++;

    root -> left = buildTree(preorder + 1,
                             mid,
                             inorder,
                             mid);
    root -> right = buildTree(preorder + mid + 1,
                              preorderSize - mid - 1,
                              inorder + mid + 1,
                              inorderSize - mid - 1);
    return root;
}
// @lc code=end

