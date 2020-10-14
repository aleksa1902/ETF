/*
 * ListKSem.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: OS1
 */

#include "ListKSem.h"
#include "ListaPCB.h"
#include "Timer.h"

	ListKernelSem::ListKernelSem(){
		prvi = 0;
		poslednji = 0;
	}

	void ListKernelSem::ubaciNaPocetak(KernelSem* ks){
		Polje *novi = new Polje(ks);

			if (prvi == 0) {
				prvi = novi;
				poslednji = novi;
			}
			else {
				novi->sled = prvi;
				prvi = novi;
			}
	}

	void ListKernelSem::ubaciNaKraj(KernelSem* ks){
		Polje *novi = new Polje(ks);

			if (prvi == 0) {
				prvi = novi;
				poslednji = novi;
			}
			else {
				poslednji->sled = novi;
				poslednji = novi;
			}
	}

	void ListKernelSem::izbaciSaPocetka(){
		Polje* trenutni;
		if (prvi != 0) {
			trenutni = prvi;
			prvi = prvi->sled;
			trenutni->sled = 0;
			delete trenutni;
		}
	}

	void ListKernelSem::izbaciSaKraja(){
		Polje* trenutni;

			if (prvi != 0) {
				if (poslednji == prvi) {
					trenutni = prvi;
					poslednji = 0;
					prvi = 0;
					delete trenutni;
				}
				else {
					trenutni = prvi;

					while (trenutni->sled != poslednji) trenutni = trenutni->sled;
					poslednji = trenutni;
					trenutni = trenutni->sled;
					poslednji->sled = 0;
					delete trenutni;
				}
			}
	}

	void ListKernelSem::izbaci(KernelSem* ks){
		Polje* tek = prvi;
		Polje* tekPre = 0;

		while(tek->kernelSem != ks){
			tekPre = tek;
			tek = tek->sled;
		}

		if(tek->kernelSem == ks){
			tekPre->sled = tek->sled;
			tek->sled = 0;
			delete tek;
		}

	}

	KernelSem* ListKernelSem::uzmiPrvi(){
		if(prvi != 0) {

				return prvi->kernelSem;
			}
			else return 0;
	}

	KernelSem* ListKernelSem::uzmiPosl(){
		if(poslednji != 0) {
				return poslednji->kernelSem;
			}
			else return 0;
	}

	ListKernelSem::~ListKernelSem(){
		Polje *tekuci = prvi;

		while (tekuci){
			prvi = prvi->sled;
			tekuci->sled = 0;
			delete tekuci;
			tekuci = prvi;
		}

		prvi = 0;
		poslednji = 0;
	}

	void ListKernelSem::proveravanjeNiti(){
		Polje* tekuci = prvi;

		Timer::lockedFlag = 0;

		while(tekuci){
			tekuci->kernelSem->listWaitDifZero->proveraPrioritetneListe();
			tekuci = tekuci->sled;
		}
		Timer::lockedFlag = 1;
	}



