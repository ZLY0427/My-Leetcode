/*
 * @lc app=leetcode.cn id=208 lang=c
 *
 * [208] 实现 Trie (前缀�?)
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

typedef struct Trie {
    struct Trie* children[26];
    bool isEnd; 
} Trie;

Trie* trieCreate()
{
    Trie* node = (Trie*)malloc(sizeof(Trie));
    if (!node) return NULL;

    node -> isEnd = false;
    for (int i = 0; i < 26; ++i)
        node -> children[i] = NULL;
    
    return node;
}

void trieInsert(Trie* obj, char* word)
{
    Trie* p = obj;
    for (int i = 0; word[i]; ++i)
    {
        int idx = word[i] - 'a';
        if (!p -> children[idx])
            p -> children[idx] = trieCreate();
    
        p = p -> children[idx];
    }
    p -> isEnd = true;
}

bool trieSearch(Trie* obj, char* word)
{
    Trie* p = obj;
    for (int i = 0; word[i]; ++i)
    {
        int idx = word[i] - 'a';
        if (!p -> children[idx]) return false;
        p = p -> children[idx];
    }
    return p -> isEnd;
}

bool trieStartsWith(Trie* obj, char* prefix)
{
    Trie* p = obj;
    for (int i = 0; prefix[i]; ++i)
    {
        int idx = prefix[i] - 'a';
        if (!p -> children[idx]) return false;
        p = p -> children[idx];
    }
    return true;
}

void trieFree(Trie* obj)
{
    if (!obj) return;
    for (int i = 0; i < 26; ++i)
        trieFree(obj -> children[i]);
    
    free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/
// @lc code=end

