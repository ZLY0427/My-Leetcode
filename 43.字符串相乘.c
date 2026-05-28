/*
 * @lc app=leetcode.cn id=43 lang=c
 *
 * [43] ×Ö·û´®Æ¥ÅäÏà³Ë
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>

char* multiply(char* num1, char* num2)
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    if (len1 == 0 || len2 == 0)
    {
        char* result = (char*)malloc(sizeof(char) * 2);
        if (!result) return NULL;
        result[0] = '0', result[1] = '\0';
        return result;
    }

    int* result = (int*)calloc(len1 + len2, sizeof(int));
    if (!result) return NULL;

    for (int i = len1 - 1; i >= 0; i--)
    {
        int n1 = num1[i] - '0';
        for (int j = len2 - 1; j >= 0; j--)
        {
            int n2 = num2[j] - '0';
            int mul = n1 * n2;
            int p1 = i + j;
            int p2 = i + j + 1;
            int sum = mul + result[p2];

            result[p1] += sum / 10;
            result[p2] = sum % 10;
        }
    }

    char* resStr = (char*)malloc(len1 + len2 + 1);
    if (!resStr)
    {
        free(result);
        return NULL;
    }
    int idx = 0;

    while (idx < len1 + len2 - 1 && result[idx] == 0)
    {
        idx++;
    }

    int resIdx = 0;
    for (; idx < len1 + len2; idx++)
    {
        resStr[resIdx++] = result[idx] + '0';
    }

    resStr[resIdx] = '\0';

    free(result);
    return resStr;
}
// @lc code=end

