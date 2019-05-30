#include "dz5_init.c"

static Cvor* nepotrebno(Cvor *lista, char *ime) {
	char nep[15], *str, *str1;
	Pesma *pesma;
	int n = 0, broj;
	char ch;
	int brojPesama, i;
	FILE *ulaz;

	ulaz = fopen(ime, "r");
	if (ulaz == NULL) {
		printf("Neuspelo otvaranje datoteke!\n");
		system("pause");
		exit(1);
	}

	while (1) {
		ch = getc(ulaz);
		if (ch < 32) {
			break;
		}
	}

	ch = getc(ulaz);
	int brm = 2;
	str = (char*)malloc(sizeof(char)*brm);
	while (1 && ch != EOF) {
		ch = getc(ulaz);
		if (ch < 32) {
			break;
		}
		if (n == brm) {
			brm *= 2;
			str = (char*)realloc(str, sizeof(char)*brm);//
		}
		str[n] = ch;
		n++;
	}
	str[n] = '\0';
	n++;

	str = (char*)realloc(str, sizeof(char)*(n + 1));//

	str1 = strchr(str, '=');
	str1++;
	brojPesama = atoi(str1);

	ch = getc(ulaz);

	for (i = 0; i < brojPesama; i++) {
		pesma = (Pesma*)malloc(sizeof(Pesma));
		broj = 0;
		n = 0;
		while (1 && ch != EOF) {
			ch = getc(ulaz);
			if (ch < 32) {
				break;
			}
			if (broj == 1) {
				pesma->adresa[n] = ch;
				n++;
			}
			if (ch == 61) {
				broj = 1;
			}
		}
		pesma->adresa[n] = '\0';

		ch = getc(ulaz);

		broj = 0;
		n = 0;
		while (1 && ch != EOF) {
			ch = getc(ulaz);
			if (ch == 45) {
				break;
			}
			if (broj == 1) {
				pesma->izvodjac[n] = ch;
				n++;
			}
			if (ch == 61) {
				broj = 1;
			}

		}
		n--;
		pesma->izvodjac[n] = '\0';

		broj = 0;
		n = 0;
		while (1 && ch != EOF) {
			ch = getc(ulaz);
			if (ch < 32) {
				break;
			}
			if (broj == 1) {
				pesma->naziv[n] = ch;
				n++;
			}
			if (ch == ' ') {
				broj = 1;
			}
		}
		pesma->naziv[n] = '\0';

		ch = getc(ulaz);

		n = 0;
		broj = 0;
		while (1 && ch != EOF) {
			ch = getc(ulaz);
			if (ch < 32) {
				break;
			}
			if (broj == 1 && ch > 47 && ch < 58) {
				pesma->duzina[n] = ch;
				n++;
			}
			if (ch == 61) {
				broj = 1;
			}

		}
		pesma->duzina[n] = '\0';

		lista = dodNaPoc(lista, pesma);

		ispisPesme(pesma);
		ch = getc(ulaz);

	}

	fclose(ulaz);
	return lista;


}