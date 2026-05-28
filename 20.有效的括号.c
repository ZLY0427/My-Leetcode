/*
 * @lc app=leetcode.cn id=20 lang=c
 *
 * [20] ÓÐÐ§µÄÀ¨ºÅ
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

struct Stack{
    char data;
    struct Stack* next;
};

void Free_all(struct Stack* head);

bool isValid(char* s)
{
    int len = strlen(s);

    struct Stack* head = (struct Stack*)malloc(sizeof(struct Stack));
    if (head == NULL)
    {
        return false;
    }
    head -> next = NULL;

    for (int i = 0; i < len; i++)
    {
        switch(s[i])
        {
            case '(':
            case '[':
            case '{':
                struct Stack* temp = (struct Stack*)malloc(sizeof(struct Stack));
                if (temp == NULL)
                {
                    Free_all(head);
                    return false;
                }
                temp -> data = s[i];
                temp -> next = head -> next;
                head -> next = temp;
                break;

            case ')':
            case ']':
            case '}':
                if (head -> next == NULL)
                {
                    Free_all(head);
                    return false;
                }
                if (s[i] == ')' && head -> next -> data != '(')
                {
                    Free_all(head);
                    return false;
                }
                else if (s[i] == ']' && head -> next -> data != '[')
                {
                    Free_all(head);
                    return false;
                }
                else if (s[i] == '}' && head -> next -> data != '{')
                {
                    Free_all(head);
                    return false;
                }
                struct Stack* del_nod = head -> next;
                head -> next = del_nod -> next;
                free(del_nod);
                break;

            default:
                Free_all(head);
                return false;
        }
    }
    if (head -> next != NULL)
    {
        Free_all(head);
        return false;
    }
    Free_all(head);
    return true;
}

void Free_all(struct Stack* head)
{
    struct Stack* p = head;
    while (p)
    {
        struct Stack* temp = p;
        p = temp -> next;
        free(temp);
    }
}
// @lc code=end

