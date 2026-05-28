/*
 * @lc app=leetcode.cn id=14 lang=c
 *
 * [14] 最长公共前缀
 */

// @lc code=start
#include <stdbool.h>

char* longestCommonPrefix(char** strs, int strsSize)
{
    if (strsSize == 0)
    {
        return "";
    }
    if (strsSize == 1)
    {
        return strs[0];
    }
    int MinLen = strlen(strs[0]);
    for (int i = 1; i < strsSize; i++)
    {
        int len = strlen(strs[i]);
        if (MinLen > len)
        {
            MinLen = len;
        }
    }
    if (MinLen == 0)
    {
        return "";
    }
    char* result = (char*)malloc(sizeof(char) * (MinLen + 1));
    result[0] = '\0';
    for (int i = 0; i < MinLen; i++)
    {
        bool is_same = true;
        for (int j = 1; j < strsSize; j++)
        {
            char temp = strs[0][i];
            if (strs[j][i] != temp)
            {
                is_same = false;
                break;
            }
        }
        if (is_same)
        {
            result[i] = strs[0][i];
        }
        else
        {
            result[i] = '\0';
            return result;
        }
    }
    result[MinLen] = '\0';
    return result;
}

// @lc code=end

