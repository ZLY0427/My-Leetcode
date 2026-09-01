/*
 * @lc app=leetcode.cn id=174 lang=c
 *
 * [174] 地下城游�?
 */

// @lc code=start
#include <stdlib.h>

int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize)
{
    if (!dungeon || !dungeonColSize) return 0;

    int row = dungeonSize;
    int col = dungeonColSize[0];

    if (row == 0 || col == 0) return 0;
    if (row == 1 && col == 1) return dungeon[0][0] > 0 ? 1 : 1 - dungeon[0][0];

    int** dp = (int**)malloc(sizeof(int *) * row);
    if (!dp) return -1;

    for (int i = 0; i < row; ++i)
    {
        dp[i] = (int*)malloc(sizeof(int) * col);
        if (!dp[i])
        {
            for (int j = 0; j < i; ++j)
            {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    dp[row-1][col-1] = (1 - dungeon[row-1][col-1]) > 1 ?
                       (1 - dungeon[row-1][col-1]) : 1;

    for(int j = col - 2; j >= 0; --j)
    {
        int val = dp[row - 1][j + 1] - dungeon[row - 1][j];
        dp[row - 1][j] = val > 1 ? val : 1;
    }

    for(int i = row - 2; i >= 0; --i)
    {
        int val = dp[i + 1][col - 1] - dungeon[i][col - 1];
        dp[i][col - 1] = val > 1 ? val : 1;
    }

    for(int i = row - 2; i >= 0; --i)
    {
        for(int j = col - 2; j >= 0; --j)
        {
            int minNext = dp[i + 1][j] < dp[i][j + 1] ? dp[i + 1][j] : dp[i][j + 1];
            int val = minNext - dungeon[i][j];
            dp[i][j] = val > 1 ? val : 1;
        }
    }

    int result = dp[0][0];
    for(int i = 0; i < row; ++i) free(dp[i]);
    free(dp);

    return result;
}
// @lc code=end

