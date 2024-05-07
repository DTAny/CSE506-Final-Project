#include "types.h"

void push(queue *q, node *n)
{
    if (q->head == 0)
    {
        q->head = n;
        q->tail = n;
    }
    else
    {
        q->tail->next = n;
        q->tail = n;
    }
}

node *peek(queue *q)
{
    return q->head;
}

node *pop(queue *q)
{
    if (q->head == 0)
    {
        return 0;
    }
    node *n = q->head;
    q->head = n->next;
    if (q->head == 0)
    {
        q->tail = 0;
    }
    return n;
}

int remove(queue *q, node *n)
{
    node *temp = q->head;
    node *prev = 0;
    while (temp != 0)
    {
        if (temp == n)
        {
            if (prev == 0)
            {
                q->head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            if (q->tail == temp)
            {
                q->tail = prev;
            }
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

int exists(queue *q, node *n)
{
    node *temp = q->head;
    while (temp != 0)
    {
        if (temp == n)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}