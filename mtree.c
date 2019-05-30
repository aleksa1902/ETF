#include "mtree.h"
#include "queue.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80

MTree *mtree_create(int m)
{
    MTree *mtree = malloc(sizeof(MTree));
    mtree->m = m;
    mtree->n = 0;
    mtree->root = mtree->free_node = NULL;
    return mtree;
}

void mtree_destroy(MTree *mtree)
{
    if (!mtree) return;

    Queue *q = q_create();
    q_insert(q, mtree->root);
    
    while (!q_empty(q)) {
        MTreeNode *node = q_delete(q);
        for (int i = 0; i < node->nc; i++) {
            q_insert(q, node->children[i]);
        }
        free(node);
    }

    free(mtree);
}

static MTreeNode *mtree_new_node(int m, int info)
{
    MTreeNode *node = malloc(sizeof(MTreeNode));
    node->info = info;
    node->nc = 0;
    node->children = calloc(m, sizeof(MTreeNode*));
    return node;
}

void mtree_insert(MTree *mtree, int info)
{
    if (!mtree) return;

    int m = mtree->m;
    MTreeNode *node = mtree_new_node(m, info);

    // Stablo je prazno, novi čvor postaje koren
    if (!mtree->root) {
        mtree->root = mtree->free_node = node;
        mtree->n++;
        return;
    }

    // Ubacuje novi čvor u free_node, u kom garantovano ima mesta
    MTreeNode *free_node = mtree->free_node;
    free_node->children[free_node->nc++] = node;
    mtree->n++;

    // U free_node nema više mesta, nađi koji je sledeći free_node
    if (free_node->nc == m) {
        Queue *q = q_create();
        q_insert(q, mtree->root);

        while (!q_empty(q)) {
            MTreeNode *node = q_delete(q);
            if (node->nc < m) {
                mtree->free_node = node;
                break;  // Nađen je čvor koji ima još mesta, stani
            }
            for (int i = 0; i < node->nc; i++) {
                q_insert(q, node->children[i]);
            }
        }

        q_destroy(q);
    }
}

void mtree_print(MTree *mtree)
{
    if (!mtree) return;

    Queue *q = q_create();
    q_insert(q, mtree->root);
    int m = mtree->m;
    int h = 0;   // Nivo
    int nh = 0;  // Broj čvorova na tom nivou

    while (!q_empty(q)) {
        MTreeNode *node = q_delete(q);
        int digits = (int)log10(node->info) + 1;

        int spaces = WIDTH / (pow(m, h) + 1);
        spaces -= digits / 2;

        printf("%*c", spaces, ' ');  // štampa razmake
        printf("%d", node->info);

        if (++nh == (int)pow(m, h)) {
            printf("\n\n");
            ++h;
            nh = 0;
        }

        for (int i = 0; i < node->nc; i++) {
            q_insert(q, node->children[i]);
        }
    }
    putchar('\n');
}

int mtree_size(MTree *mtree)
{
    return mtree ? mtree->n : 0;
}
