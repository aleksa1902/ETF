#include<stdio.h>
#include<stdlib.h>
 
void napraviMatricu(unsigned **mat, int n){
    int i, j;
 
    for(i=0; i<n; i++){
        mat[i] = (unsigned*)malloc(sizeof(unsigned)*i);//da se racuna i dijagonala, imali bi (i+1)
    }
 
    //unos matrice
    printf("===========================================\nUnesi elemente matrice:\n");
    for(i=0; i<n; i++){
        for(j=0; j<i; j++){
            scanf("%u",&mat[i][j]);
        }
    }
}
 
void brisanjeMatrice(unsigned **mat, int n){
    int i;
    //oslobadjanje matrice
    for(i=0; i<n; i++){
        free(mat[i]);
    }
    free(mat);
}
 
int dohvati(unsigned **mat, int n, int i, int j){
    if(i<=0 || j>=n){
        return -1;//greska.
    }
    if(j<0 || j>=i){
        return -1;//greska.
    }
    return mat[i][j];
}
 
void postavi(unsigned **mat, int n, int i, int j, int x){
    if(i<=0 || j>=n){
        return;//greska.
    }
    if(j<0 || j>=i){
        return;//greska.
    }
     mat[i][j] = x;
}
 
void ispisMatrice(unsigned **mat, int n){
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(j<i){
                printf("%u\t",mat[i][j]);
            }else{
                printf("0\t");
            }
        }
        printf("\n");
    }
}
 
main(){
    unsigned **mat;//niz sa pokazivacima na prve clanove(niz nizova)
    int n, m, i, j, opt;
    unsigned x;
 
    while(1){
        printf("===========================================\nUnesi Opciju:\n1.Unos Matrice\n2.Podrazumevane Vrednosti???\n3.Dohvatanje elementa\n4.Postavljanje vrednosti\n5.Dohvatanje nepodrazumevane vrednosti\n6.Ispis matrice\n7.Racunanje ostvarene ustede memorijskog prostora\n8.Brisanje matrice\n0.Izlaz===========================================\n");
        scanf("%d",&opt);
        if(opt == 0) break;//izlaz
 
        switch(opt){
            case 1:{
                printf("===========================================\n");
                printf("Uneti dimenziju Matrice: ");
                scanf("%d",&n);
 
                //zauzimamo memoriju za n pokazivaca na nizove.
                mat = (unsigned**)malloc(sizeof(unsigned*)*n);
                if(*mat == NULL){
                    printf("Greska!\n");
                    exit(1);
                }
                napraviMatricu(mat, n);
                break;
            }
            case 2:{
                printf("===========================================\n");
                printf("Kontradikcija sa zadatkom!\n");
                break;
            }
            case 3:{
                printf("===========================================\n");
                printf("Uneti i, j> ");
                scanf("%d %d",&i, &j);
                x = dohvati(&mat, n, i , j);
                if(x == -1){
                    printf("Greska u indeksima!\n");
                }else{
                    printf("Dohvatili smo %d\n",mat[i][j]);
                }
                break;
            }
            case 4:{
                printf("===========================================\n");
                printf("Uneti i, j, x> ");
                scanf("%d %d %u",&i, &j, &x);
                postavi(mat, n, i , j, x);
                break;
            }
            case 5:{
                printf("===========================================\n");
                //  (n*(n-1))/2.0 broj elemeata ispod glavne dijagonale
                printf("Broj nepodrazumevanih elemenata je %d\n",(n*(n-1))/2);
                break;
            }
            case 6:{
                printf("===========================================\n");
                ispisMatrice(mat, n);
                break;
            }
            case 7:{
                printf("===========================================\n");
                //(n*(n+1))/2 broj elemenata iznad i na glavnoj dijagonali!
                printf("Ostvarena usteda %dB\n", ((n*(n+1))/2)*sizeof(unsigned));
                break;
            }
            case 8:{
                printf("===========================================\n");
                brisanjeMatrice(mat, n);
                break;
            }
            default:{
                printf("Nepoznata Opcija!\n");
                break;
            }
        }
    }
 
 
 
}
