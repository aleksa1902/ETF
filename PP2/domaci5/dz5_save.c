#include "dz5_process.c"

static void ispisUdatoteku(Cvor *Gl3, char *ime) {
	char nep[15], *str, *str1;
	int n = 0, broj;
	char ch;
	Cvor *pok;
	FILE *izlaz;
	char ispis[100], ispis2[100];

	izlaz = fopen(ime, "w");

	strcpy(ispis, "<Asx Version = \"3.0\" >");
	n = 0;

	fprintf(izlaz, "%s\n", ispis);

	//fputs(ch, izlaz);

	strcpy(ispis, "<Param Name = \"Name\" Value = \"PlayList\"/>");
	fprintf(izlaz, "%s\n", ispis);

	pok = Gl3;

	while (pok) {
		strcpy(ispis, "<Entry>");
		fprintf(izlaz, "%s\n", ispis);

		strcpy(ispis, "<Title>\"");
		fprintf(izlaz, "%s", ispis);

		fprintf(izlaz, "%s - %s", pok->pes->izvodjac, pok->pes->naziv);

		strcpy(ispis, "\"</Title>");
		fprintf(izlaz, "%s\n", ispis);

		strcpy(ispis, "<Ref href = \"");
		strcpy(ispis2, "\"/>");
		fprintf(izlaz, "%s%s%s\n", ispis, pok->pes->adresa, ispis2);

		strcpy(ispis2, "</Entry>");
		fprintf(izlaz, "%s\n", ispis2);

		fprintf(izlaz, "\n");
		pok = pok->sl;
	}
	fclose(izlaz);
}

