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

bool is_same_string(char* s1, char* s2);
bool is_one_word_different_string(char* s1, char* s2);
void back(char* endWord, char** wordList, int wordListSize,
          char*** result, int* returnSize, int** returnColumnSizes,
          int* pathindex, int pathSize, bool* is_use);

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

    back(endWord, wordList, wordListSize, result, returnSize,
         returnColumnSizes, pathindex, 1, is_use);
}

bool is_same_string(char* s1, char* s2)
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    if (l1 != l2) return false;
    for (int i = 0; i < l1; ++i) if (s1[i] != s2[i]) return false;
    return true;
}

bool is_one_word_different_string(char* s1, char* s2)
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    if (l1 != l2) return false;
    int different_word = 0;
    for (int i = 0; i < l1; ++i) if (s1[i] != s2[i]) ++different_word;
    return different_word == 1;
}

void back(char* endWord, char** wordList, int wordListSize,
          char*** result, int* returnSize, int** returnColumnSizes,
          int* pathindex, int pathSize, bool* is_use)
{
    char* nowWord = wordList[pathindex[pathSize - 1]];
    if (is_same_string(nowWord, endWord))
    {
        
    }

    for (int i = 0; i < wordListSize; ++i)
    {
        if (is_one_word_different_string(nowWord, wordList[i]) && !is_use[i])
        {
            is_use[i] = true;
            pathindex[pathSize] = i;
            back(endWord, wordList, wordListSize, result, returnSize,
                 returnColumnSizes, pathindex, pathSize + 1, is_use);
            
            is_use[i] = false;
        }
    }
}
// @lc code=end

