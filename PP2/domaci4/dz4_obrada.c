#include "dz4_unos.c"

static CvorG* napNovi(Gost g) {
	CvorG *novi = (CvorG*)malloc(sizeof(CvorG));
	if (novi == NULL) {
		printf("Neuspela alokacija");
		exit(1);
	}
	novi->gost = g;
	novi->sl = NULL;
	return novi;
}

static CvorG* dodNaPocGost(CvorG *Gl, Gost g) {
	CvorG *novi = napNovi(g);
	if (Gl == NULL) {
		return novi;
	}
	novi->sl = Gl;
	return novi;
}

static CvorG* dodNaKrajGost(CvorG *Gl, Gost g) {
	CvorG *novi = napNovi(g);
	CvorG *tek;
	if (Gl == NULL) {
		return novi;
	}
	while (tek->sl) {
		tek = tek->sl;
	}
	tek->sl = novi;
	return novi;
}


static int porediGoste(Gost A, Gost B) {
	if (strcmp(A.ime, B.ime) == 0 && strcmp(A.prez, B.prez) == 0 && A.primKat == B.primKat && A.secKat == B.secKat) {
		return 0;
	}
	else return -1;
}

static CvorG* brisiPrvuPojavuGosta(CvorG *Gl, Gost G) {
	CvorG *p, *t;
	if (Gl == NULL) return NULL;
	if (porediGoste(Gl->gost, G) == 0) {
		p = Gl;
		Gl = Gl->sl;
		free(p);
		return Gl;
	}
	t = Gl;
	while (t->sl != NULL && porediGoste(t->sl->gost, G) != 0) {
		t = t->sl;
	}
	if (t->sl != NULL) {//treba da se brise
		p = t->sl;
		t->sl = p->sl;
		free(p);
	}
	return Gl;
}

static void brisanjeListeGostiju(CvorG *Gl) {
	CvorG* p;
	while (Gl) {
		p = Gl;
		Gl = Gl->sl;
		free(p);
	}
}



