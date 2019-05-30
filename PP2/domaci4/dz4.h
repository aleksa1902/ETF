//#pragma once
#include "dz4_obrada.c"
/*
void unosUlistu(CvorG **listaGo);

void unosUkategorije(CvorKat *VipLoza, CvorKat *FunPit, CvorKat *Tribine, CvorKat *Parter1, CvorKat *Parter2);

void ispisGosta(Gost g);

CvorG* napNovi(Gost g);

CvorG* dodNaPocGost(CvorG *Gl, Gost g);

CvorG* dodNaKrajGost(CvorG *Gl, Gost g);

int porediGoste(Gost A, Gost B);

CvorG* brisiPrvuPojavuGosta(CvorG *Gl, Gost G);

void brisanjeListeGostiju(CvorG *Gl);

void ispisListeGostiju(CvorG *Gl);

void podeliPrvuZelju(CvorG **listaGo, CvorKat *VipLoza, CvorKat *FunPit, CvorKat *Tribine, CvorKat *Parter1, CvorKat *Parter2);

void podeliDruguZelju(CvorG **listaGo, CvorKat *VipLoza, CvorKat *FunPit, CvorKat *Tribine, CvorKat *Parter1, CvorKat *Parter2);

void podeliOstale(CvorG **listaGo, CvorKat *VipLoza, CvorKat *FunPit, CvorKat *Tribine, CvorKat *Parter1, CvorKat *Parter2);
*/

void unosUlistu(CvorG **);

void unosUkategorije(CvorKat *, CvorKat *, CvorKat *, CvorKat *, CvorKat *);

void ispisGosta(Gost);

CvorG* napNovi(Gost);

CvorG* dodNaPocGost(CvorG *, Gost );

CvorG* dodNaKrajGost(CvorG *, Gost );

int porediGoste(Gost , Gost );

CvorG* brisiPrvuPojavuGosta(CvorG *, Gost );

void brisanjeListeGostiju(CvorG *);

void ispisListeGostiju(CvorG *);

void podeliPrvuZelju(CvorG **, CvorKat *, CvorKat *, CvorKat *, CvorKat *, CvorKat *);

void podeliDruguZelju(CvorG **, CvorKat *, CvorKat *, CvorKat *, CvorKat *, CvorKat *);

void podeliOstale(CvorG **, CvorKat *, CvorKat *, CvorKat *, CvorKat *, CvorKat *);