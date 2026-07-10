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
void bfs(char* nowWord, int nowindex, char* endWord,
         char** wordList, int wordListSize,
         char*** result, int* resCap, int* returnSize, int** returnColumnSizes,
         int* path, int pathSize, bool* useWord, char* beginWord);

char*** findLadders(char* beginWord, char* endWord, char** wordList,
                    int wordListSize, int* returnSize, int** returnColumnSizes)
{
    int beginSize = strlen(beginWord);
    int endSize = strlen(endWord);

    *returnSize = 0;
    *returnColumnSizes = NULL;

    if (beginSize != endSize || wordListSize <= 0) return NULL;

    int resCap = 4;
    char*** result = (char***)malloc(sizeof(char**) * resCap);
    if (!result) return NULL;

    int* path = (int*)malloc(sizeof(int) * (wordListSize + 1));
    path[0] = -1;

    bool* useWord = (bool*)calloc(wordListSize, sizeof(bool));

    bfs(beginWord, -1, endWord, wordList, wordListSize,
        result, &resCap, returnSize, returnColumnSizes,
        path, 1, useWord, beginWord);

    free(path);
    free(useWord);
    return result;
}

void bfs(char* nowWord, int nowindex, char* endWord,
         char** wordList, int wordListSize,
         char*** result, int* resCap, int* returnSize, int** returnColumnSizes,
         int* path, int pathSize, bool* useWord, char* beginWord)
{
    if (strcmp(nowWord, endWord) == 0)
    {
        if (*returnSize >= *resCap)
        {
            *resCap *= 2;
            *result = (char**)realloc(*result, sizeof(char**) * (*resCap));
        }
        char** oneAns = (char**)malloc(sizeof(char*) * pathSize);
        oneAns[0] = (char*)malloc(strlen(beginWord) + 1);
        strcpy(oneAns[0], beginWord);
        for(int i = 1; i < pathSize; ++i)
        {
            int idx = path[i];
            oneAns[i] = (char*)malloc(strlen(wordList[idx]) + 1);
            strcpy(oneAns[i], wordList[idx]);
        }
        result[*returnSize] = oneAns;

        (*returnColumnSizes) = (int*)realloc(*returnColumnSizes, sizeof(int) * (*returnSize + 1));
        (*returnColumnSizes)[*returnSize] = pathSize;
        (*returnSize) += 1;
        return ;
    }

    for (int i = 0; i < wordListSize; ++i)
    {
        if (useWord[i]) continue;

        if (isNextWord(nowWord, wordList[i]))
        {
            useWord[i] = true;
            path[pathSize] = i;
            bfs(wordList[i], i, endWord, wordList, wordListSize,
                result, resCap, returnSize, returnColumnSizes,
                path, pathSize + 1, useWord, beginWord);
            useWord[i] = false;
        }
    }
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

