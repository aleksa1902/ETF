#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define PAUSE system("pause")
 
void ispisNajduzeReci(char **mat, int n, int m){
    int i, j, ns, max, br, l, k;
    char *maxRec, *pomRec;
     
    max = (int)sqrt(n*n + m*m) + 2;
     
    maxRec = (char*)malloc(sizeof(char)*max);
    pomRec = (char*)malloc(sizeof(char)*max);
     
    maxRec[0] = '\0';
     
    for(i=0; i<n; i++){
     
        for(j=0; j<m; j++){
         
            if(isalpha(mat[i][j])){
                //na Desno
                pomRec[0] = '\0';
                for(l=j, br=0; l<m && isalpha(mat[i][l]); br++, l++){
                    pomRec[br] = mat[i][l];
                }
                pomRec[br] = '\0';
                if(strlen(maxRec) < strlen(pomRec)){
                    strcpy(maxRec, pomRec);//kopira pomRec u MaxRec
                    printf("Nadjeno na Desno %d %d\n", i, j);
                }
                //na Dole
                pomRec[0] = '\0';
                for(l=i, br=0; l<n && isalpha(mat[l][j]); br++, l++){
                    pomRec[br] = mat[l][j];
                }
                pomRec[br] = '\0';
                if(strlen(maxRec) < strlen(pomRec)){
                    strcpy(maxRec, pomRec);//kopira pomRec u MaxRec
                    printf("Nadjeno na Dole %d %d\n", i, j);
                }
                //na Dole Desno
                pomRec[0] = '\0';
                for(l=i, k=j, br=0; l<n && k<m && isalpha(mat[l][k]); br++, l++, k++){
                    pomRec[br] = mat[l][k];
                }
                pomRec[br] = '\0';
                if(strlen(maxRec) < strlen(pomRec)){
                    strcpy(maxRec, pomRec);//kopira pomRec u MaxRec
                    printf("Nadjeno na Dole Desno %d %d\n", i, j);
                }
                //na Gore Desno
                pomRec[0] = '\0';
                for(l=i, k=j, br=0; l>=0 && k<m && isalpha(mat[l][k]); br++, l--, k++){
                    pomRec[br] = mat[l][k];
                }
                pomRec[br] = '\0';
                if(strlen(maxRec) < strlen(pomRec)){
                    strcpy(maxRec, pomRec);//kopira pomRec u MaxRec
                    printf("Nadjeno na Gore Desno %d %d\n", i, j);
                }
            }           
        }
    }
    printf("Najduza rec je:%s\n",maxRec);
}
 
main() {
    char **mat;
    int n, m, i, j, veci, manji, opt;
 
    srand(time(NULL));
 
    while (1) {
        printf("BELA UKRESTENICA\n\n"
            "1. Stvaranje ukrestenice\n"
            "2. Unos vrednosti u ukrestenicu pseudoslucajnim znakom\n"
            "3. Unos vrednosti u ukrestenicu\n"
            "4. Ispis ukrestenice\n"
            "5. Pretrazi ukrestenicu\n"
            "0. Nazad\n\n"
            "Izbor: ");
         
        int opcija;
        scanf("%d", &opcija);
        printf("\n");
 
        opt = 0;
        switch (opcija) {
        case 1:
            if (opt == 1) {
                for (i = 0; i<n; i++) {
                    free(mat[i]);
                }
                free(mat);
            }
            printf("Unesite broj kolone i vrste:\n");
            scanf("%d %d", &n, &m);
            break;
        case 2:
            mat = (char**)malloc(sizeof(char*)*n);
            if (mat == NULL) {
                printf("Greska!");
                exit(1);
            }
            for (i = 0; i<n; i++) {
                mat[i] = (char*)malloc(sizeof(char)*m);
                if (mat[i] == NULL) {
                    printf("Greska!");
                    exit(1);
                }
            }
 
            veci = 127;
            manji = 32;
            for (i = 0; i<n; i++) {
                for (j = 0; j<m; j++) {
                    mat[i][j] = rand() % (veci - manji + 1) + 32;
                }
            }
            opt = 1;
            break;
        case 3:
            mat = (char**)malloc(sizeof(char*)*n);
            if (mat == NULL) {
                printf("Greska!");
                exit(1);
            }
            for (i = 0; i<n; i++) {
                mat[i] = (char*)malloc(sizeof(char)*m);
                if (mat[i] == NULL) {
                    printf("Greska!");
                    exit(1);
                }
            }
 
            for (i = 0; i<n; i++) {
                for (j = 0; j<m; j++) {
                    scanf("%c",&mat[i][j]);
                }
            }
            opt = 1;
            break;
        case 4:
            if (opt == 1) {
                break;
            }
            for (i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) printf("+---");
                printf("+\n");
                for (j = 0; j < m; j++) {
                    printf("| %c ", mat[i][j]);
                }
                printf("|\n");
            }
            for (int j = 0; j < n; j++) printf("+---");
            printf("+\n");
            break;
        case 5:
            ispisNajduzeReci(mat, n, m);
            break;
        case 0:
            for (i = 0; i<n; i++) {
                free(mat[i]);
            }
            free(mat);
            mat = NULL;
            return 0;
        default:
            printf("Neispravan unos\n");
        }
    }
}
