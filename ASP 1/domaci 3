#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 80
#define M 50

typedef struct cvor {
	int ulaz, izlaz;
	int skupZidova;
	int posecen;
	struct cvor *gore, *dole, *levo, *desno;
}Cvor;

typedef struct lista {
	int x, y;
	int skupZidova;
	struct lista *sl;
}Lista;

typedef struct qcvor{
	int x, y;
	struct Qcvor *sl;
}Qcvor;

typedef struct red {
	Qcvor *poc;
	Qcvor *kraj;
}Red;

Cvor *napraviMatricu(Cvor *mat[N][M], int n, int m) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			mat[i][j] = (Cvor*)malloc(sizeof(Cvor));
			mat[i][j]->gore = NULL;
			mat[i][j]->dole = NULL;
			mat[i][j]->levo = NULL;
			mat[i][j]->desno = NULL;
			mat[i][j]->skupZidova = 0;
			mat[i][j]->ulaz = 0;
			mat[i][j]->izlaz = 0;
			mat[i][j]->posecen = 0;
		}
	}
	return mat;
}
Lista *dodajInfo(Lista *Gl, int x, int y) {
	Lista *novi, *tek;

	novi = (Lista*)malloc(sizeof(Lista));
	novi->skupZidova = 1;
	novi->x = x;
	novi->y = y;
	novi->sl = NULL;

	if (Gl == NULL) {
		Gl = novi;
		novi->sl = NULL;
	}
	else {
		novi->sl = Gl;
		Gl = novi;
	}
	return Gl;
}

Lista *brisiZidIzListe(Lista *Gl, int randZid, int *x, int *y)
{
	Lista *stari, *tek = Gl, *pre = Gl;
	int brojac = 0;
	while (tek != NULL) {
		if (brojac == randZid) {
			stari = tek;

			*x = tek->x;
			*y = tek->y;

			tek = tek->sl;
			if (pre == Gl) {
				Gl = tek;
				free(pre);
			}
			else {
				pre->sl = tek;
				free(stari);
			}
			break;
		}
		else {
			brojac++;
			pre = tek;
			tek = tek->sl;
		}
	}
	return Gl;
}

Cvor *primAlg(Cvor *mat[N][M], int n, int m) {
	int x, y, br;
	int x1, y1;
	Lista *zid = NULL, *slobCvor = NULL;
	int i, j, brzid = 0, slZid;


	srand(time(NULL));

	x = rand() % (n - 1);
	y = rand() % (m - 1);
	mat[x][y]->posecen = 1;

	if (x - 1 >= 0) {
		x1 = x - 1;
		if (mat[x1][y]->posecen == 0 && mat[x1][y]->skupZidova == 0) {
			zid = dodajInfo(zid, x1, y);
			mat[x1][y]->skupZidova = 1;
			brzid++;
		}
	}
	if (x + 1 < n) {
		x1 = x + 1;
		if (mat[x1][y]->posecen == 0 && mat[x1][y]->skupZidova == 0) {
			zid = dodajInfo(zid, x1, y);
			mat[x1][y]->skupZidova = 1;
			brzid++;
		}
	}
	if (y - 1 >= 0) {
		y1 = y - 1;
		if (mat[x][y1]->posecen == 0 && mat[x][y1]->skupZidova == 0) {
			zid = dodajInfo(zid, x, y1);
			mat[x][y1]->skupZidova = 1;
			brzid++;
		}
	}

	if (y + 1 < m) {
		y1 = y + 1;
		if (mat[x][y1]->posecen == 0 && mat[x][y1]->skupZidova == 0) {
			zid = dodajInfo(zid, x, y1);
			mat[x][y1]->skupZidova = 1;
			brzid++;
		}
	}


	while (zid != NULL) {

		slZid = rand() % (brzid - 1);

		zid = brisiZidIzListe(zid, slZid, &x, &y);
		mat[x][y]->posecen = 1;
		brzid--;

		br = 1;
		while (br) {



			if (x + 1 < n) {
				if (mat[x + 1][y]->posecen == 1 && br == 1) {
					mat[x + 1][y]->gore = mat[x][y];
					mat[x][y]->dole = mat[x + 1][y];
					br = 0;
				}
			}
			if (x - 1 >= 0) {
				if (mat[x - 1][y]->posecen == 1 && br == 1) {
					mat[x - 1][y]->dole = mat[x][y];
					mat[x][y]->gore = mat[x + 1][y];
					br = 0;
				}
			}
			if (y + 1 < m) {
				if (mat[x][y + 1]->posecen == 1 && br == 1) {
					mat[x][y + 1]->desno = mat[x][y];
					mat[x][y]->levo = mat[x][y + 1];
					br = 0;
				}
			}
			if (y - 1 >= 0) {
				if (mat[x][y - 1]->posecen == 1 && br == 1) {
					mat[x][y - 1]->desno = mat[x][y];
					mat[x][y]->levo = mat[x][y - 1];
					br = 0;
				}
			}
		}

		if (x - 1 >= 0) {
			x1 = x - 1;
			if (mat[x1][y]->posecen == 0 && mat[x1][y]->skupZidova == 0) {
				zid = dodajInfo(zid, x1, y);
				mat[x1][y]->skupZidova = 1;
				brzid++;
			}
		}
		if (x + 1 < n) {
			x1 = x + 1;
			if (mat[x1][y]->posecen == 0 && mat[x1][y]->skupZidova == 0) {
				zid = dodajInfo(zid, x1, y);
				mat[x1][y]->skupZidova = 1;
				brzid++;
			}
		}
		if (y - 1 >= 0) {
			y1 = y - 1;
			if (mat[x][y1]->posecen == 0 && mat[x][y1]->skupZidova == 0) {
				zid = dodajInfo(zid, x, y1);
				mat[x][y1]->skupZidova = 1;
				brzid++;
			}
		}

		if (y + 1 < m) {
			y1 = y + 1;
			if (mat[x][y1]->posecen == 0 && mat[x][y1]->skupZidova == 0) {
				zid = dodajInfo(zid, x, y1);
				mat[x][y1]->skupZidova = 1;
				brzid++;
			}
		}

	}
	return mat;
}
Cvor *napCvor(Cvor *cvor) {
	cvor = (Cvor*)malloc(sizeof(Cvor));
	cvor->gore = NULL;
	cvor->dole = NULL;
	cvor->levo = NULL;
	cvor->desno = NULL;
	cvor->skupZidova = 0;
	cvor->ulaz = 0;
	cvor->izlaz = 0;
	return cvor;
}

