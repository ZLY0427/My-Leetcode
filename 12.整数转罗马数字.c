/*
 * @lc app=leetcode.cn id=12 lang=c
 *
 * [12] 整数转罗马数字
 */

// @lc code=start
#include <stdlib.h>

#define MAX_SIZE 16

const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
const char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};


char* intToRoman(int num)
{
    char* result = (char*)malloc(sizeof(char) * MAX_SIZE);
    if (!result) return NULL;
    result[0] = '\0';

    for (int i = 0; i < 13; i++)
    {
        while (num >= values[i])
        {
            strcat(result, symbols[i]);
            num -= values[i];
        }
    }
    return result;
}

// @lc code=end

