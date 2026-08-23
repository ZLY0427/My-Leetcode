/*
 * @lc app=leetcode.cn id=172 lang=c
 *
 * [172] 阶乘后的�?
 */

// @lc code=start
int trailingZeroes(int n)
{
    int count = 0;
    for (int i = 5; i <= n; ++i)
    {
        int temp = i;
        while (temp % 5 != 0)
        {
            if (temp % 5 == 0)
            {
                ++count;
                temp /= 5;
            }
            else
                break;
        }
    }

    return count;
}
// @lc code=end

