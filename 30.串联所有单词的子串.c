/*
 * @lc app=leetcode.cn id=30 lang=c
 *
 * [30] 串联所有单词的字符串
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct HashNode{
    int count;
    int staticCount;
    char* str;
    struct HashNode* next;
};

int getHash(char* str, int hashSize, int length);
struct HashNode* findNode(struct HashNode** hashList, int hashSize, char* str, int wordSize);
void addToHash(struct HashNode** hashList, int hashSize, char* str);
void freeHash(struct HashNode** hashList, int hashSize);
void resetCounts(struct HashNode** hashList, int hashSize);
bool strEqual(char* s, int start, int L, char* word);
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize)
{
    *returnSize = 0;
    if (wordsSize == 0 || s == NULL || words == NULL) return NULL;

    int wordSize = strlen(words[0]);
    int totalLen = wordSize * wordsSize;
    int sSize = strlen(s);
    if (sSize < totalLen) return NULL;

    const int hashSize = 1009;
    struct HashNode** hashList = (struct HashNode**)calloc(hashSize, sizeof(struct HashNode*));
    if (!hashList) return NULL;
    for (int i = 0; i < wordsSize; i++)
        addToHash(hashList, hashSize, words[i]);

    int* result = (int*)malloc(sizeof(int) * sSize);
    if (!result)
    {
        freeHash(hashList, hashSize);
        return NULL;
    }
    for (int start = 0; start < wordSize; start++)
    {
        resetCounts(hashList, hashSize);
        int left = start;
        int invalid = 0;
        for (int right = start; right <= sSize - wordSize; right += wordSize)
        {
            char* curWord = s + right;
            struct HashNode* node = findNode(hashList, hashSize, curWord, wordSize);
            if (node)
            {
                node -> count--;
                if (node -> count == -1)
                    invalid++;
            }
            else
            {
                invalid++;
            }
            while (right - left + wordSize > totalLen)
            {
                char* leftWord = s + left;
                struct HashNode* leftNode = findNode(hashList, hashSize, leftWord, wordSize);
                if (leftNode)
                {
                    if (leftNode -> count == -1)
                        invalid--;
                    leftNode -> count++;
                }
                else
                {
                    invalid--;
                }
                left += wordSize;
            }
            if (right - left + wordSize == totalLen && invalid == 0)
            {
                result[(*returnSize)++] = left;
            }
        }
    }
    result = (int*)realloc(result, sizeof(int) * (*returnSize));
    freeHash(hashList, hashSize);
    return result;
}

int getHash(char* str, int hashSize, int length)
{
    int hash = 0;
    for (int i = 0; i < length; i++)
        hash = (hash * 31 + str[i]) % hashSize;
    return (hash + hashSize) % hashSize;
}

struct HashNode* findNode(struct HashNode** hashList, int hashSize, char* str, int wordSize)
{
    int hashVal = getHash(str, hashSize, wordSize);
    struct HashNode* cur = hashList[hashVal];
    while (cur)
    {
        if (strEqual(str, 0, wordSize, cur -> str))
            return cur;
        cur = cur -> next;
    }
    return NULL;
}

void addToHash(struct HashNode** hashList, int hashSize, char* str)
{
    int len = strlen(str);
    int hashVal = getHash(str, hashSize, len);
    struct HashNode* node = findNode(hashList, hashSize, str, len);
    if (node)
    {
        node -> staticCount++;
        return;
    }
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode -> str = strdup(str);
    newNode -> count = 1;
    newNode -> staticCount = 1;
    newNode -> next = hashList[hashVal];
    hashList[hashVal] = newNode;
}

void freeHash(struct HashNode** hashList, int hashSize)
{
    for (int i = 0; i < hashSize; i++)
    {
        struct HashNode* cur = hashList[i];
        while (cur)
        {
            struct HashNode* temp = cur;
            cur = cur -> next;
            free(temp -> str);
            free(temp);
        }
    }
    free(hashList);
}

void resetCounts(struct HashNode** hashList, int hashSize)
{
    for (int i = 0; i < hashSize; i++)
    {
        struct HashNode* cur = hashList[i];
        while (cur)
        {
            cur -> count = cur -> staticCount;
            cur = cur -> next;
        }
    }
}

bool strEqual(char* s, int start, int L, char* word)
{
    for (int i = 0; i < L; i++)
    {
        if (s[start + i] != word[i]) return false;
    }
    return true;
}
// @lc code=end

