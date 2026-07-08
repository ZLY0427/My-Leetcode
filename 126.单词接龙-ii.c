/*
 * @lc app=leetcode.cn id=126 lang=c
 *
 * [126] µ¥´Ê½ÓÁú II
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char*** findLadders(char* beginWord, char* endWord, char** wordList,
                    int wordListSize, int* returnSize, int** returnColumnSizes)
{
    int beginSize = strlen(beginWord);
    int endSize = strlen(endWord);

    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (beginSize != endSize || wordListSize <= 0) return NULL;

    char*** result = (char***)malloc(sizeof(char**));
    if (!result) return NULL;

    int* pathindex = (int*)malloc(sizeof(int) * wordListSize);
    pathindex[0] = 0;

    bool* is_use = (bool*)calloc(sizeof(bool), wordListSize);
}
// @lc code=end

