/*
 * @lc app=leetcode.cn id=62 lang=c
 *
 * [62] 不同路径
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

// 思路没问题, 时间复杂度为O(pow(2, m * n)), 会运行超时
/*
void getCountPath(int m, int n, int x, int y, int* result);

int uniquePaths(int m, int n)
{
    int result = 0;

    getCountPath(m, n, 0, 0, &result);
    
    return result;
}

void getCountPath(int m, int n, int x, int y, int* result)
{
    if (x == n - 1 && y == m - 1)
    {
        (*result)++;
        return ;
    }
    else if (x >= n || y >= m || x < 0 || y < 0) return ;

    getCountPath(m, n, x + 1, y, result);
    getCountPath(m, n, x, y + 1, result);
}
*/

int uniquePaths(int m, int n)
{
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

    for (int i = 0; i < m; i++) count[i][0] = 1;
    for (int i = 0; i < n; i++) count[0][i] = 1;

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            count[i][j] = count[i - 1][j] + count[i][j - 1];
        }
    }

    int result = count[m - 1][n - 1];

    for (int indexForFree = 0; indexForFree < m; indexForFree++)
        free(count[indexForFree]);
            
    free(count);

    return result;
}
// @lc code=end

