/*
 * @lc app=leetcode.cn id=168 lang=c
 *
 * [168] Excel 表列名称
 */

// @lc code=start
#include <stdlib.h>

typedef struct StackNode {
    int columnNumber;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    struct StackNode* top;
    int count;
} Stack;

Stack* create_Stack();
void push_Stack(Stack* s, int columnNumber);
int pop_Stack(Stack* s);
void delete_Stack(Stack* s);

char* convertToTitle(int columnNumber)
{
    Stack* s = create_Stack();
    if (!s) return NULL;
    while (columnNumber > 0)
    {
        --columnNumber;
        push_Stack(s, columnNumber % 26);
        columnNumber = columnNumber / 26;
    }

    int length = s -> count;
    char* result = (char*)malloc(length + 1);
    if (!result)
    {
        delete_Stack(s);
        return NULL;
    }

    for (int i = 0; i < length; ++i)
        result[i] = 'A' + pop_Stack(s);

    result[length] = '\0';

    delete_Stack(s);

    return result;
}

Stack* create_Stack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s) return NULL;
    
    s -> top = NULL;
    s -> count = 0;
    
    return s;
}

void push_Stack(Stack* s, int columnNumber)
{
    if (!s) return ;
    
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (!node) return ;
    
    node -> columnNumber = columnNumber;
    node -> next = s -> top;
    
    s -> top = node;
    ++s -> count;
}

int pop_Stack(Stack* s)
{
    if (!s || s -> count <= 0) return -1;
    
    StackNode* node = s -> top;
    
    s -> top = node -> next;
    --s -> count;
    
    int columnNumber = node -> columnNumber;

    free(node);
    
    return columnNumber;
}

void delete_Stack(Stack* s)
{
    if (!s) return ;
    
    while (s -> count > 0)
        pop_Stack(s);
    
    free(s);
}

// @lc code=end

