/*
 * @lc app=leetcode.cn id=191 lang=c
 *
 * [191] ä½?1çš„ä¸ªæ•?
 */

// @lc code=start
int hammingWeight(int n)
{
    if (n < 0) return -1;
    else if (n == 0) return 0;
    int result = 0;
    while (n)
    {
        result += n & 1;
        n >>= 1;
    }

    return result;
}
// @lc code=end

