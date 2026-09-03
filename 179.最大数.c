/*
 * @lc app=leetcode.cn id=179 lang=c
 *
 * [179] 最大数
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>

struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
};

struct List {
    struct Node* head;
    struct Node* tail;
    int size;
};

struct List* creater_List();
void insert_List(struct List* list, int val);
void delete_List(struct List* list);

int compare(int num1, int num2);
int getDigits(int num);
void append_int(char* str, int num, int index);

char* largestNumber(int* nums, int numsSize)
{
    if (!nums || numsSize <= 0) return "";

    int maxSize = 0;

    struct List* list = creater_List();
    if (!list) return "";

    for (int i = 0; i < numsSize; ++i)
    {
        maxSize += getDigits(nums[i]);
        insert_List(list, nums[i]);
    }
    if (list -> size < 1) return "";
    if (list -> head -> val == 0)
    {
        delete_List(list);
        char *zero = malloc(2);
        zero[0] = '0';
        zero[1] = '\0';
        return zero;
    }

    char* result = (char*)malloc(sizeof(char) * (maxSize + 1));
    int index = 0;

    for (struct Node* cur = list -> head; cur; cur = cur -> next)
    {
        append_int(result, cur -> val, index);
        index += getDigits(cur -> val);
    }

    char* temp = realloc(result, sizeof(char) * (index + 1));
    result = temp;
    result[index] = '\0';

    delete_List(list);
    
    return result;
}

struct List* creater_List()
{
    struct List* list = (struct List*)malloc(sizeof(struct List));
    if (!list) return NULL;

    list -> head = list -> tail = NULL;
    list -> size = 0;

    return list;
}

void insert_List(struct List* list, int val)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (!node) return ;

    node -> val = val;
    node -> prev = node -> next = NULL;
    if (!list -> head)
    {
        list -> head = list -> tail = node;
        list -> size = 1;
        return ;
    }

    struct Node* cur = list -> head;
    while (cur)
    {
        if (compare(cur -> val, val) < 0)
        {
            struct Node* prevNode = cur -> prev;
            if (!prevNode)
            {
                node -> next = cur;
                cur -> prev = node;
                list -> head = node;
                ++list -> size;
            }
            else
            {
                node -> prev = prevNode;
                node -> next = cur;
                prevNode -> next = node;
                cur -> prev = node;
                ++list -> size;
            }
            return ;
        }
        cur = cur -> next;
    }

    if (!cur)
    {
        list -> tail -> next = node;
        node -> prev = list -> tail;
        list -> tail = node;
        ++list -> size;
    }
}

void delete_List(struct List* list)
{
    if (!list) return ;

    struct Node* cur = list -> head;
    while (cur)
    {
        struct Node* next = cur -> next;
        free(cur);
        cur = next;
    }

    free(list);
}

int compare(int num1, int num2)
{
    char* buf1 = (char*)malloc(sizeof(char) * 20);
    snprintf(buf1, sizeof(char) * 20, "%d%d", num1, num2);
    char* buf2 = (char*)malloc(sizeof(char) * 20);
    snprintf(buf2, sizeof(char) * 20, "%d%d", num2, num1);

    for (int i = 0; i < strlen(buf1); ++i)
    {
        if (buf1[i] < buf2[i])
        {
            free(buf1);
            free(buf2);
            return -1;
        }
        else if (buf1[i] > buf2[i])
        {
            free(buf1);
            free(buf2);
            return 1;
        }
    }

    free(buf1);
    free(buf2);

    return 0;
}

int getDigits(int num)
{
    if (num == 0) return 1;
    int digits = 0;
    while (num)
    {
        ++digits;
        num /= 10;
    }

    return digits;
}

void append_int(char* str, int num, int index)
{
    int pos = index;

    if(num == 0)
    {
        str[pos++] = '0';
        str[pos] = '\0';
        return;
    }

    int start = pos;
    while(num > 0)
    {
        str[pos++] = num % 10 + '0';
        num = num / 10;
    }
    str[pos] = '\0';

    int i = start;
    int j = pos - 1;
    while(i < j)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        ++i;
        --j;
    }
}
// @lc code=end

