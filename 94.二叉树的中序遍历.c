/*
 * @lc app=leetcode.cn id=94 lang=c
 *
 * [94] 二叉树的中序遍历
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

#define MAX_NODE_SIZE 100

#ifdef RUN_LOCATED_VSCODE
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif

void inordertraversal(struct TreeNode* root, int* result, int* index);

int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    (*returnSize) = 0;
    if (!root) return NULL;

    int* temp = (int*)malloc(sizeof(int) * MAX_NODE_SIZE);
    
    inordertraversal(root, temp, returnSize);
    int* result = (int*)realloc(temp, sizeof(int) * (*returnSize));

    return result;
}

void inordertraversal(struct TreeNode* root, int* result, int* index)
{
    if (!root) return ;

    // 进左子树
    inordertraversal(root -> left, result, index);

    // 添加当前节点
    result[(*index)++] = root -> val;

    // 进右子树
    inordertraversal(root -> right, result, index);
}
// @lc code=end

