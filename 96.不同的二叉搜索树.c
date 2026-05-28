/*
 * @lc app=leetcode.cn id=96 lang=c
 *
 * [96] 不同的二叉搜索树
 */

// @lc code=start
int getTreeCount(int start, int end);

int numTrees(int n)
{
    return getTreeCount(1, n);
}

int getTreeCount(int start, int end)
{
    if (start > end) return 1;

    int result = 0;
    for (int i = start; i <= end; i++)
    {
        int leftSize = getTreeCount(start, i - 1);
        int rightSize = getTreeCount(i + 1, end);

        result = result + leftSize * rightSize;
    }

    return result;
}
// @lc code=end

