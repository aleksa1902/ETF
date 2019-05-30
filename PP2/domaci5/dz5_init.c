#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <sys\timeb.h>







#define A 30
#define B 30
#define C 200
#define D 10

typedef struct pesma {
	char izvodjac[B];
	char naziv[B];
	char adresa[C];
	char duzina[D];
}Pesma;

typedef struct cvor {
	Pesma *pes;
	struct cvor *sl;
	struct cvor *pr;
}Cvor;

 static Cvor* dodNaPoc(Cvor* gl, Pesma *pesma) {
	Cvor *novi = (Cvor*)malloc(sizeof(Cvor));

	if (novi == NULL) {
		printf("Greska u alokaciji memorije.");
		exit(1);
	}
	novi->pes = pesma;
	novi->sl = NULL;
	novi->pr = NULL;

	if (gl == NULL) {
		return novi;
	}
	novi->sl = gl;
	gl->pr = novi;
	return novi;
}

 static void ispisPesme(Pesma *pesma) {
	int n = 0;

	while (pesma->izvodjac[n] != '\0') {
		printf("%c", pesma->izvodjac[n]);
		n++;
	}
	printf(" - ");

	n = 0;
	while (pesma->naziv[n] != '\0') {
		printf("%c", pesma->naziv[n]);
		n++;
	}
	printf(" ");
	n = 0;
	while (pesma->duzina[n] != '\0') {
		printf("%c", pesma->duzina[n]);
		n++;
	}
	printf("\n");
}
 static void brisanjeListe(Cvor *gl) {
	Cvor *pom;
	while (gl) {
		pom = gl;
		gl = gl->sl;
		free(pom);
	}
}