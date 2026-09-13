/*
 * @lc app=leetcode.cn id=205 lang=c
 *
 * [205] 同构字符��?
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct HashNode {
    char key;
    char val;
    struct HashNode* next;
};

struct Hash {
    struct HashNode** hashTable;
    int hashSize;
};

struct Hash* create_Hash(int hashSize);
void insert_Hash(struct Hash* hash, char key, char val);
char get_Hash(struct Hash* hsah, char key);
void free_Hash(struct Hash* hash);

bool isIsomorphic(char* s, char* t)
{
    if ((s && !t) || (!s && t)) return false;
    else if (!s && !t) return true;
    int sSize = strlen(s);
    int tSize = strlen(t);
    if (sSize != tSize || sSize < 0 || tSize < 0) return false;

    struct Hash* hashS = create_Hash(128);
    struct Hash* hashT = create_Hash(128);
    if (!hashS || !hashT)
    {
        free_Hash(hashS);
        free_Hash(hashT);
        return false;
    }

    for (int i = 0; i < sSize; i++)
    {
        char sc = s[i];
        char tc = t[i];
        char s2t = get_Hash(hashS, sc);
        char t2s = get_Hash(hashT, tc);

        if (s2t == '\0' && t2s == '\0')
        {
            insert_Hash(hashS, sc, tc);
            insert_Hash(hashT, tc, sc);
        }
        else
        {
            if (s2t != tc || t2s != sc)
            {
                free_Hash(hashS);
                free_Hash(hashT);
                return false;
            }
        }
    }

    free_Hash(hashS);
    free_Hash(hashT);
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

void insert_Hash(struct Hash* hash, char key, char val)
{
    if (!hash) return ;
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    if (!newNode) return ;

    int index = (unsigned char)key % hash -> hashSize;

    newNode -> key = key;
    newNode -> val = val;
    newNode -> next = hash -> hashTable[index];
    hash -> hashTable[index] = newNode;
}

char get_Hash(struct Hash* hash, char key)
{
    if (!hash) return '\0';

    int index = (unsigned char)key % hash -> hashSize;

    struct HashNode* node = hash -> hashTable[index];
    while (node)
    {
        if (node -> key == key) return node -> val;
        node = node -> next;
    }

    return '\0';
}

void free_Hash(struct Hash* hash)
{
    if (!hash) return;
    for (int i = 0; i < hash -> hashSize; i++)
    {
        struct HashNode* node = hash -> hashTable[i];
        while (node)
        {
            struct HashNode* next = node -> next;
            free(node);
            node = next;
        }
    }
    
    free(hash -> hashTable);
    free(hash);
}
// @lc code=end

