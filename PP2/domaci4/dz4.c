#include "dz4.h"

void main() {
	int x = 1;
	CvorG *listaGo = NULL;
	CvorKat FunPit, VipLoza, Parter1, Parter2, Tribine;

	while (x) {
		printf("GLAVNI MENI\n\n"
			"1. Unos liste gostiju sa zeljama:\n"
			"2. Unos cene i broj mesta kategorija\n"
			"3. Ubacivanje po prvoj zelji\n"
			"4. Ubacivanje po drugoj zelji\n"
			"5. Ubacivanje na treci nacin\n"
			"6. Ispis lista\n"
			"7. Brisanje liste gostiju\n"
			"8. Brisanje lista kategorija.\n"
			"9. Izlaz\n\n");

		int izbor;
		printf("Izbor: ");
		scanf("%d", &izbor);
		putchar('\n');

		switch (izbor) {
		case 1:
			unosUlistu(&listaGo);
			break;
		case 2:
			unosUkategorije(&VipLoza, &FunPit, &Tribine, &Parter1, &Parter2);
			break;
		case 3:
			podeliPrvuZelju(&listaGo, &VipLoza, &FunPit, &Tribine, &Parter1, &Parter2);
			break;
		case 4:
			podeliDruguZelju(&listaGo, &VipLoza, &FunPit, &Tribine, &Parter1, &Parter2);
			break;
		case 5:
			podeliOstale(&listaGo, &VipLoza, &FunPit, &Tribine, &Parter1, &Parter2);
			break;
		case 6:
			printf("Vip Loza: \n");
			ispisListeGostiju(VipLoza.listaG);
			printf("FunPit: \n");
			ispisListeGostiju(FunPit.listaG);
			printf("Tribine: \n");
			ispisListeGostiju(Tribine.listaG);
			printf("Parter1: \n");
			ispisListeGostiju(Parter1.listaG);
			printf("Parter2: \n");
			ispisListeGostiju(Parter2.listaG);
			printf("Preostali Gosti bez karata:\n");
			ispisListeGostiju(listaGo);
			break;
		case 7:
			brisanjeListeGostiju(listaGo);
			break;
		case 8:
			brisanjeListeGostiju(VipLoza.listaG);
			brisanjeListeGostiju(FunPit.listaG);
			brisanjeListeGostiju(Tribine.listaG);
			brisanjeListeGostiju(Parter1.listaG);
			brisanjeListeGostiju(Parter2.listaG);
			break;
		case 9:
			x = 0;
			break;
		default:
			puts("Neispravan unos");
		}
	}
}
