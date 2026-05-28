/*
 * @lc app=leetcode.cn id=72 lang=c
 *
 * [72] 编辑距离
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>

int minDistance(char* word1, char* word2)
{
    int m = strlen(word1);
    int n = strlen(word2);

    // 创建 (m+1) x (n+1) 的 DP 表
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++)
    {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
    }

    // 初始化边界
    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j;
    }

    // 填充 DP 表
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (word1[i - 1] == word2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                int replace = dp[i - 1][j - 1];
                int del = dp[i - 1][j];
                int insert = dp[i][j - 1];
                int min = replace < del ? replace : del;
                min = min < insert ? min : insert;
                dp[i][j] = min + 1;
            }
        }
    }

    int result = dp[m][n];

    // 释放内存
    for (int i = 0; i <= m; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return result;
}
// @lc code=end

