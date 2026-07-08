/*
 * @lc app=leetcode.cn id=131 lang=c
 *
 * [131] 分割回文�?
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(char* s, int left, int right);

char*** partition(char* s, int* returnSize, int** returnColumnSizes)
{
    int len = strlen(s);

    *returnSize = 0;
    *returnColumnSizes = NULL;

    char*** result = (char***)malloc(sizeof(char**));

    

    return result;
}

bool is_palindrome(char* s, int left, int right)
{
    if (!s || left > right) return false;
    while (left < right) if (s[left++] != s[right--]) return false;

    return true;
}
// @lc code=end

