#include "dz5_load.c"
static void ispisListe(Cvor *gl) {
	Cvor *tek;
	tek = gl;
	while (tek) {
		ispisPesme(tek->pes);
		tek = tek->sl;
	}
}

static Cvor *zajednicki(Cvor *Gl, Cvor *Gl2, Cvor *Gl3) {
	Cvor *pok1, *pok2;
	int br = 0;
	char ispis1[50], ispis2[50];
	pok1 = Gl;
	while (pok1) {
		pok2 = Gl2;
		br = 0;
		strcpy(ispis1, pok1->pes->naziv);
		while (pok2) {
			strcpy(ispis2, pok2->pes->naziv);
			if (strcmp(ispis1, ispis2) == 0) {
				br = 1;
				break;
			}
			pok2 = pok2->sl;
		}
		if (br == 1) {
			Gl3 = dodNaPoc(Gl3, pok1->pes);
		}
		pok1 = pok1->sl;
	}
	return Gl3;
}