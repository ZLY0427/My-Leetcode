/*
 * @lc app=leetcode.cn id=85 lang=c
 *
 * [85] ×î´ó¾ØÐÎ
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

bool is_rect(char** matrix, int row, int col,
             int point1_row, int point1_col,
             int point2_row, int point2_col);

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
    if (!matrix || !matrixColSize || matrixSize <= 0) return 0;
    
    int col = matrixColSize[0];
    int row = matrixSize;

    int maxarea = 0;

    for (int point1_row = 0; point1_row < row; ++point1_row)
    {
        for (int point1_col = 0; point1_col < col; ++point1_col)
        {
            if (matrix[point1_row][point1_col] == '0') continue;
            for (int point2_row = point1_row; point2_row < row; ++point2_row)
            {
                if (matrix[point2_row][point1_col] == '0') continue;
                for (int point2_col = point1_col; point2_col < col; ++point2_col)
                {
                    if (matrix[point2_row][point2_col] == '0') break;
                    if (is_rect(matrix, row, col, point1_row, point1_col, point2_row, point2_col))
                    {
                        int area = (point2_row - point1_row + 1) * (point2_col - point1_col + 1);
                        maxarea = maxarea > area ? maxarea : area;
                    }
                    else break;
                }
            }
        }
    }

    return maxarea;
}
bool is_rect(char** matrix, int row, int col,
             int point1_row, int point1_col,
             int point2_row, int point2_col)
{
    if (point1_row < 0 || point1_col < 0 || point1_row >= row || point1_col >= col ||
        point2_row < 0 || point2_col < 0 || point2_row >= row || point2_col >= col) return false;

    for (int i = point1_row; i <= point2_row; ++i)
        for (int j = point1_col; j <= point2_col; ++j)
            if (matrix[i][j] == '0') return false;

    return true;
}
// @lc code=end

