/*
 * @lc app=leetcode.cn id=51 lang=c
 *
 * [51] N »Êºó
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char** generateBoard(int* queens, int n);
bool isValid(int* queens, int row, int col);
void backtrack(int n, int row, int* queens, char*** result,
               int* returnSize, int** returnColumnSizes);

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    int maxSolutions = 400;
    char*** result = (char***)malloc(maxSolutions * sizeof(char**));
    *returnColumnSizes = (int*)malloc(maxSolutions * sizeof(int));

    int* queens = (int*)malloc(n * sizeof(int));
    backtrack(n, 0, queens, result, returnSize, returnColumnSizes);

    free(queens);

    result = (char***)realloc(result, (*returnSize) * sizeof(char**));
    *returnColumnSizes = (int*)realloc(*returnColumnSizes, (*returnSize) * sizeof(int));

    return result;
}

bool isValid(int* queens, int row, int col)
{
    for (int i = 0; i < row; ++i)
    {
        if (queens[i] == col || abs(queens[i] - col) == row - i)
        {
            return false;
        }
    }
    return true;
}

char** generateBoard(int* queens, int n)
{
    char** board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; ++i)
    {
        board[i] = (char*)malloc((n + 1) * sizeof(char));
        memset(board[i], '.', n);
        board[i][queens[i]] = 'Q';
        board[i][n] = '\0';
    }
    return board;
}

void backtrack(int n, int row, int* queens, char*** result,
               int* returnSize, int** returnColumnSizes)
{
    if (row == n)
    {
        result[*returnSize] = generateBoard(queens, n);
        (*returnColumnSizes)[*returnSize] = n;
        (*returnSize)++;
        return;
    }

    for (int col = 0; col < n; ++col)
    {
        if (isValid(queens, row, col))
        {
            queens[row] = col;
            backtrack(n, row + 1, queens, result, returnSize, returnColumnSizes);
        }
    }
}
// @lc code=end

