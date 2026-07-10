/*
 * @lc app=leetcode.cn id=127 lang=c
 *
 * [127] µ¥´Ê½ÓÁú
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct QueueNode {
    char* word;
    int word_index;
    int path_len;
    struct QueueNode* next;
};

struct Queue {
    int queue_count;
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct Queue* Create_Queue();
void Push_Queue(struct Queue* queue, char* word, int word_index, int path_len);
struct QueueNode* Pop_Queue(struct Queue* queue);
void Free_Queue(struct Queue* queue);
bool isNextWord(char* now_word, char* next_word);
bool isSameWord(char* word1, char* word2);

int ladderLength(char* beginWord, char* endWord,
                 char** wordList, int wordListSize)
{
    int begin_len = strlen(beginWord);
    int end_len = strlen(endWord);

    bool* visited = (bool*)calloc(wordListSize, sizeof(bool));
    if (!visited || begin_len != end_len) return 0;

    struct Queue* queue = Create_Queue();
    Push_Queue(queue, beginWord, -1, 1);

    while (queue -> queue_count > 0)
    {
        struct QueueNode* node = Pop_Queue(queue);
        char* word = node -> word;
        int path_len = node -> path_len;

        if (isSameWord(word, endWord))
        {
            Free_Queue(queue);
            free(visited);
            free(node);
            return path_len;
        }

        for (int i = 0; i < wordListSize; ++i)
        {
            if (visited[i]) continue;
            if (isNextWord(word, wordList[i]))
            {
                Push_Queue(queue, wordList[i], i, path_len + 1);
                visited[i] = true;
            }
        }
        free(node);
    }

    Free_Queue(queue);
    free(visited);
    return 0;
}

struct Queue* Create_Queue()
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) return NULL;
    queue -> queue_count = 0;
    queue -> front = NULL;
    queue -> rear = NULL;

    return queue;
}

void Push_Queue(struct Queue* queue, char* word, int word_index, int path_len)
{
    if (!queue || !word) return ;
    
    struct QueueNode* node = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!node) return ;
    node -> word = word;
    node -> word_index = word_index;
    node -> path_len = path_len;
    node -> next = NULL;
    
    if (queue -> queue_count == 0)
    {
        queue -> front = node;
        queue -> rear = node;
    }
    else
    {
        queue -> rear -> next = node;
        queue -> rear = node;
    }
    ++(queue -> queue_count);
}

struct QueueNode* Pop_Queue(struct Queue* queue)
{
    if (!queue || queue -> queue_count <= 0) return NULL;
    
    struct QueueNode* node = queue -> front;
    queue -> front = node -> next;
    if (queue -> queue_count == 1) queue -> rear = NULL;
    --(queue -> queue_count);
    
    return node;
}

void Free_Queue(struct Queue* queue)
{
    if (!queue) return ;
    struct QueueNode* node = queue -> front;
    while (node)
    {
        struct QueueNode* next = node -> next;
        free(node);
        node = next;
    }
    free(queue);
}

bool isNextWord(char* now_word, char* next_word)
{
    int len = strlen(now_word);
    int diff = 0;
    for (int i = 0; i < len; ++i)
    {
        if (now_word[i] != next_word[i]) ++diff;
        if (diff > 1) return false;
    }
    return diff == 1;
}

bool isSameWord(char* word1, char* word2)
{   
    return strcmp(word1, word2) == 0;
}
// @lc code=end

