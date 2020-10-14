#ifndef LISTAPCB_H_
#define LISTAPCB_H_

#include "Thread.h"


class PCB;

class ListaPCB{
private:

		struct Polje {
			PCB* pcb;
			int brojac;
			Polje* sledeci;
			Polje(PCB* p, int broj = 0) {
				pcb = p;
				sledeci = 0;
				brojac = broj;
			}

			~Polje() {}
		};

		Polje *prvi, *posl;

	public:
		ListaPCB();
		void izbaciPoslednji();
		void izbaciPrvi();
		PCB* uzmiPoslednji();
		PCB* uzmiPrvi();
		void dodajNaKraj(PCB* p);
		void dodajNaPocetak(PCB* p);

		void prioritetnaLista(PCB* p, int b);
		void proveraPrioritetneListe();

		~ListaPCB();
		void promeniStatus();
		PCB* pretraga(ID id);

};


#endif /* LISTAPCB_H_ */
