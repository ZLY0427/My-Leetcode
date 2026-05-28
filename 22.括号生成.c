/*
 * @lc app=leetcode.cn id=22 lang=c
 *
 * [22] Éú³ÉÀ¨ºÅ
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

void getSize(int n, int* size, int left, int right);
void GenerateParentheses(char* tempstr, int n, int left, int right, int index, char** result, int* pos);

char** generateParenthesis(int n, int* returnSize)
{
    *returnSize = 0;

    getSize(n, returnSize, 0, 0);

    if (*returnSize == 0)
    {
        return NULL;
    }

    char** result = (char**)malloc(sizeof(char*) * *returnSize);
    if (result == NULL)
    {
        *returnSize = 0;
        return NULL;
    }

    int strlen = 2 * n + 1;
    for (int i = 0; i < *returnSize; i++)
    {
        result[i] = (char*)malloc(sizeof(char) * strlen);
        if (result[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            *returnSize = 0;
            return NULL;
        }
    }

    char tempstr[strlen];
    memset(tempstr, 0, sizeof(tempstr));
    int pos = 0;
    GenerateParentheses(tempstr, n, 0, 0, 0, result, &pos);

    return result;
}

void getSize(int n, int* size, int left, int right)
{
    if (left == n && right == n)
    {
        (*size)++;
        return;
    }

    if (left < n)
    {
        getSize(n, size, left + 1, right);
    }

    if (right < left)
    {
        getSize(n, size, left, right + 1);
    }
}

void GenerateParentheses(char* tempstr, int n, int left, int right, int index, char** result, int* pos)
{
    if (index == 2 * n)
    {
        tempstr[index] = '\0';
        strcpy(result[*pos], tempstr);
        (*pos)++;
        return;
    }
    if (left < n)
    {
        tempstr[index] = '(';
        GenerateParentheses(tempstr, n, left + 1, right, index + 1, result, pos);
    }
    if (right < left)
    {
        tempstr[index] = ')';
        GenerateParentheses(tempstr, n, left, right + 1, index + 1, result, pos);
    }
}
// @lc code=end

