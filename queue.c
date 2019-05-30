#include "queue.h"

#include <stdlib.h>

Queue *q_create(void)
{
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->count = 0;
    return q;
}

void q_destroy(Queue *q)
{
    QueueNode *p;
    while (p = q->front) {
        q->front = p->next;
        free(p);
    }
    free(q);
}

bool q_empty(Queue *q)
{
    return !q->front;
}


static QueueNode *q_new_node(MTreeNode *info)
{
    QueueNode *node = malloc(sizeof(QueueNode));
    node->info = info;
    node->next = NULL;
    return node;
}

void q_insert(Queue *q, MTreeNode *info)
{
    QueueNode *p = q_new_node(info);
    if (q_empty(q)) {
        q->front = q->rear = p;
    } else {
        q->rear = q->rear->next = p;
    }
    q->count++;
}

MTreeNode *q_delete(Queue *q)
{
    if (q_empty(q)) return NULL;

    QueueNode *p = q->front;
    MTreeNode *info = p->info;
    q->front = p->next;
    
    if (!q->front) q->rear = NULL;
    free(p);
    q->count--;

    return info;
}

MTreeNode *q_front(Queue *q)
{
    return q->front->info;
}
