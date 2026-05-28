/*
 * @lc app=leetcode.cn id=36 lang=c
 *
 * [36] ÓÐÐ§Êý¶À
 */

// @lc code=start
#include <stdbool.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize)
{
    for (int i = 0; i < 9; i++)
    {
        bool seen[9] = {false};
        for (int j = 0; j < 9; j++)
        {
            if  (board[i][j] != '.')
            {
                int num = board[i][j] - '1';
                if (0 > num || num > 8) return false;
                if (seen[num]) return false;
                seen[num] = true;
            }
        }
    }

    for (int j = 0; j < 9; j++)
    {
        bool seen[9] = {false};
        for (int i = 0; i < 9; i++)
        {
            if (board[i][j] != '.')
            {
                int num = board[i][j] - '1';
                if (0 > num || num > 8) return false;
                if (seen[num]) return false;
                seen[num] = true;
            }
        }
    }

    for (int box = 0; box < 9; box++)
    {
        bool seen[9] = {false};
        int startRow = (box / 3) * 3;
        int startCol = (box % 3) * 3;

        for (int i = startRow; i < startRow + 3; i++)
        {
            for (int j = startCol; j < startCol + 3; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '1';
                    if (0 > num || num > 8) return false;
                    if (seen[num]) return false;
                    seen[num] = true;
                }
            }
        }
    }

    return true;
}
// @lc code=end

