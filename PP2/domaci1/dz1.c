#include <stdio.h>
#include <stdlib.h>
#define MAX_BR_EL 50
 
int provera(int *a[], int *b[], int n) {
    int x = 1, *pa, *pb, i;
    pa = &a[0];
    pb = &b[n - 1];
 
    for (i = 0; i < n; i++) {
        if (*pa != *pb) {
            x = 0;
            break;
        }
        *pa++;
        *--pb;
    }
    return x;
}
 
int main() {
    int a[MAX_BR_EL], b[MAX_BR_EL], n, m, i, j, x, y, mini, zam, maxi, ok;
    int *min, *tren, *max;
 
    while (1) {
        printf("Uneti duzinu prvog niza:\n");
        scanf("%d", &n);
 
        if (n <= 0 || n > MAX_BR_EL) {
            return 0;
        }
 
        printf("Uneti elemente prvog niza:\n");
 
        for (i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
 
        // sortiranje prvog niza ce biti rastuce
        for (i = 0; i < n - 1; i++)
        {
            mini = i;
            for (j = i + 1; j < n; j++) {
                if (a[j] < a[mini]) {
                    mini = j;
                }
            }
            min = &(a[mini]);
            tren = &(a[i]);
            zam = *min;
            *min = *tren;
            *tren = zam;
        }
 
        printf("Sortiran niz:\n");
        for (i = 0; i < n; i++) {
            printf("%d\t", a[i]);
        }
        printf("\n");
 
        printf("Uneti duzinu drugog niza:\n");
        scanf("%d", &m);
 
        if (m <= 0 || m > MAX_BR_EL) {
            return 0;
            printf("Linija 66");
        }
 
        printf("Uneti elemente drugog niza:\n");
 
        for (i = 0; i < m; i++) {
            scanf("%d", &b[i]);
        }
 
        // sortiranje drugog niza ce biti opadajuce da bi mogli izvrsiti proveru
        for (i = 0; i < n - 1; i++)
        {
            maxi = i;
            for (j = i + 1; j < n; j++) {
                if (b[j] > b[maxi]) {
                    maxi = j;
                }
            }
            max = &(b[maxi]);
            tren = &(b[i]);
            zam = *max;
            *max = *tren;
            *tren = zam;
        }
 
        printf("Sortiran niz:\n");
        for (i = 0; i < m; i++) {
            printf("%d\t", b[i]);
        }
        printf("\n");
 
        x = 0;
 
        if (n == m) {
            x = provera(a, b, n);
        }
        else if (n > m) {
            i = 0;
            while (i < n && m != n) {
                ok = 0; // brojac za proveru jel ima elementa, ako nema elementa tamo onda je 0 ako ima menja ga u 1 i automatski prekida for
                for (j = 0; j < m; j++) {
                    if (a[i] == b[j]) {
                        ok = 1;
                        break;
                    }
                }
                if (ok == 0) {
                    for (j = i; j < n; j++) {
                        a[j] = a[j + 1];
                    }
                    n--;
                }
                else {
                    i++;
                }
 
            }
 
            printf("Nakon izbacivanja iz skupa preostali brojevi su:");
            for (i = 0; i < n; i++) {
                printf("%d\t", a[i]);
            }
            printf("\n");
            if (n == m) {
                x = provera(a, b, n);
            }
            else {
                printf("Uslov nije ispunjen jer je i dalje prvi niz veci od drugog");
                return 0;
                printf("Linija 135");
            }
        }
        else if (n < m) {
            printf("Prvi niz je manji od drugog, automatski nema uslova za ispunjavanje zadatka!");
            return 0;
            printf("Linija 141");
            /* Ako treba da se izbacuje i iz drugog niza
            y = izradaNiza(b, a, m, n);
            if (y == 1) {
            x = provera(a, b, n);
            }
            */
        }
 
        if (x == 0) {
            printf("Prvi zadati niz ne prestavlja drugi niz u obrnutom poretku.\n");
        }
        else {
            printf("Prvi zadati niz prestavlja drugi niz u obrnutom poretku.\n");
        }
        printf("======================================================================================================================\n");
    }
}
