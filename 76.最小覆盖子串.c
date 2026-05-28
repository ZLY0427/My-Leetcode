/*
 * @lc app=leetcode.cn id=76 lang=c
 *
 * [76] ×îÐ¡¸²¸Ç×Ö´®
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int* PreProcessing(char* t);
bool is(int* tNum, int* sNum);

char* minWindow(char* s, char* t)
{
    char* null = (char*)malloc(sizeof(char));
    if (!null) return NULL;
    null[0] = '\0';

    int sSize = strlen(s), tSize = strlen(t);

    if (sSize < tSize) return null;

    int left = 0, right = 0;

    int* tNum = PreProcessing(t);
    int* sNum = (int*)calloc(128, sizeof(int));

    int minSize = sSize + 1, minleft = 0, minright = 0;

    while (right <= sSize && left <= right)
    {
        if (is(tNum, sNum))
        {
            if (right - left < minSize)
            {
                minleft = left;
                minright = right;
                minSize = right - left;
            }
            sNum[(int)s[left++]]--;
        }
        else
        {
            sNum[(int)s[right++]]++;
        }
    }

    if (minSize > sSize)
    {
        return null;
    }
    char* result = (char*)malloc(sizeof(char) * (minSize + 1));
    for (int i = minleft; i < minright; i++)
    {
        result[i - minleft] = s[i];
    }
    result[minSize] = '\0';

    return result;
}

int* PreProcessing(char* t)
{
    int size = strlen(t);

    int* result = (int*)calloc(128, sizeof(int));
    if (!result) return NULL;

    for (int i = 0; i < size; i++)
        result[(int)t[i]]++;

    return result;
}

bool is (int* tNum, int* sNum)
{
    for (int i = 0; i < 128; i++)
        if (sNum[i] < tNum[i]) return false;
    return true;
}
// @lc code=end

