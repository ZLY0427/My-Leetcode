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
    int key;
    int count;
    bool added;
    struct HashNode* next;
};

struct HashTable {
    struct HashNode** hashTable;
    int hashSize;
};

// 哈希函数：对桶大小取模
int hash_func(int key, int size);
// 创建哈希表
struct HashTable* create_table(int size);
// 插入或更新编码值，返回是否应该加入结果（即第二次出现
bool insert_and_check(struct HashTable* ht, int key);
// 释放哈希表
void free_table(struct HashTable* ht);
// 将编码转换为长度为 10 的字符串（仅用于结果）
void decode_to_str(int key, char *out);

char** findRepeatedDnaSequences(char* s, int* returnSize)
{
    *returnSize = 0;
    int len = strlen(s);
    if (len < 10) return NULL;

    struct HashTable* ht = create_table(len * 2);
    char** result = (char**)malloc(sizeof(char*) * len);
    int resultCap = len;

    int key = 0;
    for (int i = 0; i < 10; ++i)
    {
        int val;
        switch (s[i])
        {
            case 'A': val = 0; break;
            case 'C': val = 1; break;
            case 'G': val = 2; break;
            case 'T': val = 3; break;
            default: val = 0;
        }
        key = (key << 2) | val;
    }

    if (insert_and_check(ht, key))
    {
        char* str = (char*)malloc(11 * sizeof(char));
        decode_to_str(key, str);
        result[(*returnSize)++] = str;
    }

    int mask = (1 << 20) - 1;
    for (int i = 10; i < len; ++i)
    {
        int val;
        switch (s[i])
        {
            case 'A': val = 0; break;
            case 'C': val = 1; break;
            case 'G': val = 2; break;
            case 'T': val = 3; break;
            default: val = 0;
        }
        key = ((key << 2) | val) & mask;

        if (insert_and_check(ht, key))
        {
            char* str = malloc(11 * sizeof(char));
            decode_to_str(key, str);
            result[(*returnSize)++] = str;
        }
    }

    free_table(ht);
    char** final = realloc(result, (*returnSize) * sizeof(char*));
    return final ? final : result;
}

int hash_func(int key, int size)
{
    return (unsigned int)key % size;
}

struct HashTable* create_table(int size)
{
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht -> hashSize = size;
    ht-> hashTable = (struct HashNode**)calloc(size, sizeof(struct HashNode*));
    return ht;
}

bool insert_and_check(struct HashTable *ht, int key)
{
    int idx = hash_func(key, ht -> hashSize);
    struct HashNode* node = ht -> hashTable[idx];
    while (node)
    {
        if (node -> key == key)
        {
            ++node -> count;
            if (node -> count == 2 && !node -> added)
            {
                node -> added = true;
                return true;
            }
            return false;
        }
        node = node -> next;
    }
    node = (struct HashNode*)malloc(sizeof(struct HashNode));
    node -> key = key;
    node -> count = 1;
    node -> added = false;
    node -> next = ht -> hashTable[idx];
    ht -> hashTable[idx] = node;
    return false;
}

void free_table(struct HashTable* ht)
{
    for (int i = 0; i < ht -> hashSize; ++i)
    {
        struct HashNode* node = ht -> hashTable[i];
        while (node)
        {
            struct HashNode* tmp = node;
            node = node -> next;
            free(tmp);
        }
    }
    free(ht -> hashTable);
    free(ht);
}

void decode_to_str(int key, char* out)
{
    char map[] = "ACGT";
    for (int i = 9; i >= 0; --i)
    {
        out[i] = map[key & 3];
        key >>= 2;
    }
    out[10] = '\0';
}
// @lc code=end