Cvor *unosIzlaza(Cvor *mat[N][M], int n, int m) {
	Cvor *izlaz = NULL;
	int x, y, gde, uliz;
	while (1) {

		scanf("%d%d", &x, &y);
		//gornji levi ugao
		if (x == 0 && y == 0 && mat[x][y]->gore == NULL && mat[x][y]->levo == NULL) {
			printf("Da li ocete izlaz levo(1) ili gore(0):\n");
			scanf("%d", &gde);
			if (gde) {
				izlaz = napCvor(izlaz);
				printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
				scanf("%d", &uliz);
				if (uliz) {
					mat[x][y]->ulaz = 1;
				}
				else {
					mat[x][y]->izlaz = 1;
				}
				mat[x][y]->levo = izlaz;
				izlaz->desno = mat[x][y];
			}
			else {
				izlaz = napCvor(izlaz);
				printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
				scanf("%d", &uliz);
				if (uliz) {
					mat[x][y]->ulaz = 1;
				}
				else {
					mat[x][y]->izlaz = 1;
				}				
				mat[x][y]->gore = izlaz;
				izlaz->dole = mat[x][y];
			}
			break;
		}
		//gornja strana
		else if (x == 0 && y != 0 && y != m - 1 && mat[x][y]->gore == NULL) {
			izlaz = napCvor(izlaz);
			printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
			scanf("%d", &uliz);
			if (uliz) {
				mat[x][y]->ulaz = 1;
			}
			else {
				mat[x][y]->izlaz = 1;
			}
			mat[x][y]->gore = izlaz;
			izlaz->dole = mat[x][y];
			break;
		}
		//gornji desni ugao
		else if(x == 0 && y == m - 1 && mat[x][y]->gore == NULL && mat[x][y]->desno == NULL) {
			printf("Da li ocete izlaz desno(1) ili gore(0):\n");
			scanf("%d", &gde);
			if (gde) {
				izlaz = napCvor(izlaz);
				printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
				scanf("%d", &uliz);
				if (uliz) {
					mat[x][y]->ulaz = 1;
				}
				else {
					mat[x][y]->izlaz = 1;
				}
				mat[x][y]->desno = izlaz;
				izlaz->levo = mat[x][y];
			}
			else {
				izlaz = napCvor(izlaz);
				printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
				scanf("%d", &uliz);
				if (uliz) {
					mat[x][y]->ulaz = 1;
				}
				else {
					mat[x][y]->izlaz = 1;
				}
				mat[x][y]->gore = izlaz;
				izlaz->dole = mat[x][y];
			}
			break;
		}
		//leva strana
		else if (x != 0 && y == 0 && x != n-1 && mat[x][y]->levo == NULL) {
			izlaz = napCvor(izlaz);
			printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
			scanf("%d", &uliz);
			if (uliz) {
				mat[x][y]->ulaz = 1;
			}
			else {
				mat[x][y]->izlaz = 1;
			}
			mat[x][y]->levo = izlaz;
			izlaz->desno = mat[x][y];
			break;
		}
		//desna strana
		else if (x != 0 && y == m - 1 && x != n - 1 && mat[x][y]->desno == NULL) {
			izlaz = napCvor(izlaz);
			printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
			scanf("%d", &uliz);
			if (uliz) {
				mat[x][y]->ulaz = 1;
			}
			else {
				mat[x][y]->izlaz = 1;
			}
			mat[x][y]->desno = izlaz;
			izlaz->levo = mat[x][y];
			break;
		}
		//donji desni ugao
		else if (x == n - 1 && y == m - 1 && mat[x][y]->dole == NULL && mat[x][y]->desno == NULL) {
			printf("Da li ocete izlaz desno(1) ili dole(0):\n");
			scanf("%d", &gde);
			if (gde) {
				izlaz = napCvor(izlaz);
				printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
				scanf("%d", &uliz);
				if (uliz) {
					mat[x][y]->ulaz = 1;
				}
				else {
					mat[x][y]->izlaz = 1;
				}
				mat[x][y]->desno = izlaz;
				izlaz->levo = mat[x][y];
			}
			else {
				izlaz = napCvor(izlaz);
				printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
				scanf("%d", &uliz);
				if (uliz) {
					mat[x][y]->ulaz = 1;
				}
				else {
					mat[x][y]->izlaz = 1;
				}
				mat[x][y]->dole = izlaz;
				izlaz->gore = mat[x][y];
			}
			break;
		}
		//donji levi ugao
		if (x == n - 1 && y == 0 && mat[x][y]->dole == NULL && mat[x][y]->levo == NULL) {
			printf("Da li ocete izlaz levo(1) ili dole(0):\n");
			scanf("%d", &gde);
			if (gde) {
				izlaz = napCvor(izlaz);
				printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
				scanf("%d", &uliz);
				if (uliz) {
					mat[x][y]->ulaz = 1;
				}
				else {
					mat[x][y]->izlaz = 1;
				}
				mat[x][y]->levo = izlaz;
				izlaz->desno = mat[x][y];
			}
			else {
				izlaz = napCvor(izlaz);
				printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
				scanf("%d", &uliz);
				if (uliz) {
					mat[x][y]->ulaz = 1;
				}
				else {
					mat[x][y]->izlaz = 1;
				}
				mat[x][y]->dole = izlaz;
				izlaz->gore = mat[x][y];
			}
			break;
		}
		//donja strana
		else if (x == n - 1 && y != 0 && y != m - 1 && mat[x][y]->dole == NULL) {
			izlaz = napCvor(izlaz);
			printf("Da li unosite ulaz(1) ili izlaz(0)?\n");
			scanf("%d", &uliz);
			if (uliz) {
				mat[x][y]->ulaz = 1;
			}
			else {
				mat[x][y]->izlaz = 1;
			}
			mat[x][y]->dole = izlaz;
			izlaz->gore = mat[x][y];
			break;
		}
		else {
			printf("Neispravno, ponovo!\n");
		}
	}
	return mat;
}

