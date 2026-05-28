/*
 * @lc app=leetcode.cn id=79 lang=c
 *
 * [79] µ¥´ÊËÑË÷
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool dfs(char** board, int boardSize, int boardCol, int i, int j, char* word, int index);

bool exist(char** board, int boardSize, int* boardColSize, char* word)
{
    if (boardSize == 0 || boardColSize[0] == 0) return false;
    if (word[0] == '\0') return true;

    int m = boardSize;
    int n = boardColSize[0];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == word[0] && dfs(board, m, n, i, j, word, 0))
                return true;
        }
    }

    return false;
}

bool dfs(char** board, int boardSize, int boardCol, int i, int j, char* word, int index)
{
    if (word[index] == '\0') return true;

    if (i < 0 || i >= boardSize || j < 0 || j >= boardCol ||  board[i][j] != word[index])
        return false;

    char tmp = board[i][j];
    board[i][j] = '\0';

    bool found = dfs(board, boardSize, boardCol, i - 1, j, word, index + 1)
              || dfs(board, boardSize, boardCol, i + 1, j, word, index + 1)
              || dfs(board, boardSize, boardCol, i, j - 1, word, index + 1)
              || dfs(board, boardSize, boardCol, i, j + 1, word, index + 1);

    board[i][j] = tmp;

    return found;
}
// @lc code=end