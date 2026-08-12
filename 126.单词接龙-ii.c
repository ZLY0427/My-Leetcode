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

bool isNextWord(char* nowWord, char* nextWord);

char*** findLadders(char* beginWord, char* endWord, char** wordList,
                    int wordListSize, int* returnSize, int** returnColumnSizes)
{
    
}

bool isNextWord(char* a, char* b)
{
    int len = strlen(a);
    int diff = 0;
    for (int i = 0; i < len; ++i)
    {
        if (a[i] != b[i]) diff++;
        if (diff > 1) return false;
    }
    return diff == 1;
}
// @lc code=end

