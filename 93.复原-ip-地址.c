/*
 * @lc app=leetcode.cn id=93 lang=c
 *
 * [93] ∏¥‘≠ IP µÿ÷∑
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isEffectiveIP(char* s, int left, int right);

char** restoreIpAddresses(char* s, int* returnSize)
{
    *returnSize = 0;
    if (!s || strlen(s) < 4 || strlen(s) > 12) return NULL;
    
    int sSize = strlen(s);
}

bool isEffectiveIP(char* s, int left, int right)
{
    int size = right - left + 1;
    if (!s || size < 0 || size > 3) return false;
    if (s[0] == '0' && size > 1) return false;

    int result = 0;
    for (int i = left; i <= right; i++)
    {
        if (s[i] < '0' || s[i] > '9') return false;
        
        result = result * 10 + (s[i] - '0');
        
        if (result > 255) return false;
    }

    return true;
}
// @lc code=end

