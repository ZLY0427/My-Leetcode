/*
 * @lc app=leetcode.cn id=69 lang=c
 *
 * [69] x 的平方根
 */

// @lc code=start
int mySqrt(int x)
{
    if (x == 0)
    {
        return 0;
    }
    int left = 1;
    int right = x;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int div = x / mid;

        if (mid == div)
        {
            return mid;
        }
        else if (mid < div)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return right;
}
// @lc code=end

