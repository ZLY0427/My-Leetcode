/*
 * @lc app=leetcode.cn id=64 lang=c
 *
 * [64] 最小路径和
 */

// @lc code=start
#include <stdlib.h>

int minPathSum(int** grid, int gridSize, int* gridColSize)
{
    int m = gridSize;
    int n = gridColSize[0];

    if (m <= 0 || n <= 0) return -2;

    int** minPathValue = (int**)malloc(sizeof(int*) * m);
    if (!minPathValue) return -1;

    for (int indexForMalloc = 0; indexForMalloc < m; indexForMalloc++)
    {
        minPathValue[indexForMalloc] = (int*)malloc(sizeof(int) * n);
        if (!minPathValue[indexForMalloc])
        {
            for (int indexForFree = 0; indexForFree < indexForMalloc; indexForFree++)
                free(minPathValue[indexForFree]);
            
            free(minPathValue);

            return -1;
        }
    }

    minPathValue[0][0] = grid[0][0];
    for (int i = 1; i < m; i++) minPathValue[i][0] = minPathValue[i - 1][0] + grid[i][0];
    for (int i = 1; i < n; i++) minPathValue[0][i] = minPathValue[0][i - 1] + grid[0][i];

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            minPathValue[i][j] = minPathValue[i - 1][j] > minPathValue[i][j - 1] ? minPathValue[i][j - 1] + grid[i][j] : minPathValue[i - 1][j] + grid[i][j];
        }
    }

    int result = minPathValue[m - 1][n - 1];

    for (int indexForFree = 0; indexForFree < m; indexForFree++)
        free(minPathValue[indexForFree]);
            
    free(minPathValue);

    return result;
}
// @lc code=end

