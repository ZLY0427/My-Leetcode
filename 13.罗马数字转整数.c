/*
 * @lc app=leetcode.cn id=13 lang=c
 *
 * [13] 罗马数字转整数
 */

// @lc code=start
const int values[] = {1, 5, 10, 50, 100, 500, 1000};
const char* symbols[] = {"I", "V", "X", "L", "C", "D", "M"};

int getValue(char c);

int romanToInt(char* s)
{
    int len = strlen(s);
    int result = 0;
    for (int i = 0; i < len; i++)
    {
        int current = getValue(s[i]);
        int next = (i + 1 < len) ? getValue(s[i + 1]) : 0;
        if (current < next)
        {
            result -= current;
        }
        else
        {
            result += current;
        }
    }

    return result;
}

int getValue(char c)
{
    for (int i = 0; i < 7; i++)
    {
        if (symbols[i][0] == c)
        {
            return values[i];
        }
    }
    return 0;
}
// @lc code=end

