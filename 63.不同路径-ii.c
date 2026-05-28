/*
 * @lc app=leetcode.cn id=63 lang=c
 *
 * [63] ²»Í¬Â·¾¶ II
 */

// @lc code=start
#include <stdlib.h>
/*
    +----------------------------->n/x
    |
    |
    |
    |
    |
    |
    |
    V
    m/y
    m * n
*/
/*
void getCountPath(int** obstacleGrid, int m, int n,
                  int x, int y, int* result);

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
                             int* obstacleGridColSize)
{
    if (obstacleGrid[obstacleGridSize - 1][obstacleGridColSize[0] - 1]) return 0;
    int result = 0;

    getCountPath(obstacleGrid, obstacleGridSize, obstacleGridColSize[0], 0, 0, &result);

    return result;
}

void getCountPath(int** obstacleGrid, int m, int n,
                  int x, int y, int* result)
{
    if (y == m - 1 && x == n - 1)
    {
        (*result)++;
        return ;
    }

    if (y >= m || x >= n || y < 0 || x < 0 || obstacleGrid[y][x] == 1) return ;

    getCountPath(obstacleGrid, m, n, x + 1, y, result);
    getCountPath(obstacleGrid, m, n, x, y + 1, result);
}
*/

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
                             int* obstacleGridColSize)
{
    int m = obstacleGridSize;
    int n = obstacleGridColSize[0];

    if (m <= 0 || n <= 0) return -2;

    int** count = (int**)malloc(sizeof(int*) * m);
    if (!count) return -1;

    for (int indexForMalloc = 0; indexForMalloc < m; indexForMalloc++)
    {
        count[indexForMalloc] = (int*)malloc(sizeof(int) * n);
        if (!count[indexForMalloc])
        {
            for (int indexForFree = 0; indexForFree < indexForMalloc; indexForFree++)
                free(count[indexForFree]);
            
            free(count);

            return -1;
        }
    }

    count[0][0] = obstacleGrid[0][0] ? 0 : 1;
    int idx = 1;
    while (idx < m)
    {
        count[idx][0] = obstacleGrid[idx][0] ? 0 : count[idx - 1][0];
        idx++;
    }
    idx = 1;
    while (idx < n)
    {
        count[0][idx] = obstacleGrid[0][idx] ? 0 : count[0][idx - 1];
        idx++;
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            count[i][j] = obstacleGrid[i][j] ? 0 : count[i - 1][j] + count[i][j - 1];
        }
    }

    int result = count[m - 1][n - 1];

    for (int indexForFree = 0; indexForFree < m; indexForFree++)
        free(count[indexForFree]);
            
    free(count);

    return result;
}
// @lc code=end

