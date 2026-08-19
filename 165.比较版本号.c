/*
 * @lc app=leetcode.cn id=165 lang=c
 *
 * [165] 比较版本�?
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>

int compareSeg(char* s1, int left1, int right1,
                   char* s2, int left2, int right2);

int compareVersion(char* version1, char* version2)
{
    int len1 = strlen(version1);
    int len2 = strlen(version2);

    int left1 = 0, right1 = 0;
    int left2 = 0, right2 = 0;

    while (right1 < len1 && right2 < len2)
    {
        left1 = right1;
        left2 = right2;

        while (right1 < len1 && version1[right1] != '.') ++right1;
        while (right2 < len2 && version2[right2] != '.') ++right2;

        int result = compareSeg(version1, left1, right1 - 1, version2, left2, right2 - 1);

        if (result == 1) return 1;
        else if (result == -1) return -1;

        ++right1;
        ++right2;
    }

    while (right1 < len1)
    {
        left1 = right1;

        while (right1 < len1 && version1[right1] != '.') ++right1;

        if (compareSeg(version1, left1, right1 - 1, "0", 0, 0) == 1) return 1;

        ++right1;
    }

    while (right2 < len2)
    {
        left2 = right2;

        while (right2 < len2 && version2[right2] != '.') ++right2;

        if (compareSeg(version2, left2, right2 - 1, "0", 0, 0) == 1) return -1;

        ++right2;
    }

    return 0;
}

int compareSeg(char* s1, int left1, int right1,
                   char* s2, int left2, int right2)
{
    while(left1 <= right1 && s1[left1] == '0') ++left1;
    while(left2 <= right2 && s2[left2] == '0') ++left2;

    int len1 = right1 - left1 + 1;
    int len2 = right2 - left2 + 1;

    if(len1 > len2) return 1;
    if(len1 < len2) return -1;

    while(left1 <= right1)
    {
        if(s1[left1] > s2[left2]) return 1;
        if(s1[left1] < s2[left2]) return -1;
        ++left1;
        ++left2;
    }
    return 0;
}
// @lc code=end

