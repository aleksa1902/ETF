#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <time.h>

// CVOR STABLA
typedef struct cvor {
	int broj;
	struct Cvor *levo, *desno;
}Cvor;

// CVOR LISTE ZA BROJANJE
typedef struct cvor2 {
	int broj;
	int ponavlja;
	struct Cvor2 *sl;
}Cvor2;

// CVOR STEKA
typedef struct stek {
	struct Cvor *tek;
	struct Stek *sl;
}Stek;

Cvor* napraviCvor(int key) {
	Cvor *novi;

	novi = (Cvor*)malloc(sizeof(Cvor));
	novi->broj = key;
	novi->desno = NULL;
	novi->levo = NULL;

	return novi;
}

Cvor* dodajUstablo(int key, Cvor *glava) {
	Cvor *pok = glava, *q = NULL, *novi = NULL;
	
	novi = napraviCvor(key);

	while (pok != NULL) {
		q = pok;

		if (key == pok->broj) {
			if (pok->levo != NULL) {
				pok = pok->levo;
			}
			else {
				if (pok->desno == NULL) {
					pok->desno = novi;
					return glava;
				}
				else {
					while (pok->desno != NULL) {
						pok = pok->desno;
					}
					pok->desno = novi;
					return glava;
				}
			}
		}
		else if (key < pok->broj) {
			pok = pok->levo;
		}
		else {
			pok = pok->desno;
		}
	}
	if (q == NULL) {
		glava = novi;
	}
	else {
		if (novi->broj < q->broj) {
			q->levo = novi;
		}
		else {
			q->desno = novi;
		}
	}



	return glava;
}

void pretragaStabla(int key, Cvor *glava) {
	Cvor *tek = glava;

	if (glava != NULL) {

		while (tek != NULL && key != tek->broj) {
			if (key < tek->broj) {
				tek = tek->levo;
			}
			else {
				tek = tek->desno;
			}
		}
		//ako je nasao kljuc
		if (tek != NULL && key == tek->broj) {
			printf("Uspesna pretraga!\n");
		}
		else {
			printf("Neuspesna pretraga!\n");
		}
	}
	else {
		printf("Stablo nije formirano.\n");
	}
}

Cvor* brisanjeKljuca(int key, Cvor *glava) {
	Cvor *p = glava, *q = NULL, *rp = NULL, *f = NULL, *s = NULL;

	if (glava != NULL) {
		while (p != NULL && key != p->broj) {
			q = p;

			if (key < p->broj) {
				p = p->levo;
			}
			else {
				p = p->desno;
			}
		}
		if (p == NULL) {
			printf("Neispravan unos.\n");
			return glava;
		}
		if (p->levo == NULL) {
			rp = p->desno;
		}
		else if (p->desno == NULL) {
			rp = p->levo;
		}
		else {
			f = p;
			rp = p->desno;
			s = rp->levo;

			while (s != NULL) {
				f = rp;
				rp = s;
				s = rp->levo;
			}
			if (f != p) {
				f->levo = rp->desno;
				rp->desno = p->desno;
			}
			rp->levo = p->levo;
		}

		if (q == NULL) {
			glava = rp;
		}
		else if (p == q->levo) {
			q->levo = rp;
		}
		else {
			q->desno = rp;
		}
		free(p);
		return glava;
	}
	else {
		printf("Neispravan unos.\n");
		return glava;
	}
}

Cvor* brisanjeStabla(Cvor *glava) {
	Cvor *tek = glava, *pom = NULL;

	while (glava != NULL) {
		if (tek == NULL) {
			tek = glava;
		}
		if (tek->levo != NULL) {
			pom = tek;
			tek = tek->levo;
		}
		else if(tek->levo == NULL && tek->desno != NULL) {
			pom = tek;
			tek = tek->desno;
		}
		else if (tek->levo == NULL && tek->desno == NULL) {
			if (pom != NULL && pom->desno == tek) {
				pom->desno = NULL;
			}
			else if(pom != NULL){
				pom->levo = NULL;
			}
			free(tek);
			if (glava == tek) {
				glava = NULL; tek = NULL;
			}
			else {
				tek = NULL;
			}
		}
	}
	printf("Stablo je obrisano.\n");
	return glava;
}
Stek* uStek(Stek *poc, Cvor *cvor) {
	Stek *novi;
	novi = (Stek*)malloc(sizeof(Stek));
	novi->tek = cvor;
	novi->sl = poc;
	poc = novi;

	return poc;
}

