/*
 * @lc app=leetcode.cn id=44 lang=c
 *
 * [44] Õ®≈‰∑˚∆•≈‰
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isMatch(char* s, char* p)
{
    if (!s || !p) return false;

    int sSize = strlen(s), pSize = strlen(p);

    bool** is_match = (bool**)calloc(sSize + 1, sizeof(bool*));
    if (!is_match) return false;;

    for (int i = 0; i <= sSize; i++)
    {
        is_match[i] = (bool*)calloc(pSize + 1, sizeof(bool));
        if (!is_match[i])
        {
            for (int j = 0; j < i; j++)
            {
                free(is_match[j]);
            }
            free(is_match);
            return false;
        }
    }

    is_match[0][0] = true;

    for (int j = 1; j <= pSize; j++)
    {
        if (p[j - 1] == '*')
            is_match[0][j] = is_match[0][j - 1];
    }

    for (int i = 1; i <= sSize; i++)
    {
        for (int j = 1; j <= pSize; j++)
        {
            if (p[j - 1] == '*')
            {
                is_match[i][j] = is_match[i - 1][j] || is_match[i][j - 1];
            }
            else if (p[j - 1] == '?' || p[j - 1] == s[i - 1])
            {
                is_match[i][j] = is_match[i - 1][j - 1];
            }
        }
    }

    int result = is_match[sSize][pSize];

    for (int i = 0; i < sSize; i++)
    {
        free(is_match[i]);
    }
    free(is_match);
    
    return result;
}
// @lc code=end

