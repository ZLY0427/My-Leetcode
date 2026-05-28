/*
 * @lc app=leetcode.cn id=99 lang=c
 *
 * [99] »Ö¸´¶þ²æËÑË÷Ê÷
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
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif

void inorder_traversal(struct TreeNode* root, int* result, int* returnSize);
int* getError(int* nums, int numsSize, int* returnSize);
void changeTree(struct TreeNode* root, int* error, int errorSize);

void recoverTree(struct TreeNode* root)
{
    int* temp = (int*)malloc(sizeof(int) * 1000);
    if (!temp) return ;

    int returnSize = 0;

    inorder_traversal(root, temp, &returnSize);

    int* result = (int*)realloc(temp, sizeof(int) * returnSize);
    if (!result) return ;

    int errorSize = 0;
    int* error = getError(result, returnSize, &errorSize);
    if (!error)
    {
        free(result);
        free(error);
        return ;
    }

    changeTree(root, error, errorSize);

    free(result);
    free(error);
    return ;
}

void inorder_traversal(struct TreeNode* root, int* result, int* returnSize)
{
    if (!root) return ;

    inorder_traversal(root -> left, result, returnSize);

    result[(*returnSize)++] = root -> val;

    inorder_traversal(root -> right, result, returnSize);
}

int* getError(int* nums, int numsSize, int* returnSize)
{
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    if (result == NULL)
    {
        *returnSize = 0;
        return NULL;
    }

    int first = -1, second = -1;
    int errorCount = 0;

    for (int i = 0; i < numsSize - 1; i++)
    {
        if (nums[i] > nums[i + 1])
        {
            errorCount++;
            if (errorCount == 1)
            {
                first = nums[i];
                second = nums[i + 1];
            }
            else if (errorCount == 2)
            {
                second = nums[i + 1];
            }
        }
    }
    result[0] = first;
    result[1] = second;

    return result;
}

void changeTree(struct TreeNode* root, int* error, int errorSize)
{
    if (!root) return ;

    if (root -> val == error[0])
        root -> val = error[1];
    else if (root -> val == error[1])
        root -> val = error[0];

    changeTree(root -> left, error, errorSize);
    changeTree(root -> right, error, errorSize);
}
// @lc code=end

