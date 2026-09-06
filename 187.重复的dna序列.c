/*
 * @lc app=leetcode.cn id=187 lang=c
 *
 * [187] 閲嶅鐨凞NA搴忓垪
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct HashNode {
    char* str;
    int isAdd;
    struct HashNode* next;
};

struct Hash {
    struct HashNode* hashTable;
    int hashSize;
};

bool isSameString(char* str1, char* str2);
struct Hash* create_Hash(int hashSize);
int getHashIndex(char* str, struct Hash* hash);
int insert_Hash(char* str, struct Hash* hash);
void free_Hash(struct Hash* hash);

char** findRepeatedDnaSequences(char* s, int* returnSize)
{
    if (!s) return NULL;
    *returnSize = 0;
    int sSize = strlen(s);
    if (sSize < 10) return NULL;

    struct Hash* hash = create_Hash(sSize / 2 + 1);
    if (!hash) return NULL;

    char** temp_result = (char**)malloc(sizeof(char*) * sSize);
    if (!temp_result)
    {
        free_Hash(hash);
        return NULL;
    }
    int resultIndex = 0;

    int leftIndex = 0, rightIndex = 9;
    while (rightIndex < sSize)
    {
        char* str = (char*)malloc(sizeof(char) * 11);
        for (int i = leftIndex; i <= rightIndex; ++i)
            str[i - leftIndex] = s[i];
        str[10] = '\0';
        
        int insertResult = insert_Hash(str, hash);
        if (insertResult == 0)
            temp_result[resultIndex++] = str;
        else if (insertResult == -1)
        {
            free_Hash(hash);
            free(temp_result);
            return NULL;
        }

        leftIndex++;
        rightIndex++;
    }

    char** result = (char**)realloc(temp_result, sizeof(char*) * resultIndex);
    *returnSize = resultIndex;

    free_Hash(hash);
    return result;
}

bool isSameString(char* str1, char* str2)
{
    return strcmp(str1, str2) == 0;
}

struct Hash* create_Hash(int hashSize)
{
    if (hashSize <= 0) return NULL;
    struct Hash* hash = (struct Hash*)malloc(sizeof(struct Hash));
    if (!hash) return NULL;

    hash -> hashSize = hashSize;
    hash -> hashTable = (struct HashNode*)malloc(sizeof(struct HashNode) * hashSize);
    if (!hash -> hashTable)
    {
        free(hash);
        return NULL;
    }
    for (int i = 0; i < hashSize; ++i)
    {
        hash -> hashTable[i].str =  NULL;
        hash -> hashTable[i].next = NULL;
        hash -> hashTable[i].isAdd = 1;
    }
    return hash;
}

int getHashIndex(char* str, struct Hash* hash)
{
    if (!hash || !str) return -1;
    int hashIndex = 0;
    for (int i = 0; i < 10; i++)
    {
        int val;
        switch(str[i])
        {
            case 'A': val = 0; break;
            case 'C': val = 1; break;
            case 'G': val = 2; break;
            case 'T': val = 3; break;
            default: val =0;
        }
        hashIndex = hashIndex * 4 + val;
    }
    hashIndex %= hash -> hashSize;
    return hashIndex;
}

// 返回：
// 0：重复，需要加入结果数组
// 1：首次 / 已经添加过
// -1：内存失败
int insert_Hash(char* str, struct Hash* hash)
{
    if (!hash || !str) return -1;
    int hashIndex = getHashIndex(str, hash);
    if (hashIndex < 0) return -1;

    struct HashNode* node = hash -> hashTable[hashIndex].next;
    while (node)
    {
        bool isSame = isSameString(node->str, str);
        if (isSame)
        {
            if (!node -> isAdd)
            {
                node -> isAdd = 1;
                return 0;
            }
            else return 1;
        }
        node = node -> next;
    }
    node = (struct HashNode*)malloc(sizeof(struct HashNode));
    if (!node) return -1;
    node -> str = str;
    node -> isAdd = 0;
    node -> next = hash -> hashTable[hashIndex].next;
    hash -> hashTable[hashIndex].next = node;

    return 1;
}

void free_Hash(struct Hash* hash)
{
    if (!hash) return ;
    for (int i = 0; i < hash -> hashSize; ++i)
    {
        struct HashNode* node = hash -> hashTable[i].next;
        while (node)
        {
            struct HashNode* temp = node;
            node = node -> next;
            if (temp -> isAdd == 0) free(temp -> str);
            free(temp);
        }
    }
    free(hash -> hashTable);
    free(hash);
}
// @lc code=end

