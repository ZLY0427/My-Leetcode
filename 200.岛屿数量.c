/*
 * @lc app=leetcode.cn id=200 lang=c
 *
 * [200] 岛屿数量
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

void change_state(char** grid, bool** visited, int row, int col,
                  int index_row, int index_col);

int numIslands(char** grid, int gridSize, int* gridColSize)
{
    if (!grid || gridSize <= 0 || !gridColSize || gridColSize[0] <= 0) return -1;
    int island_count = 0;

    int row = gridSize;
    int col = gridColSize[0];

    bool** visited = (bool**)malloc(sizeof(bool*) * row);
    if (!visited) return -2;

    for (int i = 0; i < row; ++i)
    {
        visited[i] = (bool*)calloc(col, sizeof(bool));
        if (!visited[i])
        {
            for (int j = 0; j < i; ++j)
                free(visited[j]);
            free(visited);
            return -2;
        }
    }

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (visited[i][j]) continue;

            if (grid[i][j] == '1')
            {
                ++island_count;
                change_state(grid, visited, row, col, i, j);
            }
        }
    }

    for (int i = 0; i < row; ++i)
        free(visited[i]);
    free(visited);

    return island_count;
}

void change_state(char** grid, bool** visited, int row, int col,
                  int index_row, int index_col)
{
    if (index_row < 0 || index_row >= row || index_col < 0 || index_col >= col) return ;
    if (visited[index_row][index_col] || grid[index_row][index_col] == '0') return ;

    visited[index_row][index_col] = true;
    change_state(grid, visited, row, col, index_row - 1, index_col);
    change_state(grid, visited, row, col, index_row + 1, index_col);
    change_state(grid, visited, row, col, index_row, index_col - 1);
    change_state(grid, visited, row, col, index_row, index_col + 1);
}
// @lc code=end

