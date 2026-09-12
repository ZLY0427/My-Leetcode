/*
 * @lc app=leetcode.cn id=202 lang=c
 *
 * [202] 快乐�?
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

struct HashNode {
    int val;
    struct HashNode* next;
};

struct Hash {
    struct HashNode** hashTable;
    int hashSize;
};

struct Hash* create_Hash(int hashSize);
bool find_Hash(struct Hash* hash, int val);
void insert_Hash(struct Hash* hash, int val);
void free_Hash(struct Hash* hash);

bool isHappy(int n)
{
    struct Hash* hash = create_Hash(127);
    while (n != 1)
    {
        if (find_Hash(hash, n))
        {
            free_Hash(hash);
            return false;
        }
        insert_Hash(hash, n);

        int sum = 0;
        while (n != 0)
        {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
    }

    free_Hash(hash);
    return true;
}

struct Hash* create_Hash(int hashSize)
{
    if (hashSize <= 0) return NULL;
    struct Hash* hash = (struct Hash*)malloc(sizeof(struct Hash));
    if (!hash) return NULL;

    hash -> hashSize = hashSize;
    hash -> hashTable = (struct HashNode**)malloc(sizeof(struct HashNode*) * hashSize);
    if (!hash -> hashTable)
    {
        free(hash);
        return NULL;
    }
    for (int i = 0; i < hashSize; ++i)
        hash -> hashTable[i] = NULL;
    
    return hash;
}

bool find_Hash(struct Hash* hash, int val)
{
    int index = val % hash -> hashSize;
    struct HashNode* cur = hash -> hashTable[index];
    while (cur != NULL)
    {
        if (cur -> val == val) return true;
        cur = cur -> next;
    }

    return false;
}

void insert_Hash(struct Hash* hash, int val)
{
    int index = val % hash -> hashSize;
    struct HashNode* cur = hash -> hashTable[index];
    while (cur != NULL)
    {
        if (cur -> val == val) return;
        cur = cur -> next;
    }
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode -> val = val;
    newNode -> next = hash -> hashTable[index];
    hash -> hashTable[index] = newNode;
}

void free_Hash(struct Hash* hash)
{
    if (!hash) return;
    for (int i = 0; i < hash -> hashSize; ++i)
    {
        struct HashNode* cur = hash -> hashTable[i];
        while (cur)
        {
            struct HashNode* temp = cur;
            cur = cur -> next;
            free(temp);
        }
    }
    free(hash -> hashTable);
    free(hash);
}

// @lc code=end

