/*
 * @lc app=leetcode.cn id=16 lang=c
 *
 * [16] 最接近的三数之和
 */

// @lc code=start
void Sort(int* arr, int size);
void Merge_Sort(int* arr, int left, int right, int* temp);

int threeSumClosest(int* nums, int numsSize, int target)
{
    if (numsSize < 3)
    {
        printf("错误输入, 请不要相信输出结果.\n");
        return 0;
    }

    Sort(nums, numsSize);
    
    int result = nums[0] + nums[1] + nums[2];
    int min_diff = abs(result - target);

    for (int i = 0; i < numsSize - 2; i++)
    {
        int left = i + 1;
        int right = numsSize - 1;

        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];
            int temp_diff = abs(sum - target);
            if (temp_diff < min_diff)
            {
                result = sum;
                min_diff = temp_diff;
                if (min_diff == 0)
                {
                    return result;
                }
            }
            if (sum > target)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
    }
    return result;
}

void Sort(int* arr, int size)
{
    int* temp = (int*)malloc(sizeof(int) * size);
    Merge_Sort(arr, 0, size - 1, temp);
    free(temp);
}

void Merge_Sort(int* arr, int left, int right, int* temp)
{
    if (left >= right)
    {
        return ;
    }
    int middle = (left + right) / 2;
    Merge_Sort (arr, left, middle, temp);
    Merge_Sort (arr, middle + 1, right, temp);

    int len_left = middle - left + 1;
    int len_right = right - middle;

    for (int i = 0; i < len_left; i++)
    {
        temp[left + i] = arr[left + i];
    }
    for (int j = 0; j < len_right; j++)
    {
        temp[middle + 1 + j] = arr[middle + 1 + j];
    }

    int i, j, k;

    for(i = 0, j = 0, k = left; (i < len_left) && (j < len_right); k++)
    {
        if (temp[left + i] < temp[middle + 1 + j])
        {
            arr[k] = temp[left + i];
            i++;
        }
        else
        {
            arr[k] = temp[middle + 1 + j];
            j++;
        }
    }

    while (i < len_left)
    {
        arr[k] = temp[left + i];
        i++;
        k++;
    }

    while (j < len_right)
    {
        arr[k] = temp[middle + 1 + j];
        j++;
        k++;
    }
}

// @lc code=end

