#pragma once

#include "mtree.h"

#include <stdbool.h>

typedef struct q_node {
    MTreeNode *info;
    struct q_node *next;
} QueueNode;

typedef struct queue {
    QueueNode *front, *rear;
    int count;
} Queue;

Queue *q_create(void);

void q_destroy(Queue *q);

bool q_empty(Queue *q);

void q_insert(Queue *q, MTreeNode *info);

MTreeNode *q_delete(Queue *q);

MTreeNode *q_front(Queue *q);
