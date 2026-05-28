/*
 * @lc app=leetcode.cn id=65 lang=c
 *
 * [65] ÓÐÐ§Êý×Ö
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>

int getEindex(char* s);

bool isNumber(char* s)
{
    int sSize = strlen(s);
    if (sSize == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '.')) return false;
    if (sSize == 2 && (s[0] == '+' || s[0] == '-') && s[1] == '.') return false;

    int indexForE = getEindex(s);
    if (indexForE == 0 || indexForE == sSize - 1) return false;

    if (indexForE == -1)
    {
        int idx = (s[0] == '+' || s[0] == '-') ? 1 : 0;
        bool havePoint = false;
        while (idx < sSize)
        {
            if (s[idx] == '.')
            {
                if (havePoint) return false;
                havePoint = true;
            }
            else if ('0' <= s[idx] && s[idx] <= '9');
            else return false;

            idx++;
        }
    }
    else
    {
        if (indexForE == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '.')) return false;
        if (indexForE == 2 && (s[0] == '+' || s[0] == '-') && s[1] == '.') return false;
        if (indexForE == sSize - 2 && (s[sSize - 1] == '+' || s[sSize - 1] == '-')) return false;
        
        int leftIdx = (s[0] == '+' || s[0] == '-') ? 1 : 0;
        bool haveLeftPoint = false;
        while (leftIdx < indexForE)
        {
            if (s[leftIdx] == '.')
            {
                if (haveLeftPoint) return false;
                haveLeftPoint = true;
            }
            else if ('0' <= s[leftIdx] && s[leftIdx] <= '9');
            else return false;

            leftIdx++;
        }

        int rightIdx = (s[indexForE + 1] == '+' || s[indexForE + 1] == '-') ? indexForE + 2 : indexForE + 1;
        while (rightIdx < sSize)
        {
            if ('0' <= s[rightIdx] && s[rightIdx] <= '9');
            else return false;

            rightIdx++;
        }
    }

    return true;
}

int getEindex(char* s)
{
    int sSize = strlen(s);

    for (int idx = 0; idx < sSize; idx++)
    {
        if (s[idx] == 'e' || s[idx] == 'E') return idx;
    }

    return -1;
}
// @lc code=end

