/*
 * @lc app=leetcode.cn id=120 lang=c
 *
 * [120] 三角形最小路径和
 */

// @lc code=start
#include <stdlib.h>

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize)
{
    if (!triangle) return 0;

    int** copy = (int**)malloc(sizeof(int*) * triangleSize);
    for (int i = 0; i < triangleSize; ++i)
    {
        copy[i] = (int*)malloc(sizeof(int) * triangleColSize[i]);
        memcpy(copy[i], triangle[i], sizeof(int) * triangleColSize[i]);
    }

    for (int i = triangleSize - 2; i >= 0; --i)
        for (int j = 0; j < triangleColSize[i]; ++j)
            copy[i][j] += (copy[i + 1][j] < copy[i + 1][j + 1]) ? copy[i + 1][j] : copy[i + 1][j + 1];

    int result = copy[0][0];
    for (int i = 1; i < triangleColSize[0]; ++i)
        free(copy[i]);
    free(copy);

    return result;
}
// @lc code=end

