/*
 * @lc app=leetcode.cn id=115 lang=c
 *
 * [115] 不同的子序列
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int numDistinct(char* s, char* t)
{
    if (!s || !t) return 0;
    
    int sSize = strlen(s);
    int tSize = strlen(t);

    if (tSize == 0) return 1;
    if (sSize < tSize) return 0;


    unsigned long long** dp = (unsigned long long**)malloc(sizeof(unsigned long long*) * (sSize + 1));
    if (!dp) return -1;
    for (int i = 0; i <= sSize; ++i)
    {
        dp[i] = (unsigned long long*)malloc(sizeof(unsigned long long) * (tSize + 1));
        if (!dp[i])
        {
            for (int j = 0; j < i; ++j) free(dp[j]);
            free(dp);
            return -1;
        }
    }

    for (int i = 0; i <= sSize; ++i) dp[i][0] = 1;
    for (int j = 1; j <= tSize; ++j) dp[0][j] = 0;

    for (int i = 1; i <= sSize; ++i)
        for (int j = 1; j <= tSize; ++j)
            dp[i][j] = (s[i - 1] == t[j - 1]) ? dp[i - 1][j - 1] + dp[i - 1][j] : dp[i - 1][j];

    int result = (int)dp[sSize][tSize];
    for (int i = 0; i < sSize; ++i) free(dp[i]);
    free(dp);

    return result;
}
// @lc code=end