Cvor* izSteka(Stek **poc) {
	Stek *pom;	Cvor *info;
	if (*poc == NULL) {
		printf("Greska");
		return NULL;
	}
	else {
		pom = *poc;
		*poc = pom->sl;
		info = pom->tek;
		free(pom);
		return info;
	}
}

void ispisStabla(Cvor *glava) {
	Cvor *tek = glava;
	Stek *poc = NULL;
	int info;

	if (glava != NULL) {

		poc = uStek(poc, tek);

		while (poc != NULL) {
			tek = izSteka(&poc);
			while (tek != NULL) {
				printf("%d  ", tek->broj);
				if (tek->desno != NULL) {
					poc = uStek(poc, tek->desno);
				}
				tek = tek->levo;
			}
		}
	}
	else {
		printf("Stablo nije formirano.\n");
	}
}

Cvor2* ubaciUlistu(Cvor2 *gl, int br) {
	Cvor2 *novi = NULL, *tek = gl;

	while (tek != NULL) {
		if (tek->broj == br) {
			tek->ponavlja++;
			return gl;
		}
		else {
			tek = tek->sl;
		}
	}
	
	novi = (Cvor2*)malloc(sizeof(Cvor2));
	novi->broj = br;
	novi->ponavlja = 1;
	novi->sl = NULL;

	if (gl == NULL) {
		gl = novi;
	}
	else {
		tek = gl;
		while (tek->sl != NULL) {
			tek = tek->sl;
		}
		tek->sl = novi;
	}

	return gl;
}

int odredjivanjeKljuca(Cvor *glava) {
	Cvor2 *gl = NULL, *tek1, *tek2;
	Cvor *tek = glava;
	Stek *poc = NULL;
	int x;

	if (glava == NULL) {
		x = 0;
		return x;
	}

	poc = uStek(poc, tek);

	while (poc != NULL) {
		tek = izSteka(&poc);
		while (tek != NULL) {
			gl = ubaciUlistu(gl, tek->broj);
			if (tek->desno != NULL) {
				poc = uStek(poc, tek->desno);
			}
			tek = tek->levo;
		}
	}
	
	tek1 = gl;
	tek2 = tek1->sl;
	x = tek1->broj;

	while (tek2 != NULL) {
		if (tek1->ponavlja < tek2->ponavlja) {
			x = tek2->broj;
			tek1 = tek2;
		}
		tek2 = tek2->sl;
	}

	return x;
}

int main() {
	Cvor *glava = NULL;
	int x = 1, izbor, key;

	while (x) {
		printf("\n====================================================================================================\n"
			"GLAVNI MENI\n\n"
			"1. Unos kljuca\n"
			"2. Pretraga stabla\n"
			"3. Brisanje kljuca\n"
			"4. Brisanje stabla\n"
			"5. Ispis stabla\n"
			"6. Odredjivanje kljuca sa najvecim brojem pojavljivanja\n"
			"0. Izlaz\n\n");

		printf("Izbor: ");
		scanf("%d", &izbor);
		putchar('\n');

		switch (izbor) {
		case 1:
			printf("Unesite vrednost kljuca:\n");
			scanf("%d", &key);

			if (key > 0) {
				glava = dodajUstablo(key, glava);
			}
			else {
				printf("Neispravan unos.\n");
			}
			break;
		case 2:
			printf("Unesite vrednost kljuca za pretragu:\n");
			scanf("%d", &key);

			if (key > 0) {
				pretragaStabla(key, glava);
			}
			else {
				printf("Neispravan unos.\n");
			}
			break;
		case 3:
			printf("Unesite vrednost kljuca za brisanje:\n");
			scanf("%d", &key);

			if (key > 0) {
				glava = brisanjeKljuca(key, glava);
			}
			else {
				printf("Neispravan unos.\n");
			}
			break;
		case 4:
			glava = brisanjeStabla(glava);
			break;
		case 5:
			ispisStabla(glava);
			break;
		case 6:
			key = odredjivanjeKljuca(glava);

			if (key == 0) {
				printf("Stablo ne postoji.\n");
			}
			else {
				printf("Kljuc sa najvecim brojem ponavljanja je %d\n", key);
			}
			break;
		case 0:
			exit(1);
			break;
		default:
			printf("Pogresnu ste opciju ukucali, pokusajte ponovo.\n");
		}

	}

}
