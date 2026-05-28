/*
 * @lc app=leetcode.cn id=17 lang=c
 *
 * [17] 电话号码的字母组合
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char *digitMap[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

int calculateTotalCombinations(char* digits);   // 计算可能的数组总数
void backtrack(char* digits, int index, char* current, char** result, int* returnSize);

char** letterCombinations(char* digits, int* returnSize)
{
    *returnSize = 0;
    int len = strlen(digits);

    if (len == 0)
    {
        return NULL;
    }

    int size = calculateTotalCombinations(digits);

    char** result = (char**)malloc(sizeof(char*) * size);
    if (result == NULL)
    {
        return NULL;
    }

    char* current = (char*)malloc(sizeof(char) * (len + 1));
    if (current == NULL)
    {
        free(result);
        return NULL;
    }
    current[len] = '\0';

    backtrack(digits, 0, current, result, returnSize);

    free(current);
    return result;
}

int calculateTotalCombinations(char* digits)
{
    if (digits == '\0')
    {
        return 0;
    }

    int size = 1;
    for (int i = 0; digits[i] != '\0'; i++)
    {
        int digit = digits[i] - '0';
        int tempSize = strlen(digitMap[digit]);

        size *= tempSize;
    }

    return size;
}

void backtrack(char* digits, int index, char* current, char** result, int* returnSize)
{
    if (digits[index] == '\0')
    {
        result[*returnSize] = (char *)malloc(strlen(current) + 1);
        strcpy(result[*returnSize], current);
        (*returnSize)++;
        return;
    }

    int digit = digits[index] - '0';
    char* tempstr = digitMap[digit];

    for (int i = 0; tempstr[i] != '\0'; i++)
    {
        current[index] = tempstr[i];
        current[index + 1] = '\0';

        backtrack(digits, index + 1, current, result, returnSize);
    }
}
// @lc code=end
