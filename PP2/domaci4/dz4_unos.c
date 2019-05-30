#include "dz4_ispis.c"

static void unosUlistu(CvorG **listaGo) {
	int x = 1;
	Gost gost;

	while (x) {
		printf("Unesite ime i prezime kupca i prvu i drugu zelju naznaciti brojevima\n1.Vip Loza,\n2.Fun Pun,\n3.Tribine,\n4.Parter 1,\n5. Parter2\n");
		scanf("%s", gost.ime);
		scanf("%s", gost.prez);
		scanf("%d", &gost.primKat);
		scanf("%d", &gost.secKat);
		listaGo = dodNaPocGost(listaGo, gost);

		printf("Da li zelite da dodajete jos?(1/0)");
		scanf("%d", &x);
		printf("\n");
	}
}

static void unosUkategorije(CvorKat *VipLoza, CvorKat *FunPit, CvorKat *Tribine, CvorKat *Parter1, CvorKat *Parter2) {
	printf("Unesite broj mesta i cenu za Vip Lozu:\n");
	scanf("%d %d", &VipLoza->brMesta, &VipLoza->cena);
	VipLoza->listaG = NULL;
	VipLoza->zauzeto = 0;

	printf("Unesite broj mesta i cenu za Fun Pit:\n");
	scanf("%d %d", &FunPit->brMesta, &FunPit->cena);
	FunPit->listaG = NULL;
	FunPit->zauzeto = 0;

	printf("Unesite broj mesta i cenu za Tribine:\n");
	scanf("%d %d", &Tribine->brMesta, &Tribine->cena);
	Tribine->listaG = NULL;
	Tribine->zauzeto = 0;

	printf("Unesite broj mesta i cenu za Parter 1:\n");
	scanf("%d %d", &Parter1->brMesta, &Parter1->cena);
	Parter1->listaG = NULL;
	Parter1->zauzeto = 0;

	printf("Unesite broj mesta i cenu za Parter 2:\n");
	scanf("%d %d", &Parter2->brMesta, &Parter2->cena);
	Parter2->listaG = NULL;
	Parter2->zauzeto = 0;
}