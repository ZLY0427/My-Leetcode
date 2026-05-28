/*
 * @lc app=leetcode.cn id=52 lang=c
 *
 * [52] N »Êºó II
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

void back(int n, int index, bool* row, bool* left, bool* right, int* result);

int totalNQueens(int n)
{
    if(n <= 0) return -1;
    else if (n == 1) return 1;
    else if (n <= 3) return 0;

    bool* row = (bool*)calloc(n, sizeof(bool));
    bool* left = (bool*)calloc(2 * n - 1, sizeof(bool));
    bool* right = (bool*)calloc(2 * n - 1, sizeof(bool));
    if (!row || !left || !right)
    {
        free(row);
        free(left);
        free(right);
        return -1;
    }

    int result = 0;
    back(n, 0, row, left, right, &result);

    free(row);
    free(left);
    free(right);
    return result;
}

void back(int n, int index, bool* row, bool* left, bool* right, int* result)
{
    if (index == n)
    {
        (*result)++;
        return ;
    }

    for (int i = 0; i < n; ++i)
    {
        if (row[i] || left[index + i] || right[index - i + n - 1]) continue;
        row[i] = left[index + i] = right[index - i + n - 1] = true;
        back(n, index + 1, row, left, right, result);
        row[i] = left[index + i] = right[index - i + n - 1] = false;
    }
}
// @lc code=end

