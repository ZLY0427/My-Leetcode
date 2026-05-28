/*
 * @lc app=leetcode.cn id=49 lang=c
 *
 * [49] ×ÖÄ¸ÒìÎ»´Ê·Ö×é
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* key;
    char** words;
    int count;
    int capacity;
} Group;

void sortString(char* str);

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    if (strs == NULL || strsSize == 0)
    {
        *returnSize = 0;
        return NULL;
    }

    Group* groups = (Group*)calloc(strsSize, sizeof(Group));
    int groupCount = 0;

    for (int i = 0; i < strsSize; i++)
    {
        char* copy = strdup(strs[i]);
        sortString(copy);

        int foundIndex = -1;
        for (int j = 0; j < groupCount; j++)
        {
            if (strcmp(groups[j].key, copy) == 0)
            {
                foundIndex = j;
                break;
            }
        }

        if (foundIndex == -1)
        {
            groups[groupCount].key = copy;
            groups[groupCount].capacity = 4;
            groups[groupCount].words = (char**)malloc(sizeof(char*) * groups[groupCount].capacity);
            groups[groupCount].count = 0;
            foundIndex = groupCount++;
        }
        else
        {
            free(copy);
        }

        if (groups[foundIndex].count >= groups[foundIndex].capacity)
        {
            groups[foundIndex].capacity *= 2;
            groups[foundIndex].words = (char**)realloc(groups[foundIndex].words,
                                                       sizeof(char*) * groups[foundIndex].capacity);
        }
        groups[foundIndex].words[groups[foundIndex].count++] = strs[i];
    }

    char*** result = (char***)malloc(sizeof(char**) * groupCount);
    *returnColumnSizes = (int*)malloc(sizeof(int) * groupCount);
    *returnSize = groupCount;

    for (int i = 0; i < groupCount; i++)
    {
        result[i] = groups[i].words;
        (*returnColumnSizes)[i] = groups[i].count;
        free(groups[i].key);
    }

    free(groups);
    return result;
}

void sortString(char* s)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (s[i] > s[j])
            {
                char tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
}

// @lc code=end

