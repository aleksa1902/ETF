#pragma once

typedef struct mtree_node {
    int info;
    // int m;  // Stepen
    int nc;  // Broj dece
    struct mtree_node **children;
} MTreeNode;

typedef struct mtree {
    int m;  // Stepen
    int n;  // Broj čvorova
    MTreeNode *root;
    MTreeNode *free_node;
} MTree;

MTree *mtree_create(int m);

void mtree_destroy(MTree *mtree);

void mtree_insert(MTree *mtree, int info);

void mtree_print(MTree *mtree);

int mtree_size(MTree *mtree);