static void podeliPrvuZelju(CvorG **listaGo, CvorKat *VipLoza, CvorKat *FunPit, CvorKat *Tribine, CvorKat *Parter1, CvorKat *Parter2) {
	CvorG *t = *listaGo;
	Gost pomG;
	while (t) {
		pomG = t->gost;
		switch (t->gost.primKat) {
		case 0: {
			if (VipLoza->brMesta > 0) {
				VipLoza->listaG = dodNaPocGost(VipLoza->listaG, t->gost);
				VipLoza->brMesta--;
				VipLoza->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}
				break;
		case 1: {
			if (FunPit->brMesta > 0) {
				FunPit->listaG = dodNaPocGost(FunPit->listaG, t->gost);
				FunPit->brMesta--;
				FunPit->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}break;
		case 2: {
			if (Tribine->brMesta > 0) {
				Tribine->listaG = dodNaPocGost(Tribine->listaG, t->gost);
				Tribine->brMesta--;
				Tribine->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}
				break;
		case 3: {
			if (Parter1->brMesta > 0) {
				Parter1->listaG = dodNaPocGost(Parter1->listaG, t->gost);
				Parter1->brMesta--;
				Parter1->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}
				break;
		case 4: {
			if (Parter2->brMesta > 0) {
				Parter2->listaG = dodNaPocGost(Parter2->listaG, t->gost);
				Parter2->brMesta--;
				Parter2->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}
				break;
		default: {
			printf("Nije pronadjena opcija!\n");
		} break;
		}
		//	printf("Obradjen gost: ");
		//	ispisGosta(pomG);
		//	system("pause");

	}
}
static void podeliDruguZelju(CvorG **listaGo, CvorKat *VipLoza, CvorKat *FunPit, CvorKat *Tribine, CvorKat *Parter1, CvorKat *Parter2) {
	CvorG *t = *listaGo;
	Gost pomG;
	while (t) {
		pomG = t->gost;
		switch (t->gost.secKat) {
		case 0: {
			if (VipLoza->brMesta > 0) {
				VipLoza->listaG = dodNaPocGost(VipLoza->listaG, t->gost);
				VipLoza->brMesta--;
				VipLoza->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}
				break;
		case 1: {
			if (FunPit->brMesta > 0) {
				FunPit->listaG = dodNaPocGost(FunPit->listaG, t->gost);
				FunPit->brMesta--;
				FunPit->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}break;
		case 2: {
			if (Tribine->brMesta > 0) {
				Tribine->listaG = dodNaPocGost(Tribine->listaG, t->gost);
				Tribine->brMesta--;
				Tribine->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}
				break;
		case 3: {
			if (Parter1->brMesta > 0) {
				Parter1->listaG = dodNaPocGost(Parter1->listaG, t->gost);
				Parter1->brMesta--;
				Parter1->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}
				break;
		case 4: {
			if (Parter2->brMesta > 0) {
				Parter2->listaG = dodNaPocGost(Parter2->listaG, t->gost);
				Parter2->brMesta--;
				Parter2->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
			}
			else {
				t = t->sl;
			}
		}
				break;
		default: printf("Nije pronadjena opcija!\n"); break;
		}

	}
}
static void podeliOstale(CvorG **listaGo, CvorKat *VipLoza, CvorKat *FunPit, CvorKat *Tribine, CvorKat *Parter1, CvorKat *Parter2) {
	CvorG *t = *listaGo;
	Gost pomG;
	while (t) {
		pomG = t->gost;
		if (pomG.primKat == 0) {
			if (VipLoza->cena > FunPit->cena && FunPit->brMesta > 0) {
				FunPit->listaG = dodNaPocGost(FunPit->listaG, t->gost);
				FunPit->brMesta--;
				FunPit->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (VipLoza->cena > Tribine->cena && Tribine->brMesta > 0) {
				Tribine->listaG = dodNaPocGost(Tribine->listaG, t->gost);
				Tribine->brMesta--;
				Tribine->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (VipLoza->cena > Parter1->cena && Parter1->brMesta > 0) {
				Parter1->listaG = dodNaPocGost(Parter1->listaG, t->gost);
				Parter1->brMesta--;
				Parter1->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (VipLoza->cena > Parter2->cena && Parter2->brMesta > 0) {
				Parter2->listaG = dodNaPocGost(Parter2->listaG, t->gost);
				Parter2->brMesta--;
				Parter2->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
		}
		if (pomG.primKat == 1) {
			if (FunPit->cena > VipLoza->cena && VipLoza->brMesta > 0) {
				VipLoza->listaG = dodNaPocGost(VipLoza->listaG, t->gost);
				VipLoza->brMesta--;
				VipLoza->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (FunPit->cena > Tribine->cena && Tribine->brMesta > 0) {
				Tribine->listaG = dodNaPocGost(Tribine->listaG, t->gost);
				Tribine->brMesta--;
				Tribine->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (FunPit->cena > Parter1->cena && Parter1->brMesta > 0) {
				Parter1->listaG = dodNaPocGost(Parter1->listaG, t->gost);
				Parter1->brMesta--;
				Parter1->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (FunPit->cena > Parter2->cena && Parter2->brMesta > 0) {
				Parter2->listaG = dodNaPocGost(Parter2->listaG, t->gost);
				Parter2->brMesta--;
				Parter2->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
		}
		if (pomG.primKat == 2) {
			if (Tribine->cena > VipLoza->cena && VipLoza->brMesta > 0) {
				VipLoza->listaG = dodNaPocGost(VipLoza->listaG, t->gost);
				VipLoza->brMesta--;
				VipLoza->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Tribine->cena > FunPit->cena && FunPit->brMesta > 0) {
				FunPit->listaG = dodNaPocGost(FunPit->listaG, t->gost);
				FunPit->brMesta--;
				FunPit->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Tribine->cena > Parter1->cena && Parter1->brMesta > 0) {
				Parter1->listaG = dodNaPocGost(Parter1->listaG, t->gost);
				Parter1->brMesta--;
				Parter1->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Tribine->cena > Parter2->cena && Parter2->brMesta > 0) {
				Parter2->listaG = dodNaPocGost(Parter2->listaG, t->gost);
				Parter2->brMesta--;
				Parter2->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
		}
		if (pomG.primKat == 3) {
			if (Parter1->cena > VipLoza->cena && VipLoza->brMesta > 0) {
				VipLoza->listaG = dodNaPocGost(VipLoza->listaG, t->gost);
				VipLoza->brMesta--;
				VipLoza->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Parter1->cena > Tribine->cena && Tribine->brMesta > 0) {
				Tribine->listaG = dodNaPocGost(Tribine->listaG, t->gost);
				Tribine->brMesta--;
				Tribine->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Parter1->cena > FunPit->cena && FunPit->brMesta > 0) {
				FunPit->listaG = dodNaPocGost(FunPit->listaG, t->gost);
				FunPit->brMesta--;
				FunPit->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Parter1->cena > Parter2->cena && Parter2->brMesta > 0) {
				Parter2->listaG = dodNaPocGost(Parter2->listaG, t->gost);
				Parter2->brMesta--;
				Parter2->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
		}
		if (pomG.primKat == 4) {
			if (Parter2->cena > VipLoza->cena && VipLoza->brMesta > 0) {
				VipLoza->listaG = dodNaPocGost(VipLoza->listaG, t->gost);
				VipLoza->brMesta--;
				VipLoza->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Parter2->cena > Tribine->cena && Tribine->brMesta > 0) {
				Tribine->listaG = dodNaPocGost(Tribine->listaG, t->gost);
				Tribine->brMesta--;
				Tribine->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Parter2->cena > FunPit->cena && FunPit->brMesta > 0) {
				FunPit->listaG = dodNaPocGost(FunPit->listaG, t->gost);
				FunPit->brMesta--;
				FunPit->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
			if (Parter2->cena > Parter1->cena && Parter1->brMesta > 0) {
				Parter1->listaG = dodNaPocGost(Parter1->listaG, t->gost);
				Parter1->brMesta--;
				Parter1->zauzeto++;
				t = t->sl;
				*listaGo = brisiPrvuPojavuGosta(*listaGo, pomG);
				continue;
			}
		}
		t = t->sl;
	}
}
