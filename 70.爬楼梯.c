/*
 * @lc app=leetcode.cn id=70 lang=c
 *
 * [70] ÅÀÂ¥Ìİ
 */

// @lc code=start
/*
int climbStairs(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else if (n == 2)
    {
        return 2;
    }

    int a = 1;
    int b = 2;
    int result = 0;

    for (int i = 3; i <= n; i++)
    {
        result = a + b;
        a = b;
        b = result;
    }
    return result;
}
*/

int climbStairs(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else if (n == 2)
    {
        return 2;
    }
    int result = 0;
    result += climbStairs(n - 1);
    result += climbStairs(n - 2);

    return result;
}
// @lc code=end

