/*
 * @lc app=leetcode.cn id=5 lang=c
 *
 * [5] 最长回文子串
 */

// @lc code=start
#include <stdlib.h>

int expandAroundCenter(char* s, int left, int right);

char* longestPalindrome(char* s)
{
    if (s == NULL || s[0] == '\0')
    {
        char* result = (char*)malloc(1);
        result[0] = '\0';
        return result;
    }

    int start = 0, end = 0;
    int len = strlen(s);
    
    for (int i = 0; i < len; i++)
    {
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        int max_len;
        if (len1 >= len2)
        {
            max_len = len1;
        }
        else
        {
            max_len = len2;
        }
        
        if (max_len > end - start)
        {
            start = i - (max_len - 1) / 2;
            end = i + max_len / 2;
        }
    }

    int palindrome_len = end - start + 1;
    char* result = (char*)malloc(palindrome_len + 1);
    strncpy(result, s + start, palindrome_len);
    result[palindrome_len] = '\0';
    
    return result;
}

int expandAroundCenter(char* s, int left, int right)
{
    while ((left >= 0) && (s[right] != '\0') && (s[left] == s[right]))
    {
        left--;
        right++;
    }
    return right - left - 1;
}

// @lc code=end
