/*
 * @lc app=leetcode.cn id=66 lang=c
 *
 * [66] º”“ª
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

/*
int* plusOne(int* digits, int digitsSize, int* returnSize) 
{
    int carry = 1;

    for (int i = digitsSize - 1; i >= 0 && carry; i--) 
    {
        int sum = digits[i] + carry;
        digits[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry) 
    {
        *returnSize = digitsSize + 1;
        int* result = (int*)malloc(*returnSize * sizeof(int));
        result[0] = 1;
        for (int i = 0; i < digitsSize; i++) 
        {
            result[i + 1] = digits[i];
        }
        return result;
    }
    else 
    {
        *returnSize = digitsSize;
        int* result = (int*)malloc(*returnSize * sizeof(int));
        for (int i = 0; i < digitsSize; i++)
        {
            result[i] = digits[i];
        }
        return result;
    }
}
*/
int* plusOne(int* digits, int digitsSize, int* returnSize)
{
    int carry = 1;
    int* result = (int*)malloc(digitsSize * sizeof(int));
    if (!result)
    {
        return NULL;
    }

    for (int i = digitsSize - 1; i >= 0; i--)
    {
        int sum = digits[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;

        if (carry == 0) 
        {
            for (int j = i - 1; j >= 0; j--) 
            {
                result[j] = digits[j];
            }
            *returnSize = digitsSize;
            return result;
        }
    }
    
    free(result);
    *returnSize = digitsSize + 1;
    result = (int*)calloc(*returnSize, sizeof(int));
    if (!result)
    {
        return NULL;
    }
    result[0] = 1;
    return result;
}
// @lc code=end