Cvor *brisanjeMatrice(Cvor *mat[N][M], int n, int m) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			free(mat[i][j]);
		}
	}
	return mat;
}

Red *napRed(void){
	Red *novi = (Red*)malloc(sizeof(Red));
	novi->poc = novi->kraj = NULL;
	return novi;
}

void brisanjeReda(Red *red){
	Qcvor *novi;
	while (novi = red->poc) {
		red->poc = novi->sl;
		free(novi);
	}
	free(red);
}

Qcvor *noviCvorRed(int x, int y) {
	Qcvor *novi;
	novi = (Qcvor*)malloc(sizeof(Qcvor));
	novi->x = x;
	novi->y = y;
	novi->sl = NULL;
	return novi;
}

void ubacivanjeUred(Red *red, int x, int y) {
	Qcvor *novi = noviCvorRed(x, y);
	if (!red->poc) {
		red->poc = novi;
	}
	else {
		red->kraj->sl = novi;
	}
	red->kraj = novi;
}

void vadiIzReda(Red *red, int *x, int *y){
	if (!red->poc) 
		return NULL;
	Qcvor *novi = red->poc;
	*x = red->poc->x;
	*y = red->poc->y;
	red->poc = novi->sl;
	if (!red->poc) red->kraj = NULL;
	free(novi);
}

