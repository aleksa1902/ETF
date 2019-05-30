#include "dz5.h"

int main(int argc, char *argv[]) {
	int i, x, n;
	Cvor *Gl = NULL;
	Cvor *Gl2 = NULL;
	Cvor *Gl3 = NULL;
	char ime[200];
	int vreme;

	time_t pIntTime = time(NULL);
	struct timeb start, end;
	ftime(&start);
	struct tm* currentLocalTime = localtime(&pIntTime);
	char* dateTimeString = calloc(100 + 1, sizeof(char));
	unsigned diff;//razlika izmedju dva vremena
	if (currentLocalTime && dateTimeString)
		strftime(dateTimeString, 100, "%H:%M:%S", currentLocalTime);
	puts("Pocetak:");
	puts(dateTimeString);

	//strcpy(ime, "druga.PLS");
	strcpy(ime, argv[1]);
	Gl = nepotrebno(Gl, ime);

	//ispisListe(Gl);
	puts("_________________________________________________");
	strcpy(ime, "etf1.pls");
	Gl2 = nepotrebno(Gl2, argv[2]);

	Gl3 = zajednicki(Gl, Gl2, Gl3);

	brisanjeListe(Gl);
	brisanjeListe(Gl2);

	strcpy(ime, "izlaz.ASX");
	ispisUdatoteku(Gl3, argv[3]);

	brisanjeListe(Gl3);

	currentLocalTime = localtime(&pIntTime);
	strftime(dateTimeString, 100, "%H:%M:%S", currentLocalTime);
	puts("Kraj:");
	puts(dateTimeString);
	ftime(&end);
	diff = (int)(1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
	printf("Program se izvrsavao %u ms\n", diff);


	system("pause");

	return 0;

}

