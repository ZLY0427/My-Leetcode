/*
 * @lc app=leetcode.cn id=201 lang=c
 *
 * [201] 数字范围按位�?
 */

// @lc code=start
int rangeBitwiseAnd(int left, int right)
{
    int count = 0;
    while (left != right)
    {
        left >>= 1;
        right >>= 1;
        ++count;
    }
    return left << count;
}
// @lc code=end