void obilazakPoSir(Cvor *mat[N][M], int n, int m) {
	int i, j, x = 0, y = 0;
	int br = 0;
	Red *red = napRed();
	Qcvor *pamti;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			mat[i][j]->posecen = 0;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (mat[i][j]->ulaz == 1) {
				x = i;
				y = j;
				break;
			}
		}
		if (x != 0 || y != 0)
			break;
	}

	ubacivanjeUred(red, x, y);

	while (red->poc != NULL) {
		vadiIzReda(red, &x, &y);
		mat[x][y]->posecen = 1;
		printf("Posecen cvor (x,y) = (%d, %d)\n", x, y);

		if (mat[x][y]->izlaz == 0) {
			if (x - 1 >= 0 && mat[x][y]->gore != NULL && mat[x - 1][y]->posecen == 0) {
				ubacivanjeUred(red, x-1, y);
			}
			if (x + 1 < n && mat[x][y]->dole != NULL && mat[x + 1][y]->posecen == 0) {
					ubacivanjeUred(red, x+1, y);
				}

			if (y - 1 >= 0 && mat[x][y]->levo != NULL && mat[x][y - 1]->posecen == 0) {
				ubacivanjeUred(red, x, y-1);
			}

			if (y + 1 < m && mat[x][y]->desno != NULL && mat[x][y + 1]->posecen == 0) {
				ubacivanjeUred(red, x, y+1);
			}

		}
		else {
			br = 1;
			break;
		}
	}
	brisanjeReda(red);

	if (br == 1) {
		printf("Nasao je izlaz!\n");
	}
	else {
		printf("Nije nasao izlaz!\n");
	}
}

Cvor *povezujCvorove(Cvor *mat[N][M], int n, int m) {
	int x, y, izbor;

	printf("Odaberi cvor:\n");
	scanf("%d" ,&x);
	scanf("%d", &y);

	printf("Gde ocete da spojite?(gore 0/dole 1/levo 2/desno 3)\n");
	scanf("%d", &izbor);

	if (izbor == 0) {
		if (x - 1 >= 0) {
			mat[x][y]->gore = mat[x - 1][y];
			mat[x - 1][y]->dole = mat[x][y];
		}
		else {
			printf("Ne moze\n");
		}
	}
	else if (izbor == 1) {
		if (x + 1 < n) {
			mat[x][y]->dole = mat[x + 1][y];
			mat[x + 1][y]->gore = mat[x][y];
		}
		else {
			printf("Ne moze\n");
		}
	}
	else if (izbor == 2) {
		if (y - 1 >= 0) {
			mat[x][y]->levo = mat[x][y - 1];
			mat[x][y - 1]->desno = mat[x][y];
		}
		else {
			printf("Ne moze\n");
		}
	}
	else if (izbor == 3) {
		if (y + 1 < m) {
			mat[x][y]->desno = mat[x][y + 1];
			mat[x][y + 1]->levo = mat[x][y];
		}
		else {
			printf("Ne moze\n");
		}
	}
	return mat;
}

Cvor *brisanjeGrane(Cvor *mat[N][M], int n, int m) {
	int x, y, izbor;

	printf("Odaberi cvor:\n");
	scanf("%d", &x);
	scanf("%d", &y);

	printf("Gde ocete da brisete?(gore 0/dole 1/levo 2/desno 3)\n");
	scanf("%d", &izbor);

	if (izbor == 0) {
		if (x - 1 >= 0) {
			mat[x][y]->gore = NULL;
			mat[x - 1][y]->dole = NULL;
		}
		else {
			printf("Ne moze\n");
		}
	}
	else if (izbor == 1) {
		if (x + 1 < n) {
			mat[x][y]->dole = NULL;
			mat[x + 1][y]->gore = NULL;
		}
		else {
			printf("Ne moze\n");
		}
	}
	else if (izbor == 2) {
		if (y - 1 >= 0) {
			mat[x][y]->levo = NULL;
			mat[x][y - 1]->desno = NULL;
		}
		else {
			printf("Ne moze\n");
		}
	}
	else if (izbor == 3) {
		if (y + 1 < m) {
			mat[x][y]->desno = NULL;
			mat[x][y + 1]->levo = NULL;
		}
		else {
			printf("Ne moze\n");
		}
	}
	return mat;
}

