/*
 * @lc app=leetcode.cn id=93 lang=c
 *
 * [93] ∏¥‘≠ IP µÿ÷∑
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_RES 1024

bool isValid(char *seg);

char** restoreIpAddresses(char* s, int* returnSize)
{
    *returnSize = 0;
    char** res = (char**)malloc(sizeof(char*) * MAX_RES);
    int n = strlen(s);

    for (int i = 1; i <= 3 && i < n; i++)
    {
        for (int j = i + 1; j <= i + 3 && j < n; j++)
        {
            for (int k = j + 1; k <= j + 3 && k < n; k++)
            {
                int len4 = n - k;
                if (len4 < 1 || len4 > 3)
                    continue;

                char s1[4], s2[4], s3[4], s4[4];
                strncpy(s1, s, i); s1[i] = '\0';
                strncpy(s2, s + i, j - i); s2[j - i] = '\0';
                strncpy(s3, s + j, k - j); s3[k - j] = '\0';
                strncpy(s4, s + k, len4); s4[len4] = '\0';

                if (isValid(s1) && isValid(s2) && isValid(s3) && isValid(s4))
                {
                    char *ip = (char*)malloc(n + 4);
                    sprintf(ip, "%s.%s.%s.%s", s1, s2, s3, s4);
                    res[(*returnSize)++] = ip;
                }
            }
        }
    }
    return res;
}

bool isValid(char *seg)
{
    int len = strlen(seg);
    if (len == 0 || len > 3) return false;
    if (len > 1 && seg[0] == '0') return false;
    int num = 0;
    for (int i = 0; i < len; i++) 
        num = num * 10 + seg[i] - '0';
    return num <= 255;
}
// @lc code=end