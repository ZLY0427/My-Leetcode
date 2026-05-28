/*
 * @lc app=leetcode.cn id=109 lang=c
 *
 * [109] ÓÐÐòÁ´±í×ª»»¶þ²æËÑË÷Ê÷
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
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
struct ListNode {
    int val;
    struct ListNode* next;
};

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
#endif

struct TreeNode* buildTree(int* nums, int sleft, int right);

struct TreeNode* sortedListToBST(struct ListNode* head)
{
    if (!head) return NULL;

    int listSize = 0;
    struct ListNode* current = head;
    
    while (current) 
    {
        ++listSize;
        current = current -> next;
    }

    int* nums = (int*)malloc(sizeof(int) * listSize);
    if (!nums) return NULL;

    current = head;
    for (int i = 0; i < listSize; ++i)
    {
        nums[i] = current -> val;
        current = current -> next;
    }

    return buildTree(nums, 0, listSize - 1);
}

struct TreeNode* buildTree(int* nums, int left, int right)
{
    if (left > right) return NULL;

    int mid = left + (right - left) / 2;

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root -> val = nums[mid];

    root -> left = buildTree(nums, left, mid - 1);
    root -> right = buildTree(nums, mid + 1, right);

    return root;
}
// @lc code=end

