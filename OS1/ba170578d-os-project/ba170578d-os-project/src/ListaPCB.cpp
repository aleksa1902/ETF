#include "ListaPCB.h"
#include "PCB.h"
#include "SCHEDULE.H"

ListaPCB::ListaPCB() {
	this->posl = 0;
	this->prvi = 0;
}


void ListaPCB::izbaciPrvi() {
	Polje* trenutni;
	if (prvi != 0) {
		trenutni = prvi;
		prvi = prvi->sledeci;
		trenutni->sledeci = 0;
		delete trenutni;
	}
}

void ListaPCB::izbaciPoslednji() {
	Polje* trenutni;

	if (prvi != 0) {
		if (posl == prvi) {
			trenutni = prvi;
			posl = 0;
			prvi = 0;
			delete trenutni;
		}
		else {
			trenutni = prvi;

			while (trenutni->sledeci != posl) trenutni = trenutni->sledeci;
			posl = trenutni;
			trenutni = trenutni->sledeci;
			posl->sledeci = 0;
			delete trenutni;
		}
	}
}

PCB* ListaPCB::uzmiPrvi() {
	if(prvi != 0) {

		return prvi->pcb;
	}
	else return 0;
}

PCB* ListaPCB::uzmiPoslednji() {
	if(posl != 0) {
		return posl->pcb;
	}
	else return 0;
}

void ListaPCB::dodajNaKraj(PCB* p) {
	Polje *novi = new Polje(p);

	if (prvi == 0) {
		prvi = novi;
		posl = novi;
	}
	else {
		posl->sledeci = novi;
		posl = novi;
	}
}

void ListaPCB::dodajNaPocetak(PCB* p) {
	Polje *novi = new Polje(p);

	if (prvi == 0) {
		prvi = novi;
		posl = novi;
	}
	else {
		novi->sledeci = prvi;
		prvi = novi;
	}
}


ListaPCB::~ListaPCB(){
	Polje *tekuci = prvi;

		while (tekuci){
			prvi = prvi->sledeci;
			tekuci->sledeci = 0;
			delete tekuci;
			tekuci = prvi;
		}

		prvi = 0;
		posl = 0;
}


void ListaPCB::promeniStatus(){
	posl->pcb->trenStatus = ready;

}

PCB* ListaPCB::pretraga(ID id){
	if(prvi == 0) return 0;

	Polje *tekuci = prvi;

	while(tekuci && tekuci->pcb->getThread()->getId() != id){
		tekuci = tekuci->sledeci;
	}

	if(tekuci) return tekuci->pcb;
	else return 0;
}


void ListaPCB::prioritetnaLista(PCB* p, int b){
	Polje* novi = new Polje(p, b);

	if(prvi == 0){
		prvi = novi;
		posl = novi;
	}else{
		Polje* tekuci = prvi;
		Polje* tekuciPre = 0;

		while(tekuci->brojac < novi->brojac){
			tekuciPre = tekuci;
			tekuci = tekuci->sledeci;
		}

		if(tekuci == prvi){
			novi->sledeci = prvi;
			prvi = novi;
		}

		else if(tekuciPre == posl){
			posl->sledeci = novi;
			posl = novi;
		}

		else{
			tekuciPre->sledeci = novi;
			novi->sledeci = tekuci;
		}
	}



}


void ListaPCB::proveraPrioritetneListe(){
	Polje* tekuci = prvi;
	while(tekuci){

		tekuci->brojac--;

		if(tekuci->brojac == 0){
			prvi = prvi->sledeci;
			tekuci->pcb->trenStatus = ready;
			Scheduler::put(tekuci->pcb);
			tekuci->sledeci = 0;
			delete tekuci;
			tekuci = prvi;
		}else tekuci = tekuci->sledeci;
	}
}


