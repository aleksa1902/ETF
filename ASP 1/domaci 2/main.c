#include "mtree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CLEAR system("cls")
#define PAUSE system("pause")

bool menu(void)
{
    static MTree *mtree = NULL;

    CLEAR;
    printf("GLAVNI MENI\n\n"
           "1. Stvaranje stabla\n"
           "2. Brisanje stabla\n"
           "3. Umetanje elementa\n"
           "4. Ispis stabla\n"
           "5. Broj cvorova\n"
           "6. Izlaz\n\n");

    int choice, t;
    printf("Izbor: ");
    scanf("%d", &choice);
    putchar('\n');

    switch (choice) {
    case 1:
        printf("Stepen stabla: ");
        scanf("%d", &t);
        if (mtree) mtree_destroy(mtree);
        mtree = mtree_create(t);
        break;
    case 2:
        mtree_destroy(mtree);
        mtree = NULL;
        break;
    case 3:
        printf("Vrednost: ");
        scanf("%d", &t);
        mtree_insert(mtree, t);
        break;
    case 4:
        mtree_print(mtree);
        break;
    case 5:
        printf("Broj cvorova: %d\n", mtree_size(mtree));
        break;
    case 6:
        mtree_destroy(mtree);
        return false;
    default:
        puts("Neispravan unos");
    }

    PAUSE;
    return true;
}

int main(void)
{
    while (menu());
}
