/*
 * @lc app=leetcode.cn id=151 lang=c
 *
 * [151] 反转字符串中的单�?
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>

char* reverseWords(char* s)
{
    if (!s) return NULL;

    int len = strlen(s);
    if (len <= 1)
    {
        char* result = (char*)malloc(len + 1);
        strcpy(result, s);
        return result;
    }

    char* result = (char*)malloc(sizeof(char) * (len + 1));
    if (!result) return NULL;

    int left = 0;
    int right = len - 1;

    while(right >= 0)
    {
        while(right >=0 && s[right] == ' ')
            right--;
        if(right < 0) break;

        int end = right;
        while(right >=0 && s[right] != ' ')
            right--;
        int start = right + 1;

        for(int i = start; i <= end; ++i)
            result[left++] = s[i];
        result[left++] = ' ';
    }

    if(left > 0) left--;
    result[left] = '\0';
    
    return result;
}
// @lc code=end