void main()
{
	Cvor *mat[N][M];
	Lista *zid = NULL, *slobCvor = NULL;
	int n, m, i, j, brzid = 0, slZid, izbor, opt, opt1;
	int cha = 254;
	opt = 1;
	while (opt) {
		printf("\n====================================================================================================\n"
			"GLAVNI MENI\n\n"
			"1. Unos dimenzija lavirinta:\n"
			"2. Primov algoritam:\n"
			"3. Ispis Lavirinta\n"
			"4. Unos ulaza i izlaza:\n"
			"5. Obilazak po sirini\n"
			"6. Brisanje Lavirinta\n"
			"7. Povezuj cvorove\n"
			"8. Brisanje grane\n"
			"0. Izlaz\n\n");

		printf("Izbor: ");
		scanf("%d", &izbor);
		putchar('\n');

		switch (izbor) {
		case 0: 
			opt = 0;
			break;
		case 1:
			printf("Uneti dimenzije matrice:\n");
			scanf("%d%d", &n, &m);
			mat[N][M] = napraviMatricu(mat, n, m);
			break;
		case 2:
			mat[N][M] = primAlg(mat, n, m);
			break;
		case 3:

			for (i = 0; i < n; i++) {
				for (j = 0; j < m; j++) {
					if (j == 0 && mat[i][j]->gore == NULL) {
						printf("%c %c %c ", cha, cha, cha);
					}
					else if (j == 0 && mat[i][j]->gore != NULL) {
						printf("%c   %c ", cha, cha);
					}
					else if (j != 0 && j < m - 1 && mat[i][j]->gore == NULL) {

						printf("%c %c ", cha, cha);
					}
					else if (j != 0 && j < m - 1 && mat[i][j]->gore != NULL) {

						printf("  %c ", cha);
					}
					else if (j != 0 && j == m - 1 && mat[i][j]->gore != NULL) {
						if (mat[i][j]->izlaz == 1) {
							printf(" oo ");
						}
						else if (mat[i][j]->ulaz == 1) {
							printf(" uu ");
						}
						else
							printf("    %c", cha);
					}
					else if (j != 0 && j == m - 1 && mat[i][j]->gore == NULL) {
						if (mat[i][j]->izlaz == 1) {
							printf(" oo ");
						}
						else if (mat[i][j]->ulaz == 1) {
							printf(" uu ");
						}
						else
							printf("%c %c %c", cha, cha, cha);
					}
				}
				printf("\n");
				for (j = 0; j < m; j++) {
					if (j == 0 && mat[i][j]->desno == NULL) {
						printf("%c   %c ", cha, cha, cha);
					}
					else if (j == 0 && mat[i][j]->desno != NULL) {
						printf("%c     ", cha);
					}
					else if (j != 0 && j < m - 1 && mat[i][j]->desno == NULL) {
						printf("  %c ", cha);
					}
					else if (j != 0 && j < m - 1 && mat[i][j]->desno != NULL) {
						printf("    ");
					}
					else if (j == m - 1) {
						printf("    %c", cha);
					}
				}
				printf("\n");
			}
			for (j = 0; j < m; j++) {
				if (mat[n - 1][j]->dole == NULL) {
					if (j == m - 1)
						printf("%c %c %c", cha, cha, cha);
					else if (j == 0)
						printf("%c %c %c ", cha, cha, cha);
					else if (j != 0)
						printf("%c %c ", cha, cha);
				}
				else {
					if (mat[n - 1][j]->ulaz == 1) {
						printf("  x ");
					}
					else if (mat[n - 1][j]->izlaz == 1) {
						printf("  o ");
					}
				}
			}
			printf("\n");
			break;
		case 4:
			while (1) {
				printf("Ocete da unesete ulaz/izlaz?\n");
				scanf("%d", &opt1);
				if (opt1) {
					mat[N][M] = unosIzlaza(mat, n, m);
				}
				else {
					break;
				}
			}
			break;
		case 5:
			obilazakPoSir(mat, n, m);
			break;
		case 6:
			mat[N][M] = brisanjeMatrice(mat, n, m);
			break;
		case 7:
			mat[N][M] = povezujCvorove(mat, n, m);
			break;
		case 8:
			mat[N][M] = brisanjeGrane(mat, n, m);
			break;
		default:
			printf("Neispravno");
			break;
		}
	}

}
