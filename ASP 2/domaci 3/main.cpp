#include "Heap.h"
#include "PreformanceCalculator.h"
#include<stdlib.h>
#include<fstream>
#include <time.h>


int main() {
	PerformanceCalculator pc;
	int q = 1;
	int s = 0;
	Heap hip;
	int puta, ii, broj, numb, nesto;
	double protekloVreme;
	srand(time(NULL));

	while (q) {
		cout << "-------------------------------------------------------" << endl;
		cout << "Izaberite opciju:" << endl << endl;
		cout << "1. Stvaranje reda:" << endl;
		cout << "2. Provera da li je red prazan" << endl;
		cout << "3. Dohvatanje prvog elementa reda" << endl;
		cout << "4. Brisanje prvog elementa reda" << endl;
		cout << "5. Umetanje elementa u red" << endl;
		cout << "6. Tabeliranje" << endl;
		cout << "7. Konvertovanje" << endl;
		cout << "8. Ispis" << endl;
		cout << "9. Unistavanje hipa" << endl;
		cout << "0. Izlaz" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Unesi stavku za izvrsavanje operacije: ";

		cin >> q;
		switch (q) {
		case 1: hip.init(); break;
		case 2:
			if ((hip.first == nullptr) || (hip.first->info == -1))
				cout << "Red je prazan !" << endl;
			else
				cout << "Red nije prazan !" << endl;
			break;
		case 3:
			int br;
			br = hip.get();
			cout << "Prvi element reda je :" << br << endl;
			break;
		case 4:
			pc.start();
			hip.Delete(s);
			pc.stop();
			protekloVreme = pc.elapsedMillis();
			cout << protekloVreme << " broj koraka:" << s << endl;
			break;
		case 5:
			cout << "Unesite vrednost elementa koji zelite da ubacite u red:" << endl;
			int i;
			cin >> i;
			hip.add(i, s);
			break;
		case 6:
			numb = 10;
			for (int brojac = 0; brojac < 5; brojac++) {
				cout << "Broj elemenata: " << numb << "\t";
				hip.init();
				pc.start();
				ii = 0;
				s = 0;
				while (ii != numb) {
					nesto = rand() % 1000 + 1;
					hip.add(nesto, s);
					ii++;
				}
				pc.stop();
				protekloVreme = pc.elapsedMillis();
				cout << " Vreme umetanja: " << protekloVreme << " broj koraka: " << s << "\t";

				pc.start();
				hip.Delete(s);
				pc.stop();
				protekloVreme = pc.elapsedMillis();
				cout << " Vreme brisanja: " << protekloVreme << " broj koraka: " << s << endl;

				hip.destroy();
				numb *= 10;
			}
			hip.init();
			break;
		case 7:
			hip.Convert();
			break;
		case 8:
			hip.print(hip.first);
			break;
		case 9:
			hip.destroy();
			hip.init();
			break;
		case 0:
			exit(1);
			break;
		}
	}
}
