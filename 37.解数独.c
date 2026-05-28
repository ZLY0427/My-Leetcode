/*
 * @lc app=leetcode.cn id=37 lang=c
 *
 * [37] 解数独
 */

// @lc code=start
#include <stdbool.h>

void backtrack(char** board, bool row[9][10], bool col[9][10],
               bool box[9][10], int i, int j, bool* solved);

void solveSudoku(char** board, int boardSize, int* boardColSize)
{
    // 用来快速判断当前行/列/九宫格是否使用数字
    // 例如 row[0][1] 为 true 表示索引为 0 行已经填写数字 1
    // 例如 col[8][5] 为 true 表示索引为 8 行已经填写数字 5
    bool row[9][10] = {false};
    bool col[9][10] = {false};
    bool box[9][10] = {false};

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                int d = board[i][j] - '0';   // 已经填写的数字
                int box_idx = (i / 3) * 3 + (j / 3);   // 九宫格的编号
                /*
                    九宫格的编号依次为:
                    0 | 1 | 2
                    --+---+--
                    3 | 4 | 5
                    --+---+--
                    6 | 7 | 8
                */
                row[i][d] = true;
                col[j][d] = true;
                box[box_idx][d] = true;
            }
        }
    }

    bool solved = false;   // 该变量用来快速退出调用栈
    backtrack(board, row, col, box, 0, 0, &solved);
}

void backtrack(char** board, bool row[9][10], bool col[9][10],
               bool box[9][10], int i, int j, bool* solved)
{
    if (i == 9)   // 如果 i 为 9 则表示 0 ~ 8 行均已填满, 退出递归
    {
        *solved = true;
        return;
    }

    int next_i = j == 8 ? i + 1 : i;   // 如果 j 为 8 表示本行已遍历完, 则 i 需增大
    int next_j = (j + 1) % 9;   // 保证 j 不会超过范围

    if (board[i][j] != '.')   // 如果不可以修改, 则直接访问下一坐标点
    {
        backtrack(board, row, col, box, next_i, next_j, solved);
    }
    else   // 如果可以需改, 进行
    {
        int box_idx = (i / 3) * 3 + (j / 3);   // 先确认九宫格编号
        for (int d = 1; d <= 9; d++)   // 添加数字从 1 ~ 9 依次尝试
        {
            if (!row[i][d] && !col[j][d] && !box[box_idx][d])   // 该数字并未出现在 i, j 的同一行、同一列和同一九宫格
            {
                board[i][j] = '0' + d;   // 数字正确, 添加
                row[i][d] = true;
                col[j][d] = true;
                box[box_idx][d] = true;
                // 更改 row, col, box 三个状态表

                // 以当前添加的数字作为正确数字, 尝试后续其他数字的添加
                backtrack(board, row, col, box, next_i, next_j, solved);

                if (*solved) return;   // 若 solved 为 true 表示当前数字正确, 且该数独以填满, 则直接退出程序

                // 若 solved 为 false 表示当前数字不正确
                board[i][j] = '.';   // 将该坐标下的值更改为可更改状态
                row[i][d] = false;
                col[j][d] = false;
                box[box_idx][d] = false;
                // 还原三个状态表
            }
        }
        // 若程序进行到这里, 表示在 i, j 之前的位置有数字填错了
        // 需要回溯进行更改
    }
}
// @lc code=end

