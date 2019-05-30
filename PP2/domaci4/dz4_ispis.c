#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef enum  kat { VipLoza, FunPit, Tribine, Parter1, Parter2 }Kategorija;

typedef struct gost {
	char ime[20];
	char prez[20];
	Kategorija primKat;
	Kategorija secKat;
}Gost;

typedef struct cvorg {
	Gost gost;
	struct cvorg *sl;
}CvorG;

typedef struct cvorKat {
	int brMesta;
	int zauzeto;
	double cena;
	CvorG *listaG;
}CvorKat;

static void ispisGosta(Gost g) {
	printf("Gost %s %s ", g.ime, g.prez);
	switch (g.primKat) {
	case 0:printf(" Prva zelja: VipLoza "); break;
	case 1:printf(" Prva zelja: FunPit "); break;
	case 2:printf(" Prva zelja: Tribine "); break;
	case 3:printf(" Prva zelja: Parter1 "); break;
	case 4:printf(" Prva zelja: Parter2 "); break;
	}
	switch (g.secKat) {
	case 0:printf(" Druga zelja: VipLoza "); break;
	case 1:printf(" Druga zelja: FunPit "); break;
	case 2:printf(" Druga zelja: Tribine "); break;
	case 3:printf(" Druga zelja: Parter1 "); break;
	case 4:printf(" Druga zelja: Parter2 "); break;
	}
	printf("\n");
}

static void ispisListeGostiju(CvorG *Gl) {
	while (Gl) {
		ispisGosta(Gl->gost);
		Gl = Gl->sl;
	}
}