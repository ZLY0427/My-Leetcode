/*
 * @lc app=leetcode.cn id=130 lang=c
 *
 * [130] 被围绕的区域
 */

// @lc code=start
#include <stdbool.h>

void dfs(char** board, int row, int col, int i, int j, bool** visited);

void solve(char** board, int boardSize, int* boardColSize)
{
    int row = boardSize;
    int col = boardColSize[0];

    if (!board || row <= 0 || col <= 0) return;

    bool** visited = (bool**)malloc(sizeof(bool*) * row);
    for (int i = 0; i < row; ++i)
        visited[i] = (bool*)calloc(sizeof(bool), col);

    for (int i = 0; i < row; ++i)
    {
        if (board[i][0] == 'O') dfs(board, row, col, i, 0, visited);
        if (board[i][col - 1] == 'O') dfs(board, row, col, i, col - 1, visited);
    }

    for (int j = 0; j < col; ++j)
    {
        if (board[0][j] == 'O') dfs(board, row, col, 0, j, visited);
        if (board[row - 1][j] == 'O') dfs(board, row, col, row - 1, j, visited);
    }

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            if (!visited[i][j]) board[i][j] = 'X';

    free(visited);
}

void dfs(char** board, int row, int col, int i, int j, bool** visited)
{
    if (i < 0 || i >= row || j < 0 || j >= col || board[i][j] != 'O' || visited[i][j]) return;

    visited[i][j] = true;

    dfs(board, row, col, i - 1, j, visited);
    dfs(board, row, col, i + 1, j, visited);
    dfs(board, row, col, i, j - 1, visited);
    dfs(board, row, col, i, j + 1, visited);
}
// @lc code=end

