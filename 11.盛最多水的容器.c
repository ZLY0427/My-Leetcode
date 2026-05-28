/*
 * @lc app=leetcode.cn id=11 lang=c
 *
 * [11] 盛水最多的容器
 */

// @lc code=start
int maxArea(int* height, int heightSize)
{
    int maxArea = 0;
    int left = 0;
    int right = heightSize - 1;
    while (left < right)
    {
        int width = right - left;
        int min_height = (height[left] > height[right]) ? height[right] : height[left];
        int area = width * min_height;
        if (maxArea < area)
        {
            maxArea = area;
        }
        if (height[left] < height[right])
        {
            left++;
        }
        else
        {
            right--;
        }
    }

    return maxArea;
}

// @lc code=end

