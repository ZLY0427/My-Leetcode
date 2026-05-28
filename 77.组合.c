/*
 * @lc app=leetcode.cn id=77 lang=c
 *
 * [77] ×éºÏ
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

void back(int n, int k, int nowData, int nowDeep, int* path,
          int indexData, int** result, int* index);
int comb(int n, int k);

int** combine(int n, int k, int* returnSize, int** returnColumnSizes)
{
    (*returnSize) = comb(n, k);
    if ((*returnSize) == 0)
    {
        *returnColumnSizes = NULL;
        return NULL;
    }

    int** result = (int**)malloc(sizeof(int*) * (*returnSize));
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    if (!result || !(*returnColumnSizes))
    {
        free(result);
        return NULL;
    }
    for (int indexMalloc = 0; indexMalloc < (*returnSize); indexMalloc++)
    {
        result[indexMalloc] = (int*)malloc(sizeof(int) * k);
        (*returnColumnSizes)[indexMalloc] = k;
        if (!result[indexMalloc])
        {
            for (int indexFree = 0; indexFree < indexMalloc; indexFree++)
                free(result[indexFree]);
            free(result);
            return NULL;
        }
    }

    int* index = (int*)malloc(sizeof(int));
    *index = 0;

    int* path = (int*)malloc(sizeof(int) * k);
    for (int i = 1; i <= n; i++)
    {
        back(n, k, i, 0, path, 0, result, index);
    }
    return result;
}

void back(int n, int k, int nowData, int nowDeep, int* path,
          int indexData, int** result, int* index)
{
    if (nowData <= n)
    {
        path[indexData] = nowData;
        if (nowDeep + 1 == k)
        {
            for (int i = 0; i < k; i++)
            {
                result[*index][i] = path[i];
            }
            (*index)++;
            return ;
        }
        for (int i = nowData + 1; i <= n; i++)
        {
            back(n, k, i, nowDeep + 1, path, indexData + 1, result, index);
        }
    }
}

int comb(int n, int k)
{
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    if (k > n - k) k = n - k;

    int result = 1;
    for (int i = 1; i <= k; i++)
    {
        result = result * (n - k + i) / i;
    }
    return result;
}
// @lc code=end

