/*
 * @lc app=leetcode.cn id=68 lang=c
 *
 * [68] 文本左右对齐
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

char** fullJustify(char** words, int wordsSize,
                   int maxWidth, int* returnSize)
{
    (*returnSize) = 0;
    char** result = (char**)malloc(sizeof(char*) * wordsSize);
    if (!result) return NULL;
    for (int indexForMalloc = 0; indexForMalloc < wordsSize; indexForMalloc++)
    {
        result[indexForMalloc] = (char*)malloc(sizeof(char) * (maxWidth + 1));
        if (!result[indexForMalloc])
        {
            for (int indexForFree = 0; indexForFree < indexForMalloc; indexForFree++)
                free(result[indexForFree]);
            free(result);
            return NULL;
        }
        result[indexForMalloc][maxWidth] = '\0';
    }

    int left = 0;
    while (left < wordsSize)
    {
        int right = left;
        int len = 0;

        while (right < wordsSize && len + strlen(words[right]) + (right - left) <= maxWidth)
        {
            len += strlen(words[right]);
            right++;
        }

        // left 到 right - 1 之间的索引均在本行
        int wordCount = right - left;
        int spacesNumber = maxWidth - len;

        if (right == wordsSize)
        {
            int nowlen = 0;
            for (int i = left; i < right; i++)
            {
                strcpy(result[(*returnSize)] + nowlen, words[i]);
                nowlen += strlen(words[i]);
                if (i < right - 1)
                {
                    result[(*returnSize)][nowlen++] = ' ';
                }
            }
            // 填充剩余空格
            while (nowlen < maxWidth)
            {
                result[(*returnSize)][nowlen++] = ' ';
            }
        }
        else if (wordCount == 1)
        {
            // 只有一个单词：左对齐，右边填充空格
            strcpy(result[(*returnSize)], words[left]);
            int len = strlen(words[left]);
            for (int i = len; i < maxWidth; i++)
            {
                result[(*returnSize)][i] = ' ';
            }
        }
        else {
            // 多个单词：左右对齐
            int spacesBetween = spacesNumber / (wordCount - 1);
            int extraSpaces = spacesNumber % (wordCount - 1);
            
            int nowlen = 0;
            for (int i = left; i < right; i++) {
                strcpy(result[(*returnSize)] + nowlen, words[i]);
                nowlen += strlen(words[i]);
                
                if (i < right - 1)
                {
                    // 添加空格
                    int spacesToAdd = spacesBetween + (i - left < extraSpaces ? 1 : 0);
                    for (int s = 0; s < spacesToAdd; s++)
                    {
                        result[(*returnSize)][nowlen++] = ' ';
                    }
                }
            }
        }

        (*returnSize)++;
        left = right;
    }

    for (int indexForFree = (*returnSize); indexForFree < wordsSize; indexForFree++)
        free(result[indexForFree]);
        
    return result;
}
// @lc code=end

