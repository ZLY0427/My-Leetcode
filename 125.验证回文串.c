/*
 * @lc app=leetcode.cn id=125 lang=c
 *
 * [125] 验证回文串
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>

bool isLetter(char c);
char getLowercaseLetter(char c);

bool isPalindrome(char* s)
{
    if (!s) return true;
    int sSize = strlen(s);
    if (sSize <= 0) return true;

    int left = 0, right = sSize - 1;
    while (left < right)
    {
        if (!isLetter(s[left]))
        {
            ++left;
            continue;
        }
        if (!isLetter(s[right]))
        {
            --right;
            continue;
        }
        if (getLowercaseLetter(s[left]) != getLowercaseLetter(s[right]))
            return false;
        ++left;
        --right;
    }

    return true;
}

bool isLetter(char c)
{
    return ('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

char getLowercaseLetter(char c)
{
    if ('A' <= c && c <= 'Z') return c - 'A' + 'a';
    return c;
}
// @lc code=end

